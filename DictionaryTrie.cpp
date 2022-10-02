/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Filename: DictionaryTrie.cpp
 *  Author: Peiqi Fan, Shihui Zhu
 *  Userid: cs100sp19an, cs100sp19ck
 *  Description: The file contruct a DictionaryTrie structure
 *    which implements the main functionality of autocompleter
 *  Sources of help: Piazza
 */


#include "DictionaryTrie.hpp"
/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() {
    root = nullptr;
    numCompletions = threshold = 0;
}

/**
 * Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string). This might be useful for testing
 * when you want to test a certain case, but don't want to
 * write out a specific word 300 times.
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{

    if ( word.empty() ) return false;
    // If root is null, insert the letter directly
    unsigned int i = 0;
    if ( root == 0 ) {
        root = new DictionaryTrieNode(word[0]);
        if (word.size() == 1) root->freq = freq;
    }
    // Create a current Node
    DictionaryTrieNode * curr = root;

    // Insert the rest of the word in the TST
    while( i < word.size() ) {
        // left child
        if ( word[i] < curr->data ) {
            // Go to the left child if there exists one
            if ( curr->left != 0 ) {
                curr = curr->left;
            }
            // Create a new left child
            else {
                curr->left = new DictionaryTrieNode(word[i]);
                i++;
                curr->left->parent = curr;
                curr = curr->left;
                unsigned int j = i;

                // Iterate the rest of the word, insert into TST
                while ( j < word.size() ) {
                    curr->middle = new DictionaryTrieNode(word[j]);
                    curr->middle->parent = curr;
                    curr = curr->middle;
                    j++;
                }
                curr->freq = freq;
                break;
            }
        } else if ( word[i] > curr->data ) {
            // right child
            if ( curr->right != 0 ) {
                curr = curr->right;
            }
            else {
                curr->right = new DictionaryTrieNode(word[i]);
                i++;
                curr->right->parent = curr;
                curr = curr->right;
                unsigned int j = i;
                while ( j < word.size() ) {
                    curr->middle = new DictionaryTrieNode(word[j]);
                    curr->middle->parent = curr;
                    curr = curr->middle;
                    j++;
                }
                curr->freq = freq;
                break;
            }
        } else {
            // word[i] equals to letter
            // if this is the last character, break the loop
            if ( i == word.size()-1 ) {
                // label node as a word-node
                if ( curr->freq != 0 ) return false;
                else {
                    curr->freq = freq;
                    return true;
                }
            } else {
                // If it is not, go to the next middle character
                if ( curr->middle != 0 ) {
                    curr = curr->middle;
                    i++;
                } else {
                    unsigned int j = ++i;
                    // iterate letter over the remaining letters of key
                    while ( j < word.size() ){
                        curr->middle = new DictionaryTrieNode(word[j]);
                        curr->middle->parent = curr;
                        curr = curr->middle;
                        j++;
                    }
                    curr->freq = freq;
                    break;
                }
            }
        }
    }
    return true;
}


/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    if ( word.empty() || root == 0 ) return false;

    DictionaryTrieNode * curr = root;
    unsigned int i = 0;
    while( i < word.size() ) {
        if ( word[i] < curr->data ) {
            if ( curr->left != 0 ) {
                curr = curr->left;
            } else {
                return false;
            }
        } else if ( word[i] > curr->data ) {
             if ( curr->right != 0 ) {
                curr = curr->right;
            } else {
                return false;
            }
        } else {
            if ( i == word.size()-1 && curr->freq != 0 ) {
                return true;
            } else {
                if ( curr->middle != 0 ) {
                    curr = curr->middle;
                    i++;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}


/*
 * Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix,
    unsigned int num_completions)
{
    // If no prefix is entered
    vector<std::string> pred;
    if ( prefix.empty() || root == 0 ) return pred;
    // find the node contains the last node of pointer
    numCompletions = num_completions;
    threshold = 0;
    DictionaryTrieNode * curr = root;
    unsigned int i = 0;
    while( i < prefix.size() ) {
        if ( prefix[i] < curr->data ) {
            if ( curr->left != 0 ) {
                curr = curr->left;
            } else return pred;
        } else if ( prefix[i] > curr->data ) {
             if ( curr->right != 0 ) {
                curr = curr->right;
            } else return pred;
        } else {
            if ( i == prefix.size()-1 ) {
                break;
            } else {
                if ( curr->middle != 0 ) {
                    curr = curr->middle;
                    i++;
                } else return pred;
            }
        }
    }
    // add the prefix to predict vector if it is a word
    if (curr->freq) predict.push(make_pair(curr->freq, prefix));

    // transverse the middle children of the current node
    tranversal(curr->middle, prefix);
    unsigned int size = predict.size();

    for ( unsigned int i = 0; i < num_completions && i < size; i++ ) {
        pred.push_back(predict.top().second);
        predict.pop();
    }
    // Revert the vector so the words with most frequency shows up first
    std::reverse(pred.begin(), pred.end());
    return pred;
}

/* Return up to num_completions of the most frequent completions
 * of the pattern, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The pattern itself might be included in the returned words if the pattern
 * is a word (and is among the num_completions most frequent completions
 * of the pattern)
 */
std::vector<string> DictionaryTrie::predictUnderscore(std::string pattern,
    unsigned int num_completions)
{
    return vector<string>();
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
    deleteAll(root);
}

/** delete all the node, helper of destructor
 */
void DictionaryTrie::deleteAll(DictionaryTrieNode * root)
{
    if ( root == nullptr ) {
        return;
    }
    deleteAll( root->left );
    deleteAll( root->right );
    deleteAll( root->middle );
    delete root;
}

void DictionaryTrie::tranversal(DictionaryTrieNode * node, std::string prefix)
{
    if (node) {
        tranversal(node->left, prefix);
        if ( node->freq != 0 ) {
            if ( predict.size() < numCompletions ) {
                predict.push( make_pair(node->freq, prefix + node->data) );
            } else {
                //Update the node
                updateQueue(node, prefix);
            }
        }
        tranversal(node->middle, prefix + node->data);
        tranversal(node->right, prefix);
    }
}

void DictionaryTrie::updateQueue( DictionaryTrieNode * node, string prefix ) {
    pair<int, string> temp = predict.top();
    threshold = temp.first;
    if ( node->freq > threshold ) {
       predict.pop();
       predict.push( make_pair(node->freq, prefix + node->data) );
    } else if ( node->freq == threshold ) {
        string word1 = prefix + node->data;
        // if two completions have same frequency, pop out the greater
        //   alphabetical value, pick the smaller one
        if ( word1.compare(temp.second) < 0 ) {
            predict.pop();
            predict.push( make_pair(node->freq, prefix + node->data) );
        }
    }
}
