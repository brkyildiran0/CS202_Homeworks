/**
 * Title: Binary Search Trees
 * Author: Ömer Burak Yıldıran
 * ID: 21901425
 * Section: 1
 * Assignment: 2
 * Description: Header file for BinarySearchTree
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include "BinaryNode.h"

class BinarySearchTree
{
public:
    //CONSTRUCTOR & DESTRUCTOR
    BinarySearchTree();
    ~BinarySearchTree();

    //METHODS
    bool insertItem(const int key);
    bool deleteItem(const int key);
    BinaryNode* retrieveItem(const int key);
    void inorderTraversal(int*& array, int& length);
    int getHeight();
    int numHeightBalanced();
    int numNodesDeeper(int level);

    //Helper Methods
    bool isEmpty() const;
    int getNumberOfNodes();

private:
    BinaryNode* rootPtr;

    /**
     * A combination of "search" and "insertItem" pseudocode given at the textbook for Binary Trees as a general guideline.
     * Modified to work for Binary Search Trees. No other sources used than the textbook.
     * @param treePtr, root of the tree to be inserted the item.
     * @param item, value that is going to be inserted.
     * @param success, result of the operation.
     */
    void searchAndInsert(BinaryNode* &treePtr, const int &item, bool &success);

    /**
     * Removes the given value.
     * Modified to work for Binary Search Trees. No other sources used than the textbook.
     * @param subTreePtr, root of the tree that will get the key value removed, if exists.
     * @param target, value that is going to be removed.
     * @param success, result of the operation.
     */
    void removeValue(BinaryNode* &subTreePtr, int target, bool &success);

    /**
     * Deletes a desired node from the BinarySearchTree while also rearranging the node connections back.
     * @param nodePtr, the node to be deleted.
     */
    void removeNode(BinaryNode* &nodePtr);

    /**
     * Saves the value of inorder successor, then proceeds to delete the node that held it.
     * @param nodePtr, the pointer of the right child of the particular node given.
     * @param inorderSuccessor, inorder successor value will be stored here.
     */
    void removeLeftmostNode(BinaryNode* &nodePtr, int &inorderSuccessor);

    /**
     * Uses the algorithm given in the textbook to calculate the height of the given tree.
     * @param treePtr, root of the point to be calculated.
     * @return, height of the tree.
     */
    int getHeightHelper(BinaryNode *treePtr) const;

    /**
     * Traverses list with inorder manner, and increments int value by 1 for each node.
     * @param treePtr, root of the tree.
     * @param itemCount, amount of items.
     */
    void totalNumberHelper(BinaryNode* &treePtr, int &itemCount);

    /**
     * Searches whether given value exists in the tree.
     * @param treePtr, root of the tree to be searched.
     * @param key, the value that is being searched.
     * @param result, result of the search.
     */
    void containsHelper(BinaryNode *&treePtr, int key, BinaryNode* &result);

    /**
     * Algorithm as given in the textbook, inorder traversal of BST.
     * @param treePtr, root of the tree to be traversed.
     */
    void inorder(BinaryNode* &treePtr, int*& array, int* currentIndex);

    /**
     * Helper method for balanced node finder.
     * @param treePtr, root of the tree to be searched.
     * @param totalBalancedNodes, is the total amount of balanced nodes in given BST.
     */
    void numHeightBalancedHelper(BinaryNode* &treePtr, int &totalBalancedNodes);

    /**
     * Helper method for deeper node finder.
     * @param treePtr, root of the tree to be searched.
     * @param givenLevel, comparison made with this value.
     * @param currentLevel, current level of the node the function is at.
     * @param totalNodes, amount of nodes found that is in a deeper level than the given level.
     */
    void numNodesDeeperHelper(BinaryNode* &treePtr, int givenLevel, int& currentLevel, int& totalNodes);

    /**
     * Used at destructor, to free heap memory and prevent leak.
     * @param treePtr, root of the tree to be deleted.
     */
    void destroyTree(BinaryNode* &treePtr);
};

#endif
