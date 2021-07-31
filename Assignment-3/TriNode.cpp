/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: Node with 3 child ptr.
*/

#include "TriNode.h"

TriNode::TriNode()
{
    //Default Constuctor
}

TriNode::TriNode(const string &anItem)
{
    this->smallItem = anItem;
    this->largeItem = "";
    this->leftChildPtr = NULL;
    this->midChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->parent = NULL;
    this->tempRightmost = NULL;
    this->height = 1;
}

TriNode::TriNode(const string &anItem, TriNode *leftPtr, TriNode *midPtr, TriNode *rightPtr)
{
    this->smallItem = anItem;
    this->leftChildPtr = leftPtr;
    this->midChildPtr = midPtr;
    this->rightChildPtr = rightPtr;
}

TriNode::TriNode(const string &smallItem, const string &largeItem)
{
    this->smallItem = smallItem;
    this->largeItem = largeItem;
    this->leftChildPtr = NULL;
    this->midChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->parent = NULL;
    this->tempRightmost = NULL;
    this->height = 1;
}
