/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: Binary Search Tree as a Dictionary
* Essentially the same as DictionarySearchTree.
*/

#ifndef _DICTIONARYBST_H
#define _DICTIONARYBST_H

#include <string>
#include "DictionarySearchTree.h"

using namespace std;

class DictionaryBST : public DictionarySearchTree
{
public:
    //CONSTRUCTOR & DESTRUCTOR
    /**
     * Destructor is inherited, there is no need to implement a new one.
     * Constructor calls the parent constructor in cpp file next to its arguements brackets.
     */
    DictionaryBST(string dictionaryFile);

    //METHODS
    /**
     * Since DictionarySearchTree is essentially a BST, we can simply inherit the DST and use it as it is.
     * No different methods are required, thus, this part is empty.
     */
};

#endif