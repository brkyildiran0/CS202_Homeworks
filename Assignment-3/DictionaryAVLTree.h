/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: AVL Tree Implemented with TriNode and inherited from DictionarySearchTree
*/

#ifndef _DICTIONARYAVLTREE_H
#define _DICTIONARYAVLTREE_H

#include <string>
#include <fstream>
#include <iostream>
#include "TriNode.h"
#include "DictionarySearchTree.h"

using namespace std;

class DictionaryAVLTree : public DictionarySearchTree
{
public:
    //CONSTRUCTOR & DESTRUCTOR
    /**
     * Destructor is inherited, there is no need to implement a new one.
     * * Constructor calls the parent constructor in cpp file next to its arguments brackets.
     */
    DictionaryAVLTree(string dictionaryFile);
    void insert(string word) override;

private:
    /**
     * Handles the insertion process of AVL tree.
     * @param word, word to be inserted to AVL Tree.
     * @param rootNode, root of the AVL Tree.
     * @return, inserted node.
     */
    TriNode* insertHelper(const string& word, TriNode*& rootNode);

    /**
     * Used to find the greater value during comparisons.
     * @param a, first value.
     * @param b, second value.
     * @return, greater of either a or b.
     */
    int max(int a, int b);

    /**
     * Calculates the height of node "node"
     * @param node, the node to get its height calculated.
     * @return, height of "node".
     */
    int height(TriNode* node);

    /**
     * Performs RIGHT rotation on any given subtree following AVL guidelines.
     * USED THE EXACT "ALGORITHM"/"PSEUDOCODE" IN THE TEXTBOOK.
     * @param rotateNode, rotating node that caused imbalance.
     * @return, position after rotation.
     */
    TriNode* rightRotate(TriNode* rotateNode);

    /**
     * Performs LEFT rotation on any given subtree following AVL guidelines.
     * USED THE EXACT "ALGORITHM"/"PSEUDOCODE" IN THE TEXTBOOK.
     * @param rotateNode, rotating node that caused imbalance.
     * @return, position after rotation.
     */
    TriNode* leftRotate(TriNode* rotateNode);

    /**
     * Gets the balance factor by calculating the difference between two subtrees of any node.
     * @param node, any node in AVL Tree.
     * @return, less than -1 if tree if right heavy, greater than 1 if tree is left heavy.
     */
    int getBalanceFactor(TriNode* node);
};

#endif