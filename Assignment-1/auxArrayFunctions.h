#ifndef __AUX_ARRAY_FUNCTIONS
#define __AUX_ARRAY_FUNCTIONS

void displayArray(int *arr, int len);

/* It creates and returns an array with the given size N          */
/* This array is nearly sorted. That is, each item in this array  */
/* is at most K away from its target location.                    */
void createNearlySortedArrays(int *&arr1, int N, int K);

// These are auxiliary functions used to implement createNearlySortedArrays
void attemptOneSwap(int *arr, int N, int K, int currIndex);
double averageDistance(int *arr, int N);

#endif
