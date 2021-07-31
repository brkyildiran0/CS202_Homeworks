/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: Interface for other tree implementations.
* Designed as a basic BST in essence.
*/

#ifndef _DICTIONARYSEARCHTREE_H
#define _DICTIONARYSEARCHTREE_H

#include <string>
#include <fstream>
#include <iostream>
#include "TriNode.h"

using namespace std;

class DictionarySearchTree
{
public:
    //Constructor & Destructor
    DictionarySearchTree();
    DictionarySearchTree(string dictionaryFile);
    virtual ~DictionarySearchTree();

    //Inserts the given word into the dictionary
    virtual void insert(string word);

    //Searches the given word in the dictionary, and returns the number
    //of comparisons made and whether the word is found or not
    virtual void search(string word, int& numComparisons, bool& found) const;

    //Searches all words in the query file in the dictionary, and
    //summarizes the results in the output file
    virtual void search(string queryFile, string outputFile) const;

private:
    //Helper Methods
    TriNode* insertHelper(const string& word, TriNode*& rootNode);
    void searchHelper(string word, int& numCompares, bool& found, TriNode* rootNode) const;
    void destroyTree(TriNode* rootNode);

protected:
    //Properties
    TriNode* root;
};

#endif