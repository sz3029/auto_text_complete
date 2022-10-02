/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Filename: DictionaryTrieNode.cpp
 *  Author: Peiqi Fan, Shihui Zhu
 *  Userid: cs100sp19an, cs100sp19ck
 *  Description: The file contruct a DictionaryTrieNode structure
 *    which implements the main functionality of DictionaryTrie.
 *  Sources of help: Piazza
 */

#include "DictionaryTrieNode.hpp"
using namespace std;
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 */

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrieNode::DictionaryTrieNode(const char & d) : data(d) {
        freq = 0;
        left = right = middle = parent = 0;
}

/** Overload operator<< to print a DictionaryTrieNode fields to an ostream */
ostream & operator<<(ostream& stm, const DictionaryTrieNode & n) {
 stm << '[';
 stm << setw(10) << &n;                 // address of the BSTNode
 stm << "; p:" << setw(10) << n.parent; // address of its parent
 stm << "; l:" << setw(10) << n.left;   // address of its left child
 stm << "; r:" << setw(10) << n.right;  // address of its right child
 stm << "; d:" << n.data;               // its data field
 stm << ']';
 return stm;
 }
