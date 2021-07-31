/*
* Title: Sorting and Algorithm Efficiency
* Author: Ömer Burak Yıldıran
* ID: 21901425
* Section: 1
* Assignment: 1
* Description: CPP file for the sorting.cpp
* Used the exact algorithms given in the course textbook.
*/

#include "sorting.h"

/**
 * Sorts given array in descending order with insertionSort principles.
 * @param arr, given array of int
 * @param size, size of arr
 * @param countComp, amount of comparisons made
 * @param countMove, amount of data moves made
 */
void sorting::insertionSort(int *arr, const int size, int &countComp, int &countMove)
{
    for ( int unsorted = 1; unsorted < size; unsorted++)
    {
        // At this point, theArray[0..unsorted-1] is sorted.
        // Find the right position (loc) in theArray[0..unsorted]
        // for theArray[unsorted], which is the first entry in the
        // unsorted region; shift, if necessary, to make room

        int nextItem = arr[unsorted];
        int loc = unsorted - 1;

        while ((loc >= 0) && (arr[loc] < nextItem))
        {
            // Shift theArray[loc - 1] to the right
            arr[loc + 1] = arr[loc];
            loc--;

            countComp++; //!Note to TA: I didn't count loc > 0 as a compMove since it is not a key comparison.
            countMove++;
        }

        // At this point, theArray[loc] is where nextItem belongs
        arr[loc + 1] = nextItem; // Insert nextItem into sorted region
        countMove++;
    }
}

/**
 * Helper method for mergeSort. Merges two split sub arrays.
 * @param arr, the array to be split up and merged
 * @param first, index of the first element in the arr
 * @param mid, index of the middle element in the arr
 * @param last, index of the last element in the arr
 * @param compCount, counter for the comparisons made
 * @param moveCount, counter for the moves made
 */
void sorting::merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount)
{
    int *temp = new int[last + 1];

    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;

    int index = first1;

    //Check whether the sub-arrays exist, and copy the greater to the temp if it does
    while ((first1 <= last1) && (first2 <= last2))
    {
        if (arr[first1] >= arr[first2])
        {
            temp[index] = arr[first1];
            first1++;

            moveCount++;
        }
        else
        {
            temp[index] = arr[first2];
            first2++;

            moveCount++;
        }
        index++;

        compCount++;
    }

    //Concluding first array (if needed)
    while (first1 <= last1)
    {
        temp[index] = arr[first1];
        first1++;
        index++;

        moveCount++;
    }

    //Concluding second array (if needed)
    while (first2 <= last2)
    {
        temp[index] = arr[first2];
        first2++;
        index++;

        moveCount++;
    }

    //Copying the result back to the original array arr
    for (index = first; index <= last; index++)
    {
        arr[index] = temp[index];

        moveCount++;
    }

    delete [] temp;
}

/**
 * Wrapper function for mergeSort
 */
void sorting::mergeSort(int *arr, int first, int last, int &compCount, int &moveCount)
{
    if (first < last)
    {
        int mid = first + (last - first) / 2;

        //In order, first sort the left subArray, then the left. Finally merge two subarray.
        mergeSort(arr, first, mid, compCount, moveCount);
        mergeSort(arr, mid + 1, last, compCount, moveCount);

        merge(arr, first, mid, last, compCount, moveCount);
    }
}

/**
 * Sorts given array in descending order, uses wrapper function.
 * @param arr, array to be sorted
 * @param size, size of the arr
 * @param compCount, counter for the comparisons made
 * @param moveCount, counter for the moves made
 */
void sorting::mergeSort(int *arr, const int size, int &compCount, int &moveCount)
{
    mergeSort(arr, 0, size - 1, compCount, moveCount);
}

/**
 * Helper function (partition principle for quicksort) of quickSort.
 * @param arr, array to be sorted
 * @param first, index of first element
 * @param last, index of last element
 * @param pivotIndex, index of the pivot (quickSort pivot for this assignment is FIRST element of arr)
 * @param compCount, total comparisons made
 * @param moveCount, total move of elements made
 */
void sorting::partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount)
{
    //Init copy pivot (yields 1 move) !First element for this assignment is the pivot!
    int pivot = arr[first];
    moveCount++;

    //Initialize indexes that are required
    int lastS1 = first;
    int firstUnknown = first + 1;

    //Traverse the array until the unknown is emptied
    while (firstUnknown <= last)
    {
        //Move the item with respect to pivot value (descending order)
        if (arr[firstUnknown] > pivot)
        {
            lastS1++;

            //Swap the values (yields 3 moves)
            int temp = arr[firstUnknown];
            arr[firstUnknown] = arr[lastS1];
            arr[lastS1] = temp;

            moveCount = moveCount + 3;
        }
        compCount++;
        firstUnknown++;
    }

    //Relocate pivot (yields 3 moves)
    int temp = arr[first];
    arr[first] = arr[lastS1];
    arr[lastS1] = temp;

    pivotIndex = lastS1;

    moveCount = moveCount + 3;
}

