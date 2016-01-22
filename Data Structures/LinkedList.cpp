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
    
    Node* getNodeWithValue(int value) {
        Node *p = head;
        
        while (p != NULL) {
            if (p->data == value) {
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
    
    void addNodeToTail(int value) {
        Node *p;
        
        if(head == NULL)
            head = new Node(value, NULL);
        else{
            p = head;
            while(p->next != NULL) {
                p = p->next;
            }
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
        Node *p = getNodeAtPosition(position - 1);
        
        if (position == 0) {
            addNodeToHead(value);
        }
        
        if(p != NULL) {
            p->next = new Node(value, p->next);
        }
    }
    
    void addNodeAfterIndex(int position, int value) {
        Node *p = getNodeAtPosition(position);
        
        if(p != NULL) {
            p->next = new Node(value, p->next);
        }
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
            delete nodeToDelete;
            return;
        }
        
        if (getNodePostionWithValue(value) > 0) {
            nodeToDelete = getNodeWithValue(value);
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
            nodeToDelete = getNodeWithValue(value);
            p = getNodeAtPosition(getNodePostionWithValue(value) - 1);
            p->next = nodeToDelete->next;
            delete nodeToDelete;
        }
    }
    
    bool contains(int value) {
        Node *p = head;
        
        while(p != NULL) {
            if (p->data == value) {
                return true;
            }
            p = p->next;
        }
        
        return false;
    }
    
    void printList() {
        Node *p = head;
        
        while(p != NULL) {
            cout << p->data << "\n";
            p = p->next;
        }
    }
    
    void printNode(int position) {
        cout << getNodeValueWithPosition(position);
    }
};


int main(void){
    linkedList list;
    list.addNodeToTail(2);
    list.addNodeToTail(3);
    list.addNodeToTail(4);
    list.addNodeToTail(5);
    list.addNodeToTail(6);
    list.addNodeToTail(7);
    list.addNodeToHead(1);
    list.addNodeAtIndex(0, 0);
    
    list.addNodeToTail(51);
    list.addNodeToTail(51);
    list.addNodeToTail(51);
    list.addNodeToTail(51);
    list.addNodeToTail(51);
    
    list.removeAllNodesWithValue(51);
    
    list.printList();
    
    cout << "\n";
    return(0);
}
