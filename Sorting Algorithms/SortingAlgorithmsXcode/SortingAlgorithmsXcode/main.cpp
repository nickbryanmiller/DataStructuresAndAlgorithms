//
//  main.cpp
//  Sorting Algorithms
//
//  Created by Nicholas Miller on 1/15/16.
//  Copyright © 2016 Nicholas Miller. All rights reserved.
//
//
/*  The ideal sorting algorithm would have the following properties:
 
 Stable: Equal keys aren't reordered.
 Operates in place, requiring O(1) extra space.
 Worst-case O(n·lg(n)) key comparisons.
 Worst-case O(n) swaps.
 Adaptive: Speeds up to O(n) when data is nearly sorted or when there are few unique keys.
 
 */


#include <iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

int size;

// Properties of the Bad Insertion Sort
// Stable:                  Yes
// Extra Space (Array):     Θ(1)
// Overall Complexity:      Θ(n^2)
// Worst-Case:              Θ(n^2)
// Best-Case:               Θ(n^2)
// Adaptive:                Yes
// Overhead:                Very Low
void badInsertionSort(int array[], int size) {
    for (int i = 0; i <= size - 1; i++) {
        for (int j = size - 1; j > 0; j--) {
            if (array[j] < array[j-1]) {
                int temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
        }
    }
}

// Properties of the Good Insertion Sort
// Stable:                  Yes
// Extra Space (Array):     Θ(1)
// Overall Complexity:      Θ(n^2)
// Worst-Case:              Θ(n^2)
// Best-Case:               Θ(n)
// Adaptive:                Yes, Θ(n) when nearly sorted
// Overhead:                Very Low
// This algorithm is better and takes less steps than the one above.
//  I am resubmitting because it is better.
void goodInsertionSort(int array[], int size) {
    int j;
    
    for (int i = 0; i <= size - 1; i++) {
        j = i;
        while (j > 0 && array[j] < array[j-1]) {
            int temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
            j--;
        }
    }
}

// Properties of the Bad Bubble Sort
// Stable:                  Yes
// Extra Space (Array):     Θ(1)
// Overall Complexity:      Θ(n^2)
// Worst-Case:              Θ(n^2)
// Best-Case:               Θ(n^2)
// Adaptive:                Yes, Θ(^2) when nearly sorted
// Overhead:                Very Low
void badBubbleSort(int array[], int size) {
    
    for (int i = 0; i <= size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (array[j+1] < array[j]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

// Properties of the Modified Bubble Sort
// Stable:                  Yes
// Extra Space (Array):     Θ(1)
// Overall Complexity:      Θ(n^2)
// Worst-Case:              Θ(n^2)
// Best-Case:               Θ(n)
// Adaptive:                Yes, Θ(n) when nearly sorted
// Overhead:                Low
void forBubbleSort(int array[], int size) {
    bool sorted = false;
    
    for (int i = 0; (i < size - 1) && sorted == false; i++) {
        sorted = true;
        for (int j = 0; j < size - 1; j++) {
            if (array[j+1] < array[j]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                
                sorted = false;
            }
        }
    }
}
void whileBubbleSort(int array[], int size) {
    bool sorted = false;
    int i = 0;
    
    while (sorted == false) {
        sorted = true;
        i++;
        for (int j = 0; j < size - i; j++) {
            if (array[j+1] < array[j]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                
                sorted = false;
            }
        }
    }
}

// Properties of the Selection Sort
// Stable:                  No
// Extra Space (Array):     Θ(1)
// Overall Complexity:      Θ(n^2)
// Worst-Case:              Θ(n^2)
// Best-Case:               Θ(n)
// Adaptive:                No
// Overhead:                Low
void selectionSort(int array[], int size) {
    int minPos;
    int temp;
    
    for (int i = 0; i < size - 1; i++) {
        //        set minPosition to the current index of array
        minPos = i;
        
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minPos]) {
                //                minPosition will keep track of the index that min is in
                minPos = j;
            }
        }
        
        //        Swap the value of i with the new minPosition
        if (minPos != i) {
            temp = array[i];
            array[i] = array[minPos];
            array[minPos] = temp;
        }
    }
}

// Properties of the Merge Sort
// Stable:                      Yes
// Extra Space (Array):         Θ(n)
// Extra Space (Linked List):   Θ(log(n))
// Overall Complexity:          Θ(n * log(n))
// Worst-Case:                  Θ(n * log(n))
// Best-Case:                   Θ(n * log(n))
// Adaptive:                    No
// Extra:                       Does not require random access to data
/* leftIndex is for left index and rightIndex is right index of the sub-array of array to be sorted */
void merge(int array[], int leftIndex, int middleIndex, int rightIndex) {
    int i;
    int j;
    int k;
    int n1 = middleIndex - leftIndex + 1;
    int n2 =  rightIndex - middleIndex;
    
    /* create two temp arrays */
    int leftTempArray[n1];
    int rightTempArray[n2];
    
    /* Copy data to temp arrays leftTempArray[] and righTempArray[] */
    for(i = 0; i < n1; i++) {
        leftTempArray[i] = array[leftIndex + i];
    }
    for(j = 0; j < n2; j++) {
        rightTempArray[j] = array[middleIndex + 1+ j];
    }
    
    /* Merge the temp arrays back into array[leftTempArray..rightTempArray]*/
    i = 0;
    j = 0;
    k = leftIndex;
    
    while (i < n1 && j < n2) {
        if (leftTempArray[i] <= rightTempArray[j]) {
            array[k] = leftTempArray[i];
            i++;
        }
        else {
            array[k] = rightTempArray[j];
            j++;
        }
        
        k++;
    }
    
    /* Copy the remaining elements of leftTempArray[], if there are any */
    while (i < n1) {
        array[k] = leftTempArray[i];
        i++;
        k++;
    }
    
    /* Copy the remaining elements of rightTempArray[], if there are any */
    while (j < n2) {
        array[k] = rightTempArray[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        //Same as (leftIndex + rightIndex)/2, but avoids overflow for large leftIndex and h
        int middleIndex = leftIndex + (rightIndex - leftIndex) /2;
        mergeSort(array, leftIndex, middleIndex);
        mergeSort(array, middleIndex + 1, rightIndex);
        merge(array, leftIndex, middleIndex, rightIndex);
    }
}

// Properties of the Heap Sort
// Stable:                      No
// Extra Space (Array):         Θ(1)
// Overall Complexity:          Θ(n * log(n))
// Worst-Case:                  Θ(n * log(n))
// Best-Case:                   Θ(n * log(n))
// Adaptive:                    No
void maxHeap(int a[], int i, int n) {
    int l,r,largest,loc;
    l=2*i;
    r=(2*i+1);
    if((l<=n)&&a[l]>a[i])
        largest=l;
    else
        largest=i;
    if((r<=n)&&(a[r]>a[largest]))
        largest=r;
    if(largest!=i)
    {
        loc=a[i];
        a[i]=a[largest];
        a[largest]=loc;
        maxHeap(a, largest,n);
    }
}
void buildMaxHeap(int a[], int n) {
    for(int k = n/2; k >= 1; k--)
    {
        maxHeap(a, k, n);
    }
}
void heapSort(int a[], int n) {
    
    buildMaxHeap(a,n);
    int i, temp;
    for (i = n; i >= 2; i--)
    {
        temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        maxHeap(a, 1, i - 1);
    }
}

int main(int argc, const char * argv[]) {
    cout << "By the Bad Insertion Sort Method\n";
    int myArray1[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray1)/sizeof(int);
    badInsertionSort(myArray1, size);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray1[i] << "\t";
    }
    
    cout << "\nBy the Good Insertion Sort Method\n";
    int myArray7[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray7)/sizeof(int);
    goodInsertionSort(myArray7, size);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray7[i] << "\t";
    }
    
    cout << "\nBy the Bad Bubble Sort Method\n";
    int myArray2[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray2)/sizeof(int);
    badBubbleSort(myArray2, size);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray2[i] << "\t";
    }
    
    cout << "\nBy the For-Loop Bubble Sort Method\n";
    int myArray3[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray3)/sizeof(int);
    forBubbleSort(myArray3, size);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray3[i] << "\t";
    }
    
    cout << "\nBy the While-Loop Bubble Sort Method\n";
    int myArray4[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray4)/sizeof(int);
    whileBubbleSort(myArray4, size);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray4[i] << "\t";
    }
    
    cout << "\nBy the Selection Sort Method\n";
    int myArray5[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray5)/sizeof(int);
    selectionSort(myArray5, size);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray5[i] << "\t";
    }
    
    cout << "\nBy the Merge Sort Method\n";
    int myArray6[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray6)/sizeof(int);
    mergeSort(myArray6, 0, size - 1);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray6[i] << "\t";
    }
    
    cout << "\nBy the Heap Sort Method\n";
    int myArray8[] = {3, 2, 5, 7, 4, 12, 6, 15, 1, 0, 8, 10, 11};
    size = sizeof(myArray8)/sizeof(int);
    heapSort(myArray8, size);
    for (int i = 0; i <= size - 1; i++) {
        cout << myArray8[i] << "\t";
    }
    
    
    cout << "\n\n";
    return 0;
}