/**
 * Wrapper function for quicksort
 */
void sorting::quickSort(int *arr, int first, int last, int &compCount, int &moveCount)
{
    int pivotIndex;

    if (first < last)
    {
        //Initialize partition
        partition(arr, first, last, pivotIndex, compCount, moveCount);

        //Sort both regions (recursion)
        quickSort(arr, first, pivotIndex - 1, compCount, moveCount);
        quickSort(arr, pivotIndex + 1, last, compCount, moveCount);
    }
}

/**
 * Sorts given array in descending order with quickSort algorithm, uses wrapper function.
 * @param arr, array to be sorted in descending order
 * @param size, size of arr
 * @param compCount, counter for the comparisons made
 * @param moveCount, counter for the moves made
 */
void sorting::quickSort(int *arr, const int size, int &compCount, int &moveCount)
{
    quickSort(arr, 0, size - 1, compCount, moveCount);
}

/**
 * Populates three identical int array with completely random int values
 * @param arr1, arr2, arr3 are identical arrays.
 * @param size, size of all three arrays (individually)
 */
void sorting::createRandomArrays(int *&arr1, int *&arr2, int *&arr3, const int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        int randomNumber = rand();
        arr1[i] = randomNumber;
        arr2[i] = randomNumber;
        arr3[i] = randomNumber;
    }
}

/**
 * Populates three identical int array with random values, but in an ascending manner
 * @param arr1, arr2, arr3 are identical arrays.
 * @param size, size of all three arrays (individually)
 */
void sorting::createAscendingArrays(int *&arr1, int *&arr2, int *&arr3, const int size)
{
    srand(time(NULL));
    int sumSoFar = 0;
    for (int i = 0; i < size; ++i)
    {
        sumSoFar += rand() % 100;
        arr1[i] = sumSoFar;
        arr2[i] = sumSoFar;
        arr3[i] = sumSoFar;
    }
}

/**
 * Populates three identical int array with random values, but in an descending manner
 * @param arr1, arr2, arr3 are identical arrays.
 * @param size, size of all three arrays (individually)
 */
void sorting::createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, const int size)
{
    srand(time(NULL));
    //Note to TA: I didn't use INT_MAX since it required me to include "climits.h" (which seems that it's not allowed)
    int maxPositiveIntValue = 2147483647;
    for (int i = 0; i < size; ++i)
    {
        maxPositiveIntValue -= rand() % 100; //(% 100 is to ensure we won't go to negative values)
        arr1[i] = maxPositiveIntValue;
        arr2[i] = maxPositiveIntValue;
        arr3[i] = maxPositiveIntValue;
    }
}

/**
 * BELOW IS THE PERFORMANCE ANALYSIS, INCLUDES EVERYTHING ABOVE AND ANALYSES ALL CASES.
 */
void sorting::performanceAnalysis()
{
    //Initialize Arrays for all three types of sorting algorithm tests
    int *insertionArr1 = new int[5000];
    int *insertionArr2 = new int[10000];
    int *insertionArr3 = new int[15000];
    int *insertionArr4 = new int[20000];
    int *insertionArr5 = new int[25000];
    int *insertionArr6 = new int[30000];
    int *insertionArr7 = new int[35000];
    int *insertionArr8 = new int[40000];

    int *mergeArr1 = new int[5000];
    int *mergeArr2 = new int[10000];
    int *mergeArr3 = new int[15000];
    int *mergeArr4 = new int[20000];
    int *mergeArr5 = new int[25000];
    int *mergeArr6 = new int[30000];
    int *mergeArr7 = new int[35000];
    int *mergeArr8 = new int[40000];

    int *quickArr1 = new int[5000];
    int *quickArr2 = new int[10000];
    int *quickArr3 = new int[15000];
    int *quickArr4 = new int[20000];
    int *quickArr5 = new int[25000];
    int *quickArr6 = new int[30000];
    int *quickArr7 = new int[35000];
    int *quickArr8 = new int[40000];

    //------------------------------FOR RANDOMLY DISTRIBUTED ARRAYS------------------------------//
    createRandomArrays(insertionArr1, mergeArr1, quickArr1, 5000);
    createRandomArrays(insertionArr2, mergeArr2, quickArr2, 10000);
    createRandomArrays(insertionArr3, mergeArr3, quickArr3, 15000);
    createRandomArrays(insertionArr4, mergeArr4, quickArr4, 20000);
    createRandomArrays(insertionArr5, mergeArr5, quickArr5, 25000);
    createRandomArrays(insertionArr6, mergeArr6, quickArr6, 30000);
    createRandomArrays(insertionArr7, mergeArr7, quickArr7, 35000);
    createRandomArrays(insertionArr8, mergeArr8, quickArr8, 40000);

    int compCounter = 0;
    int moveCounter = 0;

    cout << "################################# RANDOMLY GENERATED ARRAYS, SORTING ANALYSIS #############################" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

    cout << "Analysis of Insertion Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    auto begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr1, 5000, compCounter, moveCounter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Analysis of Merge Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Analysis of Quick Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    //------------------------------FOR RANDOMLY DISTRIBUTED ASCENDING ARRAYS------------------------------//
    createAscendingArrays(insertionArr1, mergeArr1, quickArr1, 5000);
    createAscendingArrays(insertionArr2, mergeArr2, quickArr2, 10000);
    createAscendingArrays(insertionArr3, mergeArr3, quickArr3, 15000);
    createAscendingArrays(insertionArr4, mergeArr4, quickArr4, 20000);
    createAscendingArrays(insertionArr5, mergeArr5, quickArr5, 25000);
    createAscendingArrays(insertionArr6, mergeArr6, quickArr6, 30000);
    createAscendingArrays(insertionArr7, mergeArr7, quickArr7, 35000);
    createAscendingArrays(insertionArr8, mergeArr8, quickArr8, 40000);

    cout << "################################# RANDOMLY GENERATED ASCENDING ARRAYS, SORTING ANALYSIS #############################" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

    cout << "Analysis of Insertion Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Analysis of Merge Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Analysis of Quick Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    //------------------------------FOR RANDOMLY DISTRIBUTED DESCENDING ARRAYS------------------------------//
    createDescendingArrays(insertionArr1, mergeArr1, quickArr1, 5000);
    createDescendingArrays(insertionArr2, mergeArr2, quickArr2, 10000);
    createDescendingArrays(insertionArr3, mergeArr3, quickArr3, 15000);
    createDescendingArrays(insertionArr4, mergeArr4, quickArr4, 20000);
    createDescendingArrays(insertionArr5, mergeArr5, quickArr5, 25000);
    createDescendingArrays(insertionArr6, mergeArr6, quickArr6, 30000);
    createDescendingArrays(insertionArr7, mergeArr7, quickArr7, 35000);
    createDescendingArrays(insertionArr8, mergeArr8, quickArr8, 40000);
    cout << "################################# RANDOMLY GENERATED DESCENDING ARRAYS, SORTING ANALYSIS #############################" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

    cout << "Analysis of Insertion Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    insertionSort(insertionArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Analysis of Merge Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(mergeArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Analysis of Quick Sort" << endl;
    cout << "Array Size " << "\t\t\t" << "Elapsed Time" << "\t\t\t" << "compCount" << "\t\t\t" << "moveCount" << endl;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr1, 5000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "5000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr2, 10000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "10000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr3, 15000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "15000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr4, 20000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "20000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr5, 25000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "25000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr6, 30000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "30000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr7, 35000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "35000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    begin = std::chrono::high_resolution_clock::now();
    quickSort(quickArr8, 40000, compCounter, moveCounter);
    end = std::chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "40000" << "\t\t\t\t" << duration << "ms" << "\t\t\t\t" << compCounter << "\t\t\t\t" << moveCounter << endl;
    compCounter = 0;
    moveCounter = 0;

    //Heap Cleaning
    delete [] insertionArr1;
    delete [] insertionArr2;
    delete [] insertionArr3;
    delete [] insertionArr4;
    delete [] insertionArr5;
    delete [] insertionArr6;
    delete [] insertionArr7;
    delete [] insertionArr8;

    delete [] mergeArr1;
    delete [] mergeArr2;
    delete [] mergeArr3;
    delete [] mergeArr4;
    delete [] mergeArr5;
    delete [] mergeArr6;
    delete [] mergeArr7;
    delete [] mergeArr8;

    delete [] quickArr1;
    delete [] quickArr2;
    delete [] quickArr3;
    delete [] quickArr4;
    delete [] quickArr5;
    delete [] quickArr6;
    delete [] quickArr7;
    delete [] quickArr8;
}