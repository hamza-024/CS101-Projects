#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>

#include "p3.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

//Helper Functions
int PersonList::compareOfHeightWeight(const Person *person1, const Person *person2) {
    if (person1->height != person2->height) {
        return person2->height - person1->height; 
    }
    
    if (person1->weight != person2->weight) {
        return person1->weight - person2->weight; 
    }
    
        return 1;
}



int PersonList::getSize()
{
    return size;
}

void PersonList::printByHeight(ostream &os)
{
    Person *heightList[size];
    int j = 0;

    Person *cur = headHeightList;
    while(cur != nullptr){
        heightList[j] = cur;
        cur = cur -> nextHeight;
        j++;
    }

    //Selection Sort
    for(int i = 0; i < size - 1; i++){
        int indexMax = i;

        for(int k = i + 1; k < size; k++){
            if(heightList[k] -> height > heightList[indexMax] -> height){
                indexMax = j;
            }
        }
        Person *t = heightList[indexMax];
        heightList[indexMax] = heightList[i];
        heightList[i] = t;
    }

    for(int i = 0; i < size; i++){
        os << heightList[i] -> first << " " << heightList[i] -> last << ": height =" << heightList[i] -> height << ", weight =" << heightList[i]->weight << endl;
    }
}

void PersonList::printByWeight(ostream &os)
{
    Person *weightList[size];
    int i = 0;
    Person *current = headWeightList;
    while(current != nullptr){
        weightList[i] = current;
        current = current -> nextWeight;
        i++;
    }

    for(int i = 0; i < size - 1; i++){
        int maxIndex = i;
        for(int j = i + 1; j < size; j++){
            if(weightList[i] -> weight > weightList[maxIndex] -> weight){
                maxIndex = j;
            }
        }
        Person *t = weightList[maxIndex];
        weightList[maxIndex] = weightList[i];
        weightList[i] = t;
    }

    for(int i = 0; i < size; i++){
        os << weightList[i] -> first << " " << weightList[i] -> last << ": height =" << weightList[i] -> height << ", weight =" << weightList[i] -> weight << endl;
    }
}

bool PersonList::exists(string first, string last)
{
    Person *cur = headHeightList;

    while(cur != nullptr){
        if(cur -> first == first && cur -> last == last){
            return true;
        }
        cur = cur -> nextHeight;
    }
    return false;
}

int PersonList::getHeight(string first, string last) {
    Person *cur = headHeightList;
    while(cur != nullptr){
        if(cur -> last == last && cur -> first == first){
            return cur -> height;
        }
        cur = cur -> nextHeight;
    }
    return -1;
}

int PersonList::getWeight(string first, string last) {
    Person *cur = headWeightList;
    while(cur != nullptr){
        if(cur -> first == first && cur -> last == last){
            return cur -> weight;
        }
        cur = cur -> nextWeight;
    }
    return -1;
}

bool PersonList::add(std::string first, std::string last, int height, int weight) {
    if (exists(first, last)) {
        return false;
    }

    Person *p = new Person(first, last, height, weight);

    if (headHeightList == nullptr || p->height > headHeightList->height ||
        (p->height == headHeightList->height && p->weight < headHeightList->weight)) {
        p->nextHeight = headHeightList;
        headHeightList = p;
    } else {
        Person *cur = headHeightList;
        while (cur->nextHeight != nullptr && (cur->nextHeight->height > p->height ||
                (cur->nextHeight->height == p->height &&
                 cur->nextHeight->weight > p->weight))) {
            cur = cur->nextHeight;
        }
        p->nextHeight = cur->nextHeight;
        cur->nextHeight = p;
    }

    if (headWeightList == nullptr || p->weight < headWeightList->weight ||
        (p->weight == headWeightList->weight && p->height > headWeightList->height)) {
        p->nextWeight = headWeightList;
        headWeightList = p;
    } else {
        Person *cur = headWeightList;
        while (cur->nextWeight != nullptr &&
               (cur->nextWeight->weight < p->weight ||
                (cur->nextWeight->weight == p->weight &&
                 cur->nextWeight->height < p->height))) {
            cur = cur->nextWeight;
        }
        p->nextWeight = cur->nextWeight;
        cur->nextWeight = p;
    }

    size++;
    return true;
}



