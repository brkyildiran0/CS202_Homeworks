/*
* Title: Sorting and Algorithm Efficiency
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 1
* Description: Header file for the sorting.cpp
*/
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

#ifndef HW01_SORTING_H
#define HW01_SORTING_H

class sorting
{
public:
    //Assignment-given methods
    //(Sorting Methods)
    void insertionSort(int* arr, const int size, int& countComp, int& countMove);
    void mergeSort(int* arr, const int size, int& countComp, int& countMove);
    void quickSort(int* arr, const int size, int& countComp, int& countMove);

    //(Random Array Initializers)
    void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, const int size);
    void createAscendingArrays(int*& arr1, int*& arr2, int*& arr3, const int size);
    void createDescendingArrays(int*& arr1, int*& arr2, int*& arr3, const int size);

    //(Performance-Analysis)
    void performanceAnalysis();
protected:
    //Helper methods
    void mergeSort(int *arr, int first, int last, int &compCount, int &moveCount);
    void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount);
    void quickSort(int *arr, int first, int last, int &compCount, int &moveCount);
    void partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount);
};


#endif //HW01_SORTING_H
