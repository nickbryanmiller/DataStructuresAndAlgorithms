//
//  main.cpp
//  Busyman
//
//  Created by Nicholas Miller on 4/15/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>

void merge(int otherArray[], int array[], int leftIndex, int middleIndex, int rightIndex) {
    int i;
    int j;
    int k;
    int n1 = middleIndex - leftIndex + 1;
    int n2 =  rightIndex - middleIndex;
    
    /* create two temp arrays */
    int leftTempArray[n1];
    int rightTempArray[n2];
    
    int leftOtherArray[n1];
    int rightOtherArray[n2];
    
    /* Copy data to temp arrays leftTempArray[] and righTempArray[] */
    for(i = 0; i < n1; i++) {
        leftTempArray[i] = array[leftIndex + i];
        leftOtherArray[i] = otherArray[leftIndex + i];
    }
    for(j = 0; j < n2; j++) {
        rightTempArray[j] = array[middleIndex + 1+ j];
        rightOtherArray[j] = otherArray[middleIndex + 1+ j];
    }
    
    /* Merge the temp arrays back into array[leftTempArray..rightTempArray]*/
    i = 0;
    j = 0;
    k = leftIndex;
    
    while (i < n1 && j < n2) {
        if (leftTempArray[i] <= rightTempArray[j]) {
            array[k] = leftTempArray[i];
            otherArray[k] = leftOtherArray[i];
            i++;
        }
        else {
            array[k] = rightTempArray[j];
            otherArray[k] = rightOtherArray[j];
            j++;
        }
        
        k++;
    }
    
    /* Copy the remaining elements of leftTempArray[], if there are any */
    while (i < n1) {
        array[k] = leftTempArray[i];
        otherArray[k] = leftOtherArray[i];
        i++;
        k++;
    }
    
    /* Copy the remaining elements of rightTempArray[], if there are any */
    while (j < n2) {
        array[k] = rightTempArray[j];
        otherArray[k] = rightOtherArray[j];
        j++;
        k++;
    }
}

void mergeSort(int otherArray[], int array[], int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        //Same as (leftIndex + rightIndex)/2, but avoids overflow for large leftIndex and h
        int middleIndex = leftIndex + (rightIndex - leftIndex) /2;
        mergeSort(otherArray, array, leftIndex, middleIndex);
        mergeSort(otherArray, array, middleIndex + 1, rightIndex);
        merge(otherArray, array, leftIndex, middleIndex, rightIndex);
    }
}

int getMaxNumOfActivities(int startArray[], int endArray[], int size) {
    
    // We always do the first activity because it is sorted
    int count = 1;
    
    int i = 0;
    int j = 0;

    // go through and if the start time is greater than the old end time then set the new end time to that one
    for (j = 1; j < size; j++) {
        if (startArray[j] >= endArray[i]) {
            i = j;
            count++;
        }
    }
    
    return count;
}

int main() {
    
    int numOfCases = 0;
    std::cin >> numOfCases;
    
    int outArray[numOfCases];
    
    for (int i = 0; i < numOfCases; i++) {
        
        int numOfActivities = 0;
        std::cin >> numOfActivities;
        
        int startArray[numOfActivities];
        int endArray[numOfActivities];
        
        for (int j = 0; j < numOfActivities; j++) {
            int start = 0;
            std::cin >> start;
            
            int end = 0;
            std::cin >> end;
            
            startArray[j] = start;
            endArray[j] = end;
        }
        
        // Sort endArray by ascending numbers and keep the correct positions for the startArray
        mergeSort(startArray, endArray, 0, numOfActivities - 1);
        
        outArray[i] = getMaxNumOfActivities(startArray, endArray, numOfActivities);
        
    }
    
    for (int k = 0; k < numOfCases; k++) {
        std::cout << outArray[k] << "\n";
    }
    
    return 0;
}
