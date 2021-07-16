/**
 * Title: Binary Search Trees
 * Author: Ömer Burak Yıldıran
 * ID: 21901425
 * Section: 1
 * Assignment: 2
 * Description: Header file for BinaryNode
 */

class BinaryNode
{
    //To be able to reach private properties of BinaryNode from BST, we must define these two classes as "friend classes"
    friend class BinarySearchTree;

private:
    //Constructors
    BinaryNode();
    BinaryNode(const int &key, BinaryNode* leftPtr, BinaryNode* rightPtr);

    //Properties
    int key;
    BinaryNode* leftChildPtr;
    BinaryNode* rightChildPtr;
};