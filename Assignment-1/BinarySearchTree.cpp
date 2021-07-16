/**
 * Title: Binary Search Trees
 * Author: Ömer Burak Yıldıran
 * ID: 21901425
 * Section: 1
 * Assignment: 2
 * Description: CPP file for BinarySearchTree
 */

#include "BinarySearchTree.h"
#include <iostream>


using namespace std;

//######################################## CONSTRUCTOR & DESTRUCTOR ########################################
BinarySearchTree::BinarySearchTree()
{
    rootPtr = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
    destroyTree(rootPtr);
}

//######################################## METHODS ########################################
bool BinarySearchTree::isEmpty() const
{
    return (rootPtr == NULL);
}

int BinarySearchTree::getHeight()
{
    return getHeightHelper(rootPtr);
}

int BinarySearchTree::getNumberOfNodes()
{
    int totalAmount = 0;
    totalNumberHelper(rootPtr, totalAmount);
    return totalAmount;
}

bool BinarySearchTree::insertItem(const int key)
{
    bool result = false;
    searchAndInsert(rootPtr, key, result);
    return result;
}

bool BinarySearchTree::deleteItem(const int key)
{
    bool result = false;
    removeValue(rootPtr, key, result);
    return result;
}

BinaryNode* BinarySearchTree::retrieveItem(const int key)
{
    BinaryNode* result = NULL;
    containsHelper(rootPtr, key, result);
    return result;
}


void BinarySearchTree::inorderTraversal(int*& array, int& length)
{
    length = getNumberOfNodes();
    array = new int[length];
    int startIndex = 0;
    inorder(rootPtr, array, &startIndex);
}

int BinarySearchTree::numHeightBalanced()
{
    int totalBalancedNodes = 0;
    numHeightBalancedHelper(rootPtr, totalBalancedNodes);
    return totalBalancedNodes;
}

int BinarySearchTree::numNodesDeeper(int level)
{
    int totalDeeperNodes = 0;
    int startingLevel = 1;
    numNodesDeeperHelper(rootPtr, level, startingLevel, totalDeeperNodes);
    return totalDeeperNodes;
}

//######################################## HELPER METHODS ########################################
void BinarySearchTree::searchAndInsert(BinaryNode* &treePtr, const int &item, bool &success)
{
    if (treePtr == NULL)
    {
        treePtr = new BinaryNode(item, NULL, NULL);
        success = true;
    }
    else if (item < treePtr->key)
    {
        searchAndInsert(treePtr->leftChildPtr, item, success);
    }
    else if (item > treePtr->key)
    {
        searchAndInsert(treePtr->rightChildPtr, item, success);
    }
    else if (item == treePtr->key)
    {
        success = false;
    }
}

void BinarySearchTree::removeValue(BinaryNode* &subTreePtr, int target, bool &success)
{
    if (subTreePtr != NULL)
    {
        if (target == subTreePtr->key)
        {
            removeNode(subTreePtr);
            success = true;
        }
        else if (target < subTreePtr->key)
        {
            removeValue(subTreePtr->leftChildPtr, target, success);
        }
        else
        {
            removeValue(subTreePtr->rightChildPtr, target, success);
        }
    }
}

void BinarySearchTree::removeNode(BinaryNode* &nodePtr)
{
    //Case 1: Node is a leaf
    if (nodePtr->leftChildPtr == NULL && nodePtr->rightChildPtr == NULL)
    {
        delete nodePtr;
        nodePtr = NULL;
    }
        //Cases 2: Node has only 1 child
    else if (nodePtr->rightChildPtr == NULL)
    {
        BinaryNode* delPtr = nodePtr;
        nodePtr = nodePtr->leftChildPtr;
        delPtr->leftChildPtr = NULL;
        delete delPtr;
    }
    else if (nodePtr->leftChildPtr == NULL)
    {
        BinaryNode* delPtr = nodePtr;
        nodePtr = nodePtr->rightChildPtr;
        delPtr->rightChildPtr = NULL;
        delete delPtr;
    }
        //Case 3: Node has both children
    else
    {
        int replacementItem; //swap with the inorder successor and delete
        removeLeftmostNode(nodePtr->rightChildPtr, replacementItem);
        nodePtr->key = replacementItem;
    }
}

void BinarySearchTree::removeLeftmostNode(BinaryNode* &nodePtr, int &inorderSuccessor)
{
    if (nodePtr->leftChildPtr == NULL)
    {
        inorderSuccessor = nodePtr->key;
        removeNode(nodePtr);
    }
    else
    {
        removeLeftmostNode(nodePtr->leftChildPtr, inorderSuccessor);
    }
}

void BinarySearchTree::inorder(BinaryNode* &treePtr, int*& array, int* currentIndex)
{
    if (treePtr != NULL)
    {
        inorder(treePtr->leftChildPtr, array, currentIndex);
        array[*currentIndex] = treePtr->key;
        (*currentIndex)++;
        inorder(treePtr->rightChildPtr, array, currentIndex);
    }
}

void BinarySearchTree::containsHelper(BinaryNode *&treePtr, int key, BinaryNode* &result)
{
    if (treePtr == NULL)
    {
        result = NULL;
        return;
    }
    if (treePtr->key == key)
    {
        result = treePtr;
        return;
    }
    else if (treePtr->key > key)
    {
        containsHelper(treePtr->leftChildPtr, key, result);
    }
    else
    {
        containsHelper(treePtr->rightChildPtr, key, result);
    }
}

int BinarySearchTree::getHeightHelper(BinaryNode *treePtr) const
{
    if (treePtr == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + max(getHeightHelper(treePtr->leftChildPtr), getHeightHelper(treePtr->rightChildPtr));
    }
}

void BinarySearchTree::totalNumberHelper(BinaryNode* &treePtr, int &itemCount)
{
    if (treePtr != NULL)
    {
        totalNumberHelper(treePtr->leftChildPtr, itemCount);
        itemCount++;
        totalNumberHelper(treePtr->rightChildPtr, itemCount);
    }
}

void BinarySearchTree::numHeightBalancedHelper(BinaryNode *&treePtr, int &totalBalancedNodes)
{
    if (treePtr == NULL) return;

    int leftSubTreeHeight = 0;
    int rightSubTreeHeight = 0;

    leftSubTreeHeight = getHeightHelper(treePtr->leftChildPtr);
    rightSubTreeHeight = getHeightHelper(treePtr->rightChildPtr);

    if (abs(leftSubTreeHeight - rightSubTreeHeight) <= 1)
    {
        totalBalancedNodes++;
    }

    numHeightBalancedHelper(treePtr->leftChildPtr, totalBalancedNodes);
    numHeightBalancedHelper(treePtr->rightChildPtr, totalBalancedNodes);
}

void BinarySearchTree::numNodesDeeperHelper(BinaryNode *&treePtr, int givenLevel, int &currentLevel, int &totalNodes)
{
    if (treePtr == NULL) return;

    if (currentLevel >= givenLevel) totalNodes++;

    currentLevel++;

    numNodesDeeperHelper(treePtr->leftChildPtr, givenLevel, currentLevel, totalNodes);
    numNodesDeeperHelper(treePtr->rightChildPtr, givenLevel, currentLevel, totalNodes);
}

void BinarySearchTree::destroyTree(BinaryNode* &treePtr)
{
    //Deleting all nodes of the tree in a postorder traversal manner.
    if (treePtr == NULL)
    {
        return;
    } else
    {
        destroyTree(treePtr->leftChildPtr);
        destroyTree(treePtr->rightChildPtr);
        delete treePtr;
    }
}


