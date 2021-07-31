/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: AVL Tree Implemented with TriNode and inherited from DictionarySearchTree
*/

#include "DictionaryAVLTree.h"

DictionaryAVLTree::DictionaryAVLTree(string dictionaryFile)
{
    //Open the input file
    ifstream file;
    file.open(dictionaryFile);
    string line;

    //Construct the tree
    while (getline(file, line))
    {
        DictionaryAVLTree::insert(line);
    }
}

void DictionaryAVLTree::insert(string word)
{
    DictionaryAVLTree::insertHelper(word, root);
}

TriNode* DictionaryAVLTree::insertHelper(const string &word, TriNode *&rootNode)
{
    //Usual BST insertion part.
    if (rootNode == NULL)
    {
        rootNode = new TriNode(word);
        return rootNode;
    }
    if (word < rootNode->smallItem)
    {
        rootNode->leftChildPtr = insertHelper(word, rootNode->leftChildPtr);
    }
    else if (word > rootNode->smallItem)
    {
        rootNode->midChildPtr = insertHelper(word, rootNode->midChildPtr);
    }
    else
    {
        return rootNode;
    }

    //AVL Balancing with rotation (if required)
    //Step 1. Update the height of added node and initialize balancefactor of it
    rootNode->height = max(height(rootNode->leftChildPtr), height(rootNode->midChildPtr)) + 1;
    int balanceFactor = getBalanceFactor(rootNode);
    //Step2. Analyze cases

    //Case 1 & 2. Balance Factor is > 0, thus check the case and act accordingly:
    //(i)Apply single right rotation , (ii)Apply double LR rotation.
    if (balanceFactor > 1)
    {
        if (word < rootNode->leftChildPtr->smallItem) //(i)
        {
            rootNode = rightRotate(rootNode);
        }
        else if (word > rootNode->leftChildPtr->smallItem) //(ii)
        {
            rootNode->leftChildPtr = leftRotate(rootNode->leftChildPtr);
            rootNode = rightRotate(rootNode);
        }
    }

    //Case 3 & 4. Balance Factor is < 0, thus check the case and act accordingly:i
    //(i)Apply single left rotation, (ii)Apply double RL rotation.
    if (balanceFactor < -1)
    {
        if (word > rootNode->midChildPtr->smallItem) //(i)
        {
            rootNode = leftRotate(rootNode);
        }
        else if (word < rootNode->midChildPtr->smallItem) //(ii)
        {
            rootNode->midChildPtr = rightRotate(rootNode->midChildPtr);
            rootNode = leftRotate(rootNode);
        }
    }
    return rootNode;
}

int DictionaryAVLTree::max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int DictionaryAVLTree::height(TriNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return max(height(node->leftChildPtr), height(node->midChildPtr)) + 1;
    }
}

TriNode* DictionaryAVLTree::rightRotate(TriNode *rotateNode)
{
    TriNode* NodeA = rotateNode->leftChildPtr;
    TriNode* NodeB = NodeA->midChildPtr;

    NodeA->midChildPtr = rotateNode;
    rotateNode->leftChildPtr = NodeB;

    rotateNode->height = max(height(rotateNode->leftChildPtr), height(rotateNode->midChildPtr)) + 1;
    NodeA->height = max(height(NodeA->leftChildPtr), height(NodeA->midChildPtr)) + 1;

    return NodeA;
}

TriNode* DictionaryAVLTree::leftRotate(TriNode *rotateNode)
{
    TriNode* NodeA = rotateNode->midChildPtr;
    TriNode* NodeB = NodeA->leftChildPtr;

    NodeA->leftChildPtr = rotateNode;
    rotateNode->midChildPtr = NodeB;

    rotateNode->height = max(height(rotateNode->leftChildPtr), height(rotateNode->midChildPtr)) + 1;
    NodeA->height = max(height(NodeA->leftChildPtr), height(NodeA->midChildPtr)) + 1;

    return NodeA;
}

int DictionaryAVLTree::getBalanceFactor(TriNode *node)
{
    if (node == NULL) return 0;
    return height(node->leftChildPtr) - height(node->midChildPtr);
}