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
    
    int getSize() {
        Node *p = head;
        int count = 0;
        
        while(p != NULL) {
            count++;
            p = p->next;
        }
        
        return count;
    }
    
    Node* getNodeAtPosition(int position) {
        Node *p = head;
        
        while (position--) {
            if (p != NULL)
                p = p->next;
            else
                return NULL;
        }
        return p;
    }
    
    Node* getNodeWithDataValue(int value) {
        Node *p = head;
        
        while (p != NULL) {
            if (p->data == value) {
                return p;
            }
            p = p->next;
        }
        
        return NULL;
    }
    
    Node* getNodeWithPositionValue(int value) {
        Node *p = head;
        
        while (p != NULL) {
            if (p->position == value) {
                return p;
            }
            p = p->next;
        }
        
        return NULL;
    }
    
    int getNodePostionWithValue(int value) {
        Node *p = head;
        int counter = -1;
        
        if (p == NULL) {
            return -1;
        }
        
        while (p != NULL) {
            counter++;
            if (p->data == value) {
                return counter;
            }
            p = p->next;
        }
        
        return -1;
    }
    
    int getNodeValueWithPosition(int position) {
        Node *p = getNodeAtPosition(position);
        return p->data;
    }
    
    void pointNodeToPosition(Node* myNode, int position) {
        Node *p = getNodeAtPosition(position);
        myNode->next = p;
    }
    void pointNodeToNode(Node* node1, Node* node2) {
        node1->next = node2;
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
    
    void addNodeToHead(int value, int position) {
        Node *p;
        
        if (head == NULL) {
            head = new Node(value, NULL);
            publicHead = head;
        }
        else {
            p = head;
            Node *node = new Node(value, position);
            node->next = p;
            head = node;
        }
        
        size++;
    }
    
    void addNodeAtIndex(int position, int value) {
        Node *p = getNodeAtPosition(position - 1);
        
        if (position == 0) {
            addNodeToHead(value, position);
        }
        
        if(p != NULL) {
            p->next = new Node(value, position, p->next);
        }
        
        size++;
    }
    
    void addNodeAfterIndex(int position, int value) {
        Node *p = getNodeAtPosition(position);
        
        if(p != NULL) {
            p->next = new Node(value, position, p->next);
        }
        
        size++;
    }
    
    void removeNodeAtPosition(int position) {
        Node *nodeToDelete = getNodeAtPosition(position);
        Node *p = getNodeAtPosition(position - 1);
        
        p->next = nodeToDelete->next;
        delete nodeToDelete;
        
    }
    
    void removeNodeWithValue(int value) {
        Node *p = NULL;
        Node *nodeToDelete = NULL;
        
        if (head->data == value) {
            nodeToDelete = head;
            
            head = nodeToDelete->next;
            publicHead = head;
            delete nodeToDelete;
            return;
        }
        
        if (getNodePostionWithValue(value) > 0) {
            nodeToDelete = getNodeWithDataValue(value);
            p = getNodeAtPosition(getNodePostionWithValue(value) - 1);
            p->next = nodeToDelete->next;
            delete nodeToDelete;
        }
        
    }
    
    //    Does not work if all numbers in a list are the same
    void removeAllNodesWithValue(int value) {
        Node *p;
        Node *nodeToDelete;
        
        //        while (head->data == value && head != NULL) {
        //            nodeToDelete = head;
        //            head = nodeToDelete->next;
        //            delete nodeToDelete;
        ////            p = p->next;
        //        }
        
        while (getNodePostionWithValue(value) > 0) {
            nodeToDelete = getNodeWithDataValue(value);
            p = getNodeAtPosition(getNodePostionWithValue(value) - 1);
            p->next = nodeToDelete->next;
            delete nodeToDelete;
        }
    }
    
    bool containsValue(int value) {
        Node *p = head;
        
        while(p != NULL) {
            if (p->data == value) {
                return true;
            }
            p = p->next;
        }
        
        return false;
    }
    bool containsPosition(int value) {
        Node *p = head;
        
        while(p != NULL) {
            if (p->position == value) {
                return true;
            }
            p = p->next;
        }
        
        return false;
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
    
    void printNodeAtPosition(int position) {
        cout << getNodeValueWithPosition(position);
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
