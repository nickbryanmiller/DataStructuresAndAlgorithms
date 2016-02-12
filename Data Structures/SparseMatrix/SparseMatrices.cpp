//
//  main.cpp
//  SparseMatrix
//
//  Created by Nicholas Miller on 2/09/16.
//  Copyright © 2016 Nicholas Miller. All rights reserved.
//

#include <iostream>
//#include <ctime>

//This is more efficient because we don't have to look through all of std to find cout.
using std::cout;
using std::cin;
using std::string;

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
    //    int size;
    
    linkedList(){
        head = NULL;
        publicHead = NULL;
        tail = NULL;
        //        size = 0;
    }
    
    void addNodeToTailByTail(int value, int position) {
        Node *p;
        
        if(head == NULL) {
            head = new Node(value, position, NULL);
            publicHead = head;
            tail = head;
        }
        else {
            p = tail;
            p->next = new Node(value, position, NULL);
            tail = p->next;
        }
        
        //        size++;
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

linkedList* addMatrices(linkedList *sparse1, linkedList *sparse2, linkedList *finMatrix, int rows) {
    
    Node *p1;
    Node *p2;
    
    for (int i = 0; i < rows; i++) {
        
        p1 = sparse1[i].publicHead;
        p2 = sparse2[i].publicHead;
        
        while (p1 != NULL || p2 != NULL) {
            
            if (p1 != NULL && p2 == NULL) {
                finMatrix[i].addNodeToTailByTail(p1->data, p1->position);
                
                p1 = p1->next;
            }
            else if (p1 == NULL && p2 != NULL) {
                finMatrix[i].addNodeToTailByTail(p2->data, p2->position);
                
                p2 = p2->next;
            }
            else if (p1->position < p2->position) {
                finMatrix[i].addNodeToTailByTail(p1->data, p1->position);
                
                p1 = p1->next;
            }
            else if (p1->position == p2->position) {
                
                if ((p1->data + p2->data) != 0) {
                    finMatrix[i].addNodeToTailByTail((p1->data + p2->data), p1->position);
                }
                
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (p1->position > p2->position) {
                finMatrix[i].addNodeToTailByTail(p2->data, p2->position);
                
                p2 = p2->next;
            }
        }
        
    }
    
    return finMatrix;
}

string searchForValue(linkedList *finMatrix, int value, int rows) {
    Node *p1;
    string answer = "";
    
    for (int i = 0; i < rows; i++) {
        p1 = finMatrix[i].publicHead;
        while (p1 != NULL) {
            if (p1->data == value) {
                //                 cout << i << " " << p1->position << " ";
                answer = answer + std::to_string(i) + " " + std::to_string(p1->position) + " ";
            }
            p1 = p1->next;
        }
    }
    
    answer = answer + "\n";
    return answer;
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
            
            if (value != 0) {
                mySparse1[i].addNodeToTailByTail(value, column);
            }
        }
    }
    
    //    cout << "------------------------------------------------------------------------";
    //    cout << "matrix one done\n";
    
    int rows2;
    cin >> rows2;
    linkedList *mySparse2 = new linkedList[rows2];
    // This is the double for loop to make the second sparce matrix.
    for (int i = 0; i < rows2; i++) {
        cin >> numElements;
        for (int j = 0; j < numElements; j++) {
            cin >> column;
            cin >> value;
            
            if (value != 0) {
                mySparse2[i].addNodeToTailByTail(value, column);
            }
        }
    }
    
    //    cout << "------------------------------------------------------------------------";
    //    cout << "matrix two done\n";
    
    linkedList *finMatrix = new linkedList[rows1];
    finMatrix = addMatrices(mySparse1, mySparse2, finMatrix, rows1);
    
    int searchAmount;
    cin >> searchAmount;
    
    int searchValue;
    
    string answer = "";
    for (int i = 0; i < searchAmount; i++) {
        cin >> searchValue;
        answer = answer + searchForValue(finMatrix, searchValue, rows1);
        //        cout << "\n";
    }
    
    cout << answer;
    
}

int main(void) {
    
    std::ios::sync_with_stdio(false);
    
    doMatrixAdditionThenFindValue();
    
    cout << "\n";
    return(0);
}
