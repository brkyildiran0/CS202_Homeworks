/**
 * Title: Binary Search Trees
 * Author: Ömer Burak Yıldıran
 * ID: 21901425
 * Section: 1
 * Assignment: 2
 * Description: Basic Binary Node
 */

#include "BinaryNode.h"

//CONSTRUCTORS
BinaryNode::BinaryNode()
{
    //Default Constructor
}

BinaryNode::BinaryNode(const int &key, BinaryNode* leftPtr, BinaryNode* rightPtr)
{
    this->key = key;
    this->leftChildPtr = leftPtr;
    this->rightChildPtr = rightPtr;
}