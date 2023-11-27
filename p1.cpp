#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string decodeMessage(string str, string encoding, string alpha){
    string total;
    total = "";
    for(int i = 0; i < str.length(); i++){
        if(isalpha(str[i])){
            total = total + alpha[encoding.find(str[i])];
        }
        else{
            total = total + str[i];
        }
    }

    return total;
}


int main(int argc, char* argv[]) {
  
  string fileMap = argv[1];
  string file1 = argv[2];
  string word = argv[3];

  string alpha;
  string encoding;
  ifstream file(fileMap);
  file >> alpha;
  file >> encoding;
 
  file.close();

  string message;
  string all = "";
  ifstream fileIn(file1);



  while (!fileIn.eof()) {
    getline(fileIn, message);
    
    all += message + "\n";
  }
  fileIn.close();
  
  string backupAlpha;
  string backupEncoding;
  int i = 0;
  int len = all.length() - word.length();
  
  for (i = 0; i < all.length(); i++) {                                    //Loops through all
    if (!isalpha(all[i]) && !isalpha(all[i+word.length()+1])) {  //Checks to see if word we are trying to find is contained in two nonalpha characters 
        int k = 0;           
        for (int j = i + 1; j < word.length() + i; j++) {       // Loops thorugh the "chosen word"
            if (isalpha(all[j])) {                              // checks if the character in the "chosen word" is alpha
                backupAlpha = alpha;
                backupEncoding = encoding;
                if (encoding.find(all[j]) == string::npos && alpha.find(word[j]) == string::npos) { //|| encoding.find(all[j]) == string::npos) {    // this checks if eachy letter of word is in the string "encoding"
                    encoding += all[j];                         // if the letter is not in encoding then it adds the letter to encoding
                    alpha += word[k];
                    k++;
                    if ((encoding.find(all[j]) == string::npos && alpha.find(word[j]) != string::npos) || (encoding.find(all[j]) != string::npos && encoding.find(alpha[j]) != alpha.find(word[k]))) {
                        //reset
                        alpha = backupAlpha;
                        encoding = backupEncoding;

                    }
                        /*if (encoding.find(all[j+1]) == string::npos || word[j+1] == alpha[encoding.find(all[j+1])]) {
                            encoding += all[j];
                            alpha += word[k];
                            //cout << all[j] << " all[j] " << endl;
                            //cout << word[k] << " word[k] k: " << k << endl;                      // adds the entire word (which is the "word" in input) to the alphabet
                            k++;
                        }*/

                    
                }
                


            }
        }

    }

  }
  //cout << alpha << " - alpha array" << endl; 
  //cout << encoding << "- encoding array" << endl; 
    // Objective is to find the word that does NOT ENCODE 
    // Only run big for loop until len(str) - len(word)
    // Loop through all to all.len - word.len and while looping through you will have if statement 
    //if all[i] and all[i+wordlen+1] is notAlpha 
    //ONce in if there is another for loop which goes from i + 1 to (<) i + wordlen
    // check if the word is alpha 
    // or one encoding letter can be there but it has to be mapped
    // INside for loop check if(alpha[j]) because use another variable and if its not inside encoding or
    // the letter can be there but it has to be mapped to word[j-i-1]
    
    


if (alpha.length() < 26) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < 26; i++){              //Try to find missing letter IF there is one
    //cout << "Missing: " << alpha.find(alphabet[i]) << endl;
    if (alpha.find(alphabet[i]) == -1) {
        alpha += alphabet[i];
    }
    if (encoding.find(alphabet[i]) == -1) {
        encoding += alphabet[i];
    }
  }
  //cout << alpha << " - alpha" << endl;
  //cout << encoding << " - encoding" << endl;

}

  string decodedMessage = decodeMessage(all,encoding,alpha);
  cout << decodedMessage << endl;

  return 0;
}