//
//  main.cpp
//  InversionCount
//
//  Created by Nicholas Miller on 4/13/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>

using std::cout;
using std::cin;

long long mergeThem(long long array[], long long tempArray[], long long left, long long mid, long long right) {
    
    // Index of the left array
    long long i = left;
    // Index of the right array
    long long j = mid;
    // Index of the resulting array
    long long k = left;
    
    long long inversionCount = 0;
    
    // Move through both subarrays and put them long longo the resulting array in order
    while ((i <= mid - 1) && (j <= right)) {
        
        if (array[i] <= array[j]) {
            tempArray[k++] = array[i++];
        }
        else {
            tempArray[k++] = array[j++];
            
            // If left[i] is ever bigger than right[j] then we know there are mid - i inversions
            inversionCount = inversionCount + (mid - i);
        }
    }
    
    // If left had more elements left over after right was done then add them to the resulting array
    while (i <= mid - 1) {
        tempArray[k++] = array[i++];
    }
    
    // If right had more elements left over after left was done then add them to the resulting array
    while (j <= right) {
        tempArray[k++] = array[j++];
    }
    
    // Everything goes back into the spots of the original array
    for (i = left; i <= right; i++) {
        array[i] = tempArray[i];
    }
    
    return inversionCount;
}

long long mergeSort(long long array[], long long tempArray[], long long left, long long right) {
    
    long long mid = 0;
    long long inversionCount = 0;
    
    if (right > left) {
        
        // Need our split to know the left and right arrays
        mid = (right + left)/2;
        
        // Sum the left count and right count
        inversionCount  = mergeSort(array, tempArray, left, mid);
        inversionCount += mergeSort(array, tempArray, mid + 1, right);
        
        // Merge the two halves together
        inversionCount += mergeThem(array, tempArray, left, mid + 1, right);
    }
    
    return inversionCount;
}

// Set a tempArray and call our recursive method
long long doMergeSort(long long array[], long long size) {
    
    long long tempArray[size];
    
    return mergeSort(array, tempArray, 0, size - 1);
}

int main() {
    
    long long numOfCases = 0;
    cin >> numOfCases;
    
    long long outputArray[numOfCases];
    
    for (int i = 0; i < numOfCases; i++) {
        long long arraySize = 0;
        cin >> arraySize;
        long long array[arraySize];
        
        for (long long j = 0; j < arraySize; j++) {
            long long input = 0;
            cin >> input;
            
            array[j] = input;
        }
        
        outputArray[i] = doMergeSort(array, arraySize);
    }
    
    for (long long i = 0; i < numOfCases; i++) {
        cout << outputArray[i] << "\n" ;
    }
    
    
    return 0;
}
