/**
* Title: Balanced Search Trees
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 3
* Description: Interface for other tree implementations.
* Designed as a basic BST in essence.
*/

#include <iomanip> //Included to tidy output by using setw(int)
#include "DictionarySearchTree.h"

DictionarySearchTree::DictionarySearchTree()
{
    root = NULL;
}

DictionarySearchTree::DictionarySearchTree(string dictionaryFile)
{
    //Initialize root to NULL
    root = NULL;

    //Open the input file
    ifstream file;
    file.open(dictionaryFile);
    string line;

    //Construct the tree
    /**
    * NOTE: insert() is being called here since it is the way assignment lowers the amount of code.
    * But it is STRONGLY advised to not invoke virtual functions from the class constructor.
    * Reference: The Design and Evolution of C++, Bjarne Stroustrup, Sec. 13.2.4.2.
    */
    while (getline(file, line))
    {
        insert(line);
    }
}

DictionarySearchTree::~DictionarySearchTree()
{
    destroyTree(root);
}

void DictionarySearchTree::insert(string word)
{
    insertHelper(word, root);
}

void DictionarySearchTree::search(string word, int &numComparisons, bool &found) const
{
    searchHelper(word, numComparisons, found, root);
}

void DictionarySearchTree::search(string queryFile, string outputFile) const
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
        search(inputLine, numComps, exists);
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

TriNode* DictionarySearchTree::insertHelper(const string& word, TriNode *&rootNode)
{
    if (rootNode == NULL)
    {
        rootNode = new TriNode(word);
    }
    else if (string(word) < string(rootNode->smallItem))
    {
        rootNode->leftChildPtr = insertHelper(word, rootNode->leftChildPtr);
    }
    else if (string(word) > string(rootNode->smallItem))
    {
        rootNode->midChildPtr = insertHelper(word, rootNode->midChildPtr);
    }
    return rootNode;
}

void DictionarySearchTree::destroyTree(TriNode *rootNode) //TODO if memory leak occurs, seek here.
{
    if (rootNode == NULL) return;

    destroyTree(rootNode->leftChildPtr);
    destroyTree(rootNode->midChildPtr);
    destroyTree(rootNode->rightChildPtr);

    delete rootNode;
}

void DictionarySearchTree::searchHelper(string word, int &numCompares, bool& found, TriNode* rootNode) const
{
    if (rootNode == NULL)
    {
        found = false;
        return;
    }
    else if (word < rootNode->smallItem)
    {
        numCompares++;
        searchHelper(word, numCompares, found, rootNode->leftChildPtr);
    }
    else if (word > rootNode->smallItem)
    {
        numCompares++;
        searchHelper(word, numCompares, found, rootNode->midChildPtr);
    }
    else
    {
        numCompares++;
        found = true;
        return;
    }
}