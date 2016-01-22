//
//  main.cpp
//  LinkedList
//
//  Created by Nicholas Miller on 1/22/16.
//  Copyright © 2016 Nicholas Miller. All rights reserved.
//

#include <iostream>

//This is more efficient because we don't have to look through all of std to find cout.
//using namespace std;
using std::cout;

class Node{
public:
    int data;
    Node * next;
    
    Node(int x) {
        data = x;
        next = NULL;
    }
    Node(int x, Node * y) {
        data = x;
        next = y;
    }
};


class linkedList{
    Node *head;
public:
    
    linkedList(){
        head = NULL;
    }
    
    Node* getNode(int position) {
        Node *p = head;
        
        while (position--) {
            if (p != NULL)
                p = p->next;
            else
                return NULL;
        }
        return p;
    }
    
    void addNodeToTail(int value) {
        Node *p;
        
        if(head == NULL)
            head = new Node(value, NULL);
        else{
            p = head;
            while(p->next != NULL)
                p = p->next;
            p->next = new Node(value, NULL);
        }
    }
    
    void addNodeToHead(int value) {
        Node *p;
        
        if (head == NULL) {
            head = new Node(value, NULL);
        }
        else {
            p = head;
            Node *node = new Node(value);
            node->next = p;
            head = node;
        }
    }
    
    void addNodeAtIndex(int position, int value) {
        Node *p = getNode(position - 1);
        
        if (position == 0) {
            addNodeToHead(value);
        }
        
        if(p != NULL) {
            p->next = new Node(value, p->next);
        }
    }
    
    void addNodeAfterIndex(int position, int value) {
        Node *p = getNode(position);
        
        if(p != NULL) {
            p->next = new Node(value, p->next);
        }
    }
    
    void removeNodeWithValue(int value) {
        
    }
    
    void printList() {
        Node *p = head;
  
        while(p != NULL){
            cout << p->data << "\n";
            p = p->next;
        }
    }
    
    void printNode(int position) {
        Node *p = getNode(position);
        cout << p->data;
    }
};


int main(void){
    linkedList list;
    list.addNodeToTail(1);
    list.addNodeToTail(2);
    list.addNodeToTail(4);
    list.addNodeToTail(5);
    list.addNodeToTail(6);
    list.addNodeToTail(7);
    list.addNodeToHead(0);
    
    list.addNodeAtIndex(0, 33);
    
    list.printList();
    
    cout << "\n";
    return(0);
}
