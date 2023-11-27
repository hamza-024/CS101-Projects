#include <iostream> 
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

// Store the return of this function as an unsigned long!
unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash;
}

class HashTable {
public:
    HashTable(int len, int stratC, int a = 0)
        : len(len), stratC(stratC), a(a) {
        table.resize(len);
    }

    void insert(string key, int line) {
        int index = h1(key);

        if (table[index].first.empty()) {
            table[index].first = key;
            table[index].second.push_back(line);
        } else {
            int j = 0;
            int collisions = 0;

            while (!table[index].first.empty() && table[index].first != key) {
                collisions++;
                j++;
                index = getNextIndex(key, j);
            }

            if (table[index].first.empty()) {
                table[index].first = key;
                table[index].second.push_back(line);
            } else {
                table[index].second.push_back(line);
            }

            totalCollisions += collisions;
        }
        totalWords++;
    }

    pair<string, pair<vector<int>, int>> search(string key) {
        int index = h1(key);
        int j = 0;
        int collisions = 0;

        while (!table[index].first.empty() && table[index].first != key) {
            collisions++;
            j++;
            index = getNextIndex(key, j);
        }

        return {table[index].first, {table[index].second, collisions}};
    }

    int getTotalWords() {
        return totalWords;
    }

    int getDistinctWords() {
        int distinctWordCount = 0;
        for (const auto &entry : table) {
            if (!entry.first.empty()) {
                distinctWordCount++;
            }
        }
        return distinctWordCount;
    }
    int getTotalCollisions() {
        return totalCollisions;
    }

private:
   int len;
   int stratC;
   int a;
   int totalWords = 0;
   int totalCollisions = 0;
   vector<pair<string, vector<int>>> table;

    int h1(string key) {
        return djb2(key) % len;
    }

    int h2(string key) {
        return a - (djb2(key) % a);
    }

    int getNextIndex(string key, int j) {
        switch (stratC) {
        case 1://LP
            return (h1(key) + j) % len;
        case 2://QP
            return (h1(key) + j * j) % len;
        case 3://DH
            return (h1(key) + j * h2(key)) % len;
        default:
            return -1;
        }
    }
};

void processWord(HashTable &hash_table, string &word, int line) {
    if (!word.empty()) {
        for (auto &c : word) {
            c = tolower(c);
        }
        hash_table.insert(word, line);
    }
}

//Main Function

int main(int argc, char *argv[]) {
string inFile = argv[1];
string qFile = argv[2];
int size = stoi(argv[3]);
int cStrat = (argv[4][0] == 'l' ? 1 : (argv[4][0] == 'q' ? 2 : 3));
int a = (cStrat == 3 ? stoi(argv[5]) : 0);

HashTable hash_table(size, cStrat, a);

ifstream in(inFile);

string line;
int line_num = 1;
while (getline(in, line)) {
    string word;
    istringstream iss(line);
    char x;
    while (iss.get(x)) {
        if (isalpha(x)) {
            word.push_back(x);
        } else {
            processWord(hash_table, word, line_num);
            word.clear();
        }
    }
    processWord(hash_table, word, line_num);
    line_num++;
}

cout << "The number of words found in the file was " << hash_table.getTotalWords() << endl;
cout << "The number of unique words found in the file was " << hash_table.getDistinctWords() << endl;
cout << "The number of collisions was " << hash_table.getTotalCollisions() << endl;
cout << endl;

ifstream queryWords(qFile);

int counts = 0;
while (getline(queryWords, line)) {
    istringstream iss(line);
    string query;
    iss >> query;

    auto result = hash_table.search(query);
    cout << query << " appears on lines [";
    for (size_t i = 0; i < result.second.first.size(); ++i) {
        if (i > 0) {
            cout << ",";
        }
        cout << result.second.first[i];
    }
    cout << "]\n";
    cout << "The search had " << result.second.second << " collisions\n";
    if(counts == result.second.first.size()){
       break;
    }
    else{
       cout << endl;
    }
}
}
