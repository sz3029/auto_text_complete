/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Filename: DictionaryTrieNode.hpp
 *  Author: Peiqi Fan, Shihui Zhu
 *  Userid: cs100sp19an, cs100sp19ck
 *  Description: The file contruct a DictionaryTrieNode structure
 *    which implements the main functionality of DictionaryTrie.
 *  Sources of help: Piazza
 */

#ifndef DICTIONARY_TRIE_NODE_HPP
#define DICTIONARY_TRIE_NODE_HPP

#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 */
class DictionaryTrieNode
{
    public:

    /* Create a new Dictionary Node that uses a Trie back end */
    DictionaryTrieNode(const char & d);

    // Fields
    DictionaryTrieNode * left;
    DictionaryTrieNode * middle;
    DictionaryTrieNode * right;
    DictionaryTrieNode * parent;
    char const data;   // the const char in this node.
    //bool end;  // whether the node is an end node of the word
    unsigned int freq; // frequncy of this word
};

struct MinHeap {
    bool operator()( const pair<int, string> & p1,
                     const pair<int, string> & p2) {
        // If freq equal, smaller alphabet comes first
        if (p1.first == p2.first) return p1.second.compare(p2.second);
        // else, compare freq
        return p1.first > p2.first;
    }
};
#endif // DICTIONARY_TRIE_H
