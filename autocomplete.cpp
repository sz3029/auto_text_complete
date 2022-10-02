/*
 * Filename: autocomplete.cpp
 * Author: Peiqi Fan, Shihui Zhu
 * Userid: cs100sp19an, cs100sp19ck
 * Description: The file output the most frequent labels for a pointer's k
 * nearest neighbors.
 * Sources of help: Piazza
 */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <string.h>

#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;

// global variables used in command line arguments
const int filenm = 1;

/** Check if a given data file is valid. Note that his does not 
 * check if the data file is in correct format
 */
bool fileValid(const char * fileName) {

  ifstream in;
  in.open(fileName, ios::binary);

  // Check if input file was actually opened
  if(!in.is_open()) {
    cout<< "Invalid input file. No file was opened. Please try again.\n";
    in.close();
    return false;
  }

  // Check for empty file
  in.seekg(0, ios_base::end);
  int len = (int) in.tellg();
  if(len == 0) {
    cout << "The file is empty. \n";
    in.close();
    return false;
  }

  in.close();
  return true;
}


/**
 * IMPORTANT! You should use the following lines of code to match the correct output:
 * 
 * cout << "This program needs exactly one argument!" << endl;
 * cout << "Reading file: " << file << endl;
 * cout << "Enter a prefix/pattern to search for:" << endl;
 * cout << "Enter a number of completions:" << endl;
 * cout << completion << endl;
 * cout << "Continue? (y/n)" << endl;
 * 
 * arg 1 - Input file name (in format like freq_dict.txt)
 */
int main(int argc, char** argv){

  //  error mesage if there is extra argument
  if (argc != 2){
    cout << "This program needs exactly one argument!" << endl;
    return -1;
  }

  // stop and return -1 if the input file is not valid
  if (!fileValid(argv[filenm])){
    return -1;
  }

  // message indicate reading files
  cout << "Reading file: " << argv[filenm] << endl;

  // Read the words from the file into a trie
  DictionaryTrie * tree = new DictionaryTrie();

  // open the in stream
  ifstream in;
  in.open(argv[filenm], ios::binary);

  // load words into the trie
  Utils::load_dict(*tree, in);

  // variables of input prefix and num of completions
  string input;
  string cont;
  string nComp;
  int numComp;
  char underscore = '_';

  // using loop to parse the input
  while(1){
    // input the prefix
    cout << "Enter a prefix/pattern to search for:" << endl;
    getline(cin, input);

    // input the number of completions
    cout << "Enter a number of completions:" << endl;
    getline(cin, nComp);
    numComp = Utils::stripFrequency(nComp);

    // find the completions if input and numComp are valid
    if (input.compare("") && numComp) {
      std::vector<string> prediction = vector<string>();
      if (input.find(underscore) != std::string::npos){
        prediction = tree->predictUnderscore(input, numComp);
      }
      else {
        prediction = tree->predictCompletions(input, numComp);
      }
      // if prediction exists
      if (!prediction.empty()){
        // print out the completions
        for (auto i : prediction){
          cout << i << endl;
        }
      }
    } 
    // input whether to continue or not
    cout << "Continue? (y/n)" << endl;
    getline(cin, cont);

    // stop reading input if input is not "y"
    if (cont.compare("y")){
      break;
    }
  }
  // close the file stream and delete the trie object
  in.close();
  delete tree;
  return 0;
}
