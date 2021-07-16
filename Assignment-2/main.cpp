/**
 * Title: Binary Search Trees
 * Author: Ömer Burak Yıldıran
 * ID: 21901425
 * Section: 1
 * Assignment: 2
 * Description: Contains heightAnalysis() and main().
 * ADDITIONAL NOTES for TA: I included algorithm/ctime/random libraries just for shuffles and rand() seeds, which seems to be allowed.
 */

#include <iostream>
#include <ctime> //Used to seed rand() function.
#include <algorithm> //Used to shuffle the array.
#include <random> //Used to shuffle the array.
#include "BinarySearchTree.h"
#include "auxArrayFunctions.h"

using namespace std;

void heightAnalysis()
{
    //Create random number array
    int randomNumbers[20000];

    //Seed rand() function
    srand(time(0));

    for (int & randomNumber : randomNumbers)
    {
        randomNumber = rand();
    }

    //Create empty BST
    BinarySearchTree BST;

    //Insert elements and output when necessary
    for (int i = 0; i < 20000; ++i)
    {
        BST.insertItem(randomNumbers[i]);

        if (i % 1000 == 0)
        {
            cout << "After " << i << " insertions, height of the BST is: " << BST.getHeight() << endl;
        }
    }
    cout << "After 20000 insertions, height of the BST is: " << BST.getHeight() << endl;

    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    //Shuffle the array
    unsigned rnd = 0;
    shuffle(&randomNumbers[0], &randomNumbers[20000], default_random_engine(rnd));

    //Delete elements and output when necessary
    for (int i = 0; i < 20000; ++i)
    {
        BST.deleteItem(randomNumbers[i]);

        if (i % 1000 == 0)
        {
            cout << "After " << i << " removals, height of the BST is: " << BST.getHeight() << endl;
        }
    }
    cout << "After 20000 removals, height of the BST is: " << BST.getHeight() << endl;

}

int main()
{
    //Tree initialize
    BinarySearchTree BST;

    //Given insert orders
    BST.insertItem(5);
    BST.insertItem(3);
    BST.insertItem(9);
    BST.insertItem(4);
    BST.insertItem(8);
    BST.insertItem(6);
    BST.insertItem(1);
    BST.insertItem(7);
    BST.insertItem(2);
    BST.insertItem(10);

    //Given delete orders
    BST.deleteItem(1);
    BST.deleteItem(5);
    BST.deleteItem(9);
    BST.deleteItem(10);
    BST.deleteItem(7);

    //Perform inorder traversal to tree
    int* tree = 0; //This is just a null pointer declaration for function below, the dynamic array alloc occurs within the function.
    int length = 0;
    BST.inorderTraversal(tree, length);

    //Display the contents of the tree
    cout << "BST after given operations : [";
    for (int i = 0; i < length; ++i)
    {
        cout << " " << tree[i];
    }
    cout << " ]" << endl;

    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    heightAnalysis();
    delete [] tree;


    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    //QUESTION 3 STARTS BELOW
    int* arr1 = new int[20000];
    int* arr2 = new int[20000];
    int* arr3 = new int[20000];

    //Experiment, diversities with 10, 100, 1000 of elements between different BSTs.
    createNearlySortedArrays(arr1, 20000, 10);
    createNearlySortedArrays(arr2, 20000, 100);
    createNearlySortedArrays(arr3, 20000, 1000);
    BinarySearchTree BST1, BST2, BST3;

    for (int i = 0; i < 20000; ++i)
    {
        BST1.insertItem(arr1[i]);
        BST2.insertItem(arr2[i]);
        BST3.insertItem(arr3[i]);

        if (i % 1000 == 0)
        {
            cout << "After " << i << " insertions, height of the BST1 is: " << BST1.getHeight() << endl;
            cout << "After " << i << " insertions, height of the BST2 is: " << BST2.getHeight() << endl;
            cout << "After " << i << " insertions, height of the BST3 is: " << BST3.getHeight() << endl;

            cout << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << endl;
        }
    }

    cout << "After " << "20000" << " insertions, height of the BST1 is: " << BST1.getHeight() << endl;
    cout << "After " << "20000" << " insertions, height of the BST2 is: " << BST2.getHeight() << endl;
    cout << "After " << "20000" << " insertions, height of the BST3 is: " << BST3.getHeight() << endl;

    delete [] arr1;
    delete [] arr2;
    delete [] arr3;

    return 0;
}