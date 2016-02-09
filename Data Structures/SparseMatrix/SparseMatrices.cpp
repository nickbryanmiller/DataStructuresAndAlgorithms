//
//  main.cpp
//  SparseMatrix
//
//  Created by Nicholas Miller on 2/09/16.
//  Copyright © 2016 Nicholas Miller. All rights reserved.
//

#include <iostream>
#include <ctime>

//This is more efficient because we don't have to look through all of std to find cout.
using std::cout;
using std::cin;

class Node{
public:
    int data;
    int position;
    Node * next;
    
    Node(int x, int pos) {
        data = x;
        position = pos;
        next = NULL;
    }
    Node(int x, int pos, Node * y) {
        data = x;
        position = pos;
        next = y;
    }
};


class linkedList{
    Node *head;
    Node *tail;
public:
    
    Node *publicHead;
    int size;
    
    linkedList(){
        head = NULL;
        publicHead = NULL;
        tail = NULL;
        size = 0;
    }
    
    void addNodeToTail(int value, int position) {
        Node *p;
        
        if(head == NULL) {
            head = new Node(value, position, NULL);
            publicHead = head;
        }
        else {
            p = head;
            while(p->next != NULL) {
                p = p->next;
            }
            p->next = new Node(value, position, NULL);
        }
        
        size++;
    }
    
    Node* containsPositionReturn(int value) {
        Node *p = head;
        
        while(p != NULL) {
            if (p->position == value) {
                return p;
            }
            p = p->next;
        }
        
        return NULL;
    }
    
    bool hasLoop(){
        
        Node *tortoise = head;
        Node *hare = head;
        
        while (tortoise && hare && hare->next) {
            tortoise = tortoise->next;
            hare = hare->next->next;
            
            if (tortoise == hare) {
                
                //                removeLoop(tortoise);
                
                return true;
            }
        }
        
        return false;
    }
    
    void printListOfPosAndValue() {
        Node *p = head;
        
        while(p != NULL) {
            cout << "(" << p->position << ", " << p->data << ")" << "\t";
            p = p->next;
        }
    }
    
    void printListOfValue() {
        Node *p = head;
        
        while(p != NULL) {
            cout << p->data << "\t";
            p = p->next;
        }
    }
    
};
//==========================================================================================================================//


void timeCheck() {
    clock_t begin = clock();
    
    //    Method to test
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "The Program took " << elapsed_secs << " seconds";
}

void doMatrixAdditionThenFindValue() {
    // Input variables.
    int numElements;
    int column;
    int value;
    
    int rows1;
    cin >> rows1;
    linkedList *mySparse1 = new linkedList[rows1];
    // This is the double for loop to make the first sparse matrix.
    for (int i = 0; i < rows1; i++) {
        cin >> numElements;
        for (int j = 0; j < numElements; j++) {
            cin >> column;
            cin >> value;
            
            mySparse1[i].addNodeToTail(value, column);
        }
    }
    
    int rows2;
    cin >> rows2;
    linkedList *mySparse2 = new linkedList[rows2];
    // This is the double for loop to make the second sparce matrix.
    for (int i = 0; i < rows2; i++) {
        cin >> numElements;
        for (int j = 0; j < numElements; j++) {
            cin >> column;
            cin >> value;
            
            mySparse2[i].addNodeToTail(value, column);
        }
    }
    
    linkedList *finMatrix = new linkedList[rows1];
//    finMatrix = addMatrices(mySparse1, mySparse2, finMatrix, rows1);
    
    int searchAmount;
    cin >> searchAmount;
    
    int searchValue;
    for (int i = 0; i < searchAmount; i++) {
        cin >> searchValue;
//        searchForValue(finMatrix, searchValue, rows1);
        cout << "\n";
    }
    
//    // This prints the matrices.
//    for (int i = 0; i < rows1; i++) {
//        finMatrix[i].printListOfPosAndValue();
//        cout << "\n";
//    }

}

int main(void) {
    
//    doMatrixAdditionThenFindValue();
    
    cout << "\n";
    return(0);
}
