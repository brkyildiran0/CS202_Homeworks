/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: Node with 3 child ptr.
*/

#ifndef _TRINODE_H
#define _TRINODE_H

#include <string>

using namespace std;

class TriNode
{
private:
    //Properties
    string smallItem;
    string largeItem; //Used for 2-3 Tree.
    string temp; //Used for 2-3 Tree.

    TriNode* leftChildPtr;
    TriNode* midChildPtr;
    TriNode* rightChildPtr; //Used for 2-3 Tree.
    TriNode* parent; //Used for 2-3 Tree.
    TriNode* tempRightmost; //Used for 2-3 Tree.

    int height; //Used for AVL.


    friend class DictionarySearchTree;
    friend class DictionaryAVLTree;
    friend class Dictionary23Tree;

public:
    //Constructors
    TriNode();
    TriNode(const string& anItem);
    TriNode(const string& smallItem, const string& largeItem);
    TriNode(const string& anItem, TriNode* leftPtr, TriNode* midPtr, TriNode* rightPtr);

    //Methods
    bool isLeaf() const;
    bool isTwoNode() const;
    bool isThreeNode() const;
};

#endif