bool PersonList::remove(string first, string last) {
    if (size == 0) {
        return false;
    }
    
    if (headHeightList->last == last && headHeightList->first == first) {
        Person *t = headHeightList;
        headHeightList = headHeightList->nextHeight;
        headWeightList = t->nextWeight;
        delete t;
        size--;
        return true;
    }
    
    Person *cur = headHeightList->nextHeight;
    Person *before = headHeightList;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            before->nextHeight = cur->nextHeight;
            before->nextWeight = cur->nextWeight;
            delete cur;
            size--;
            return true;
        }
        before = cur;
        cur = cur->nextHeight;
    }
    
    cur = headWeightList;
    before = nullptr;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            before->nextWeight = cur->nextWeight;
            if (before == nullptr) {
                headHeightList = cur->nextHeight;
            }
            else {
                before->nextHeight = cur->nextHeight;
            }
            delete cur;
            size--;
            return true;
        }
        before = cur;
        cur = cur->nextWeight;
    }
    
    return false;
}


bool PersonList::updateName(string first, string last, string newFirst, string newLast) {
    Person *cur = headHeightList;
    bool match = false;
    while (cur != nullptr && !match) {
        if (cur->first == first && cur->last == last) {
            match = true;
            cur->first = newFirst;
            cur->last = newLast;
            break;
        }
        cur = cur->nextHeight;
    }

    if (match) {
        int height = cur->height;
        int weight = cur->weight;
        remove(first, last);
        add(newFirst, newLast, height, weight);
        return true;
    }
    else {
        return false;
    }
}

bool PersonList::updateHeight(std::string first, std::string last, int height) 
{
    Person *cur = headHeightList;
    Person *before = nullptr;
    while (cur != nullptr) {
        if (cur->first == first && cur->last == last) {
            if (before == nullptr) {
                headHeightList = cur->nextHeight;
            } else {
                before->nextHeight = cur->nextHeight;
            }
            cur->height = height;
            Person *newPrev = nullptr;
            Person *newCurrent = headHeightList;
            while (newCurrent != nullptr) {
                if (compareOfHeightWeight(cur, newCurrent) <= 0) {
                    cur->nextHeight = newCurrent;
                    if (newPrev == nullptr) {
                        headHeightList = cur;
                    } else {
                        newPrev->nextHeight = cur;
                    }
                    return true;
                }
                newPrev = newCurrent;
                newCurrent = newCurrent->nextHeight;
            }
            cur->nextHeight = nullptr;
            if (newPrev == nullptr) {
                headHeightList = cur;
            } else {
                newPrev->nextHeight = cur;
            }
            return true;
        }
        before = cur;
        cur = cur->nextHeight;
    }
    return false;
}



bool PersonList::updateWeight(string first, string last, int weight) 
{
    Person *cur = headWeightList;
    Person *before = nullptr;
    while (cur != nullptr) {
        if (cur->last == last && cur->first == first) {
            if (before == nullptr) {
                headWeightList = cur->nextWeight;
            } else {
                before->nextWeight = cur->nextWeight;
            }
            cur->weight = weight;
            Person *newBef = nullptr;
            Person *newCur = headWeightList;
            while (newCur != nullptr) {
                if (compareOfHeightWeight(cur, newCur) <= 0) {
                    cur->nextWeight = newCur;
                    if (newBef == nullptr) {
                        headWeightList = cur;
                    } else {
                        newBef->nextWeight = cur;
                    }
                    return true;
                }
                newBef = newCur;
                newCur = newCur->nextWeight;
            }
            cur->nextHeight = nullptr;
            if (newBef == nullptr) {
                headWeightList = cur;
            } else {
                newBef->nextWeight = cur;
            }
            return true;
        }
        before = cur;
        cur = cur->nextWeight;
    }
    return false;
}



PersonList::~PersonList()
{
    Person *cur = headHeightList;
    while(cur != nullptr){
        Person *after = cur->nextHeight;
        delete cur;
        cur = after;
    }

    headHeightList = nullptr;
    headWeightList = nullptr;
    size = 0;
}

PersonList::PersonList(const PersonList &src)
{
    size = 0;
    headHeightList = nullptr;
    headWeightList = nullptr;

    Person* cur = src.headHeightList;
    while(cur != nullptr){
        add(cur->first, cur->last, cur->height, cur->weight);
        cur = cur->nextHeight;
    }
}

const PersonList &PersonList::operator=(const PersonList &src)
{
    if(this == &src){
        return *this;
    }

    PersonList temp;

    for(Person* current = src.headHeightList; current != nullptr; current = current->nextHeight){
        temp.add(current->first, current->last, current->height, current->weight);
    }

    std::swap(headHeightList, temp.headHeightList);
    std::swap(headWeightList, temp.headWeightList);
    std::swap(size, temp.size);

    return *this;
}
