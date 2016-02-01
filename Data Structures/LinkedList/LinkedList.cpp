//
//  main.cpp
//  LinkedList
//
//  Created by Nicholas Miller on 1/22/16.
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
    
    int size() {
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
    
    void pointNodeToPosition(Node* myNode, int position) {
        Node *p = getNodeAtPosition(position);
        myNode->next = p;
    }
    void pointNodeToNode(Node* node1, Node* node2) {
        node1->next = node2;
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
    
    void printList() {
        Node *p = head;
        
        while(p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
    }
    
    void printNodeAtPosition(int position) {
        cout << getNodeValueWithPosition(position);
    }
    
//    This method is about 17.37 % faster than the interleaving method below.
    void interleaveMe() {
        int listSize;
        int numOfLists;
        int steps;
        int input;
        int difference;
        
        cin >> listSize;
        
        
        for (int i = 0; i < listSize; i++) {
            cin >> input;
            addNodeToTail(input);
        }
        
        cin >> numOfLists;
        
        for (int i = 0; i < numOfLists; i++) {
            cin >> steps;
            cin >> listSize;
            
            difference = steps + 1;
            
            for (int j = 0; j < listSize; j++) {
                cin >> input;
                
                addNodeAtIndex(steps, input);
                steps = steps + difference;
            }
        }
        
    }
    
//    This takes about 0.000074 more seconds than the interleaveMe method above
//    This is because we have to take the time to add the nodes
    void interleaveMeWithList(linkedList list2, int step) {
        Node *p = head;
        Node *pNext;
        Node *q = list2.head;
        Node *qNext;
        
        
        if (step == 0) {
            list2.getNodeAtPosition(list2.size() - 1)->next = p;
            head = list2.getNodeAtPosition(0);
        }
        else {
            int count = 1;
            int numLeft = list2.size();
            
            while (p != NULL && q != NULL && numLeft > 0) {
                if (count == step) {
                    pNext = p->next;
                    qNext = q->next;
                    
                    q->next = pNext;
                    p->next = q;
                    
                    p = pNext;
                    q = qNext;
                    
                    count = 0;
                    numLeft--;
                }
                else {
                    pNext = p->next;
                    p = pNext;
                    pNext = pNext->next;
                    
                }
                
                count++;
            }
            
            list2.head = q;
        }
        
    }
};
//==========================================================================================================================//


void getInputsAndMakeListsThenInterleave() {
    linkedList list1;
    
    int listSize;
    int numOfLists;
    int steps;
    int input;
    cin >> listSize;
    for (int i = 0; i < listSize; i++) {
        cin >> input;
        list1.addNodeToTail(input);
    }
    cin >> numOfLists;
    for (int i = 0; i < numOfLists; i++) {
        cin >> steps;
        cin >> listSize;
        
        linkedList list2;
        
        for (int j = 0; j < listSize; j++) {
            cin >> input;
            
            list2.addNodeToTail(input);
        }
        
        list1.interleaveMeWithList(list2, steps);
    }
    
    list1.printList();

}

void timeCheck() {
    clock_t begin = clock();
    
//    Method to test
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "The Program took " << elapsed_secs << " seconds";
}

int main(void) {
    linkedList list;
    
    list.interleaveMe();
//    getInputsAndMakeListsThenInterleave();
    
    list.printList();

    cout << "\n";
    return(0);
}
