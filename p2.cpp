#include <iostream>
#include <cstring>
#include <fstream>
#include<string>

using namespace std;

void quicksort(string arr[], int left, int right) {
    int i = left, j = right;
    string temp;
    string pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j)
        quicksort(arr, left, j);
    if (i < right)
        quicksort(arr, i, right);
}

void Merge(int numbers[], int i, int j, int k) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (numbers[leftPos] < numbers[rightPos]) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j);
      MergeSort(numbers, j + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k);
   }
}

void removeDuplicatesStr(string arr[], int n) {
    // Create an array of bool to keep track of unique words
    bool unique[n];
    memset(unique, true, sizeof(unique));
    
    // Traverse the array
    for(int i = 0; i < n; i++) {
        // If the word is not already marked as duplicate, mark all its occurrences as duplicate and print it
        if(unique[i]) {
            if (!arr[i].empty()) {
            cout << arr[i] << endl;
            for(int j = i + 1; j < n; j++) {
                if(strcmp(arr[i].c_str(), arr[j].c_str()) == 0) {
                    unique[j] = false;
                }
            }
            }
        }
    }
}

void removeDuplicatesInt(int arr[], int n) {
    // Create an array of bool to keep track of unique integers
    bool unique[20000];
    memset(unique, false, sizeof(unique));
    
    // Traverse the array
    for(int i = 0; i < n; i++) {
        // If the integer is not already marked as duplicate, mark all its occurrences as duplicate and print it
        if(!unique[arr[i]]) {
            if (arr[i] != NULL) {
                cout << arr[i] << endl;
                unique[arr[i]] = true;
            }
        }
    }
}

int main(int argc, char* argv[]) {
   string mergeType;
   mergeType = argv[1];

   string fileIn1 = argv[2];
   ifstream FileI1;
   FileI1.open(fileIn1);

   string fileIn2 = argv[3];
   ifstream FileI2;
   FileI2.open(fileIn2); 

    if(mergeType[0] == 'i') {

        const int MAX_SIZE = 20000; // maximum array size
        int data1[MAX_SIZE], data2[MAX_SIZE]; // integer arrays to store data
        int size1 = 0, size2 = 0; // current sizes of data1 and data2

        int num;
        while (FileI1 >> num) {
                if (size1 < MAX_SIZE) { 
                data1[size1] = num;
                size1++;
            }
        }

        while (FileI2 >> num) {
            // Check if the integer is in data1
            bool found = false;
            for (int i = 0; i < size1; i++) {
                if (num == data1[i]) {
                    found = true;
                    break;
                }
            }
            if (found && size2 < MAX_SIZE) { 
                data2[size2] = num;
                size2++;
            }
        }

        /*int index = 0;
        for (int i=0; i<sizeof(data2)/sizeof(data2[i]); i++) {
        
        int j; 
        for (j=0; j<i; j++)
            if (data2[i] == data2[j])
                break;
      
        if (j == i)
            data2[index++] = data2[i];
   }*/

        int n = sizeof(data2)/sizeof(data2[0]);
        
        MergeSort(data2, 0, size2 - 1);
        removeDuplicatesInt(data2, n);
        // Print the contents of data2
        /*for (int i = 0; i < size2; i++) {
            if (data2[i] != NULL) {
                cout << data2[i] << endl;
            //}
            }
        }*/
    }
    
    else if (mergeType[0] == 's') {
        const int MAX_SIZE = 20000; 
        string data1[MAX_SIZE], data2[MAX_SIZE]; 
        int size1 = 0, size2 = 0; 
        

        
        
        // Read the strings from the first file into data1
        string word;
        while (FileI1 >> word) {
            if (size1 < MAX_SIZE) { 
                data1[size1] = word;
                size1++;
            }
        }
        
        while (FileI2 >> word) {
            // Check if the string is in data1
            bool found = false;
            for (int i = 0; i < size1; i++) {
                if (word == data1[i]) {
                    found = true;
                    break;
                }
            }
            // If the string is in both files, add it to data2
            if (found && size2 < MAX_SIZE) { // make sure we don't exceed the maximum array size
                data2[size2] = word;
                size2++;
            }
        }
        
        
        /*int index = 0;
        for (int i=0; i<sizeof(data2)/sizeof(data2[i]); i++) {
        
        int j; 
        for (j=0; j<i; j++)
            if (data2[i] == data2[j])
                break;
      
        if (j == i)
            data2[index++] = data2[i];
   }*/

    int n = sizeof(data2) / sizeof(data2[0]);
    

   // Print the contents of data2
    quicksort(data2, 0, size2 - 1);
    removeDuplicatesStr(data2, n);
        /*for (int i = 0; i < size2; i++) {
            if (data2[i].empty()) {
                
            }
            else {
                cout << data2[i] << endl;
            }
        }*/



    }
    // Close the files
    FileI1.close();
    FileI2.close();


   return 0;
}