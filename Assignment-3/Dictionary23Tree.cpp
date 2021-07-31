/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: 2-3 Tree implemented with TriNode and inherited from DictionarySearchTree
*/

#include <iomanip> //Included to tidy output by using setw(int)
#include "Dictionary23Tree.h"

Dictionary23Tree::Dictionary23Tree(string dictionaryFile)
{
    //Open the input file
    ifstream file;
    file.open(dictionaryFile);
    string line;

    //Construct the tree
    while (getline(file, line))
    {
        Dictionary23Tree::insert(line);
    }
}

void Dictionary23Tree::search(string word, int &numComparisons, bool &found) const
{
    searchHelper(word, numComparisons, found, root);
}

void Dictionary23Tree::insert(string word)
{
    insertHelper(word, root);
}

void Dictionary23Tree::searchHelper(string word, int &numCompares, bool &found, TriNode *rootNode) const
{
    //Case 1. Tree is empty
    if (rootNode == NULL)
    {
        found = false;
        return;
    }

    //Case 2. Node is root
    else if (word == rootNode->smallItem)
    {
        numCompares++;
        found = true;
        return;
    }
    else if (word == rootNode->largeItem)
    {
        numCompares = numCompares + 2;
        found = true;
        return;
    }

    //Case 3. Node is 3-node
    else if (rootNode->largeItem != "")
    {
        if (word < rootNode->smallItem)
        {
            numCompares++;
            searchHelper(word, numCompares, found, rootNode->leftChildPtr);
        }
        else if (word < rootNode->largeItem)
        {
            numCompares = numCompares + 2;
            searchHelper(word, numCompares, found, rootNode->midChildPtr);
        }
        else
        {
            numCompares = numCompares + 2;
            searchHelper(word, numCompares, found, rootNode->rightChildPtr);
        }
    }

    //Case 4. Node is 2-node
    else
    {
        if (word < rootNode->smallItem)
        {
            numCompares++;
            searchHelper(word, numCompares, found, rootNode->leftChildPtr);
        }
        else
        {
            numCompares++;
            searchHelper(word, numCompares, found, rootNode->midChildPtr);
        }
    }
}

void Dictionary23Tree::insertHelper(string word, TriNode*& rootNode)
{
    //Case 1. Tree is empty
    if (rootNode == NULL)
    {
        rootNode = new TriNode(word);
        return;
    }

    //Case 2. Node is leaf
    else if (rootNode->leftChildPtr == NULL)
    {
        //Case 2.1. Node is 2-node
        if (rootNode->largeItem == "")
        {
            if (word < rootNode->smallItem)
            {
                rootNode->largeItem = rootNode->smallItem;
                rootNode->smallItem = word;
            }
            else
            {
                rootNode->largeItem = word;
            }
        }
        //Case 2.2. Node is 3-node
        else
        {
            if (word < rootNode->smallItem)
            {
                rootNode->temp = rootNode-> smallItem; //Preserve small item at temp pointer temporarily.
                rootNode->smallItem = word;
            }
            else if (word < rootNode->largeItem)
            {
                rootNode->temp = word;
            }
            else
            {
                rootNode->temp = rootNode->largeItem;
                rootNode->largeItem = word;
            }

            //Split 3-node to proceed
            split(rootNode);
        }
        return;
    }

    //Case 3. Node is not a leaf
    //Case 3.1. Node is 3-node
    else if (rootNode->largeItem != "")
    {
        if (word < rootNode->smallItem)
        {
            insertHelper(word, rootNode->leftChildPtr);
        }
        else if (word < rootNode->largeItem)
        {
            insertHelper(word, rootNode->midChildPtr);
        }
        else
        {
            insertHelper(word, rootNode->rightChildPtr);
        }
    }
    //Case 3.2. Node is 2-node
    else
    {
        if (word < rootNode->smallItem)
        {
            insertHelper(word, rootNode->leftChildPtr);
        }
        else
        {
            insertHelper(word, rootNode->midChildPtr);
        }
    }
}

void Dictionary23Tree::split(TriNode*& rootNode)
{
    //Preserve a reference rootNode to delete later (Prevent memory leak)
    TriNode* placeholder = rootNode;

    //See if new root creation needed
    bool newRoot = false;

    //Initialize parent
    TriNode* parentNode = rootNode->parent;

    //Case: parent does not exist.
    if (parentNode == NULL)
    {
        parentNode = new TriNode();
        newRoot = true;
    }

    //Adjust nodes to their according parents
    TriNode* firstNode = new TriNode(rootNode->smallItem);
    firstNode->parent = parentNode;

    TriNode* secondNode = new TriNode(rootNode->largeItem);
    secondNode->parent = parentNode;


    //If rootNode was not a leaf:
    //1. firstNode becomes parent of rootNode's two leftmost children
    //2. secondNode becomes parent of rootNode's two rightmost children
    if (rootNode->leftChildPtr != NULL)
    {
        firstNode->leftChildPtr = rootNode->leftChildPtr; rootNode->leftChildPtr->parent = firstNode;
        firstNode->midChildPtr = rootNode->midChildPtr; rootNode->midChildPtr->parent = firstNode;

        secondNode->leftChildPtr = rootNode->rightChildPtr; rootNode->rightChildPtr->parent = secondNode;
        secondNode->midChildPtr = rootNode->tempRightmost; rootNode->tempRightmost->parent = secondNode;
    }

    //Now, move item from temp in rootNode to p

    //Case 1: Parent is a newly created root
    if (newRoot)
    {
        parentNode->smallItem = rootNode->temp;
        parentNode->leftChildPtr = firstNode;
        parentNode->midChildPtr = secondNode;
    }

    //Case 2: Parent is a 2-node
    else if (parentNode->largeItem == "")
    {
        //If rootNode was a leftChildPtr beforehand,
        if (parentNode->leftChildPtr == rootNode)
        {
            parentNode->largeItem = parentNode->smallItem;
            parentNode->rightChildPtr = parentNode->midChildPtr;

            //Insert the new elements
            parentNode->smallItem = rootNode->temp;
            parentNode->leftChildPtr = firstNode;
            parentNode->midChildPtr = secondNode;
        }
        //If rootNode was a rightChildPtr beforehand,
        else
        {
            //Insert the new elements
            parentNode->largeItem = rootNode->temp;
            parentNode->midChildPtr = firstNode;
            parentNode->rightChildPtr = secondNode;
        }
    }

    //Case 3: Parent is a 3-node
    else
    {
        //For each case:
        // 1. Initialize temp to small/large item value.
        // 2. Realign items of the node to their correct positions by shifting values

        //Case 1: rootNode was a leftChildPtr
        if (parentNode->leftChildPtr == rootNode)
        {
            //Hold value at temp temporarily and switch later
            parentNode->temp = parentNode->smallItem;
            parentNode->smallItem = rootNode->temp;

            //Realign position of the elements
            parentNode->tempRightmost = parentNode->rightChildPtr;
            parentNode->rightChildPtr = parentNode->midChildPtr;
            parentNode->midChildPtr = secondNode;
            parentNode->leftChildPtr = firstNode;
        }
        //Case 2: rootNode was a midChildPtr
        else if (parentNode->midChildPtr == rootNode)
        {
            //Realign position of the elements
            parentNode->temp = rootNode->temp;
            parentNode->tempRightmost = parentNode->rightChildPtr;
            parentNode->midChildPtr = firstNode;
            parentNode->rightChildPtr = secondNode;
        }
        //Case 3: rootNode was a rightChildPtr
        else
        {
            //Realign position of the elements
            parentNode->temp = parentNode->largeItem;
            parentNode->largeItem = rootNode->temp;
            parentNode->rightChildPtr = firstNode;
            parentNode->tempRightmost = secondNode;
        }
        //Split the node at the end of the process since node is a 3-node
        split(parentNode);
    }

    //Memory-Leak Handling
    delete placeholder;

    //If the value inserted caused a new node creation, set root to parent node once again
    if (newRoot)
    {
        root = parentNode;
    }
}

void Dictionary23Tree::search(string queryFile, string outputFile) const
{
    ifstream input;
    ofstream output;

    input.open(queryFile);
    output.open(outputFile);

    string inputLine;
    string outputLine;

    int numComps = 0;
    int numOfQueries = 0;
    int maxCompSoFar = 0;
    double totalCompsMade = 0;
    bool exists = false;

    output << std::noboolalpha;
    output << left;

    while (getline(input, inputLine))
    {
        numComps = 0; exists = false;
        Dictionary23Tree::search(inputLine, numComps, exists);
        output << std::setw(20) << inputLine << std::setw(20) << exists << std::setw(20) << numComps << "\n";
        numOfQueries++;
        if (maxCompSoFar < numComps) { maxCompSoFar = numComps;}
        totalCompsMade += numComps;
    }

    output << "Number of queries: " << numOfQueries << "\n";
    output << "Maximum number of comparisons: " << maxCompSoFar << "\n";
    output << "Average number of comparisons: " << (totalCompsMade / numOfQueries) << "\n";

    input.close();
    output.close();
}