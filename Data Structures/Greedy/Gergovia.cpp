//
//  main.cpp
//  Gergovia
//
//  Created by Nicholas Miller on 4/13/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>

//This is more efficient because we don't have to look through all of std to find cout.
using std::cout;
using std::cin;

class Node{
public:
    long long data;
    Node * next;
    
    Node(long long x) {
        data = x;
        next = NULL;
    }
    Node(long long x, Node * y) {
        data = x;
        next = y;
    }
};


class linkedList{
    Node *head;
    Node *tail;
public:
    
    Node *publicHead;
    
    linkedList(){
        head = NULL;
        publicHead = NULL;
        tail = NULL;
    }
    
    long long getAbs(long long num) {
        
        long long ans = 0;
        
        if (num < 0) {
            ans = 0 - num;
        }
        else if (num > 0) {
            ans = num;
        }
        
        return ans;
    }
    
    void addNodeToTailByTail(long long value) {
        Node *p;
        
        if(head == NULL) {
            head = new Node(value, NULL);
            publicHead = head;
            tail = head;
        }
        else {
            p = tail;
            p->next = new Node(value, NULL);
            tail = p->next;
        }
        
    }
    
    long long getWorkAmount() {
        
        long long workAmount = 0;
        
        Node *p = head;
        
        while (p != NULL) {
            workAmount += getAbs(p->data);
            if (p->next != NULL) {
                p->next->data = p->data + p->next->data;
            }

            p = p->next;
        }
        
        return workAmount;
    }
    
    void printListOfValue() {
        Node *p = head;
        while(p != NULL) {
            cout << p->data << "\n";
            p = p->next;
        }
    }
    
};

int main() {
    
    linkedList outList;
    
    int numOfPeople = 0;
    cin >> numOfPeople;
    
    while (numOfPeople > 0) {
        linkedList myList;
        
        for (int i = 0; i < numOfPeople; i++) {
            int input = 0;
            cin >> input;
            myList.addNodeToTailByTail(input);
        }
        
        outList.addNodeToTailByTail(myList.getWorkAmount());
        
        cin >> numOfPeople;
    }
    
    outList.printListOfValue();
    
    return 0;
}