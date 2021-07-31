/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: 2-3 Tree implemented with TriNode and inherited from DictionarySearchTree
*/

#ifndef _DICTIONARY23TREE_H
#define _DICTIONARY23TREE_H

#include <string>
#include <fstream>
#include <iostream>
#include "TriNode.h"
#include "DictionarySearchTree.h"

using namespace std;

class Dictionary23Tree : public DictionarySearchTree
{
public:
    /**
     * Destructor is inherited, there is no need to implement a new one.
     * Constructor would be slightly different due to the nature of 2-3 trees.
     */
     Dictionary23Tree(string dictionaryFile);
     void insert(string word) override;
     void search(string word, int& numComparisons, bool& found) const override;
     void search(string queryFile, string outputFile) const override;

private:
    void split(TriNode*& rootNode);
    void insertHelper(string word, TriNode*& rootNode);
    void searchHelper(string word, int& numCompares, bool& found, TriNode* rootNode) const;

};

#endif