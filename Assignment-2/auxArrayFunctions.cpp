#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

#include "auxArrayFunctions.h"

void attemptOneSwap(int *arr, int N, int K, int currIndex){
    int minIndex, maxIndex, swapIndex;
    
    arr[currIndex] - K >= 0 ? minIndex = arr[currIndex] - K : minIndex = 0;
    arr[currIndex] + K <  N ? maxIndex = arr[currIndex] + K : maxIndex = N - 1;
    swapIndex = rand() % (maxIndex - minIndex + 1) + minIndex;
    
    if (arr[swapIndex] - K <= currIndex && currIndex <= arr[swapIndex] + K){
        int temp = arr[swapIndex];
        arr[swapIndex] = arr[currIndex];
        arr[currIndex] = temp;
    }
}

double averageDistance(int *arr, int N, int K){
    double avgDist = 0.0;
    
    for (int i = 0; i < N; i++){
        int diff = abs(arr[i] - i);
        if (diff > K)
            cout << "Error (please inform the instructor)" << endl;
        avgDist += diff;
    }
    if (N == 0)
        return 0;
    return avgDist / N;
}

void createNearlySortedArrays(int *&arr, int N, int K){
    if (N <= 0){
        arr = NULL;
        return;
    }
    int minIndex, maxIndex;
    arr = new int [N];
    
    srand( time(NULL) );
    for (int i = 0; i < N; i++)
        arr[i] = i;
    
    int iterNo = 0;
    while (iterNo < 10) {
        for (int i = 0; i < N; i++)
            attemptOneSwap(arr, N, K, i);
        for (int i = N - 1; i >= 0; i--)
            attemptOneSwap(arr, N, K, i);
        double d = averageDistance(arr, N, K);
        //cout << d << endl;
        if (d > K / 2)
            break;
        iterNo++;
    }
}

