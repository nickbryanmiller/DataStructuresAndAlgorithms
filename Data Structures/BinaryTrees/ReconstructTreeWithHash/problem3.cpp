//
//  main.cpp
//  BinaryTreeTraversal3
//  problem3.cpp is the file name
//
//  Created by Nicholas Miller on 3/18/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>
#include <queue>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::queue;
using std::stringstream;
//using std::stoi;

// This is just like our node class with a few slight changes
class LinkedHashEntry {
private:
    string key;
    int value;
    LinkedHashEntry *next;
public:
    // This is our constructor and how we are going to make a new node for that particular bucket
    LinkedHashEntry(string key, int value) {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
    string getKey() {
        return key;
    }
    string getValue() {
        stringstream ss;
        ss << value;
        return ss.str();
    }
    void setValue(int value) {
        this->value = value;
    }
    LinkedHashEntry *getNext() {
        return next;
    }
    void setNext(LinkedHashEntry *next) {
        this->next = next;
    }
};

// Can store a default of 128 elements (2^7 = 8 bits to use);
const int DEFAULT_TABLE_SIZE = 128;

/*
 * This is a basic implementation of a hashmap with chaining (a linked list at each array index bucket)
 */
class HashTable {
private:
    float threshold;
    int maxSize;
    int tableSize;
    int size;
    
    // Double pointer because a LIST of entries is a table
    LinkedHashEntry **table;
    
    // This is standard library method for hashing a string (returns a size_t)
//    std::hash<std::string> str_hash;
    
    // If we every reach 128 entries we make a new table double the original size and copy the old table over
    void resize() {
        int oldTableSize = tableSize;
        tableSize *= 2;
        maxSize = (int) (tableSize * threshold);
        LinkedHashEntry **oldTable = table;
        table = new LinkedHashEntry*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = NULL;
        }
        size = 0;
        for (int hash = 0; hash < oldTableSize; hash++) {
            if (oldTable[hash] != NULL) {
                LinkedHashEntry *oldEntry;
                LinkedHashEntry *entry = oldTable[hash];
                while (entry != NULL) {
                    
                    int value;
                    std::stringstream convert;
                    convert << entry->getValue();
                    convert >> value;
                    put(entry->getKey(), value);
                    
//                    put(entry->getKey(), stoi(entry->getValue()));
                    oldEntry = entry;
                    entry = entry->getNext();
                    delete oldEntry;
                }
            }
        }
        // Use the system deallocator function so we do not reach memory capacity
        delete[] oldTable;
    }
    
    size_t hashMe(const std::string& str) {
        size_t b = 378551;
        size_t a = 63689;
        size_t hash = 0;
        
        for(std::size_t i = 0; i < str.length(); i++) {
            hash = hash * a + str[i];
            a = a * b;
        }
        return hash;
    }
    
public:
    HashTable() {
        // Specify so that it is a float constant to the compiler
        // 0.75 is recommended for max memory efficiency and time efficiency
        threshold = 0.75f;
        maxSize = 100;
        tableSize = DEFAULT_TABLE_SIZE;
        size = 0;
        table = new LinkedHashEntry*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = NULL;
        }
    }
    
    // This sets the maximum size so we can check when we start reaching capacity
    void setThreshold(float threshold) {
        this->threshold = threshold;
        maxSize = (int) (tableSize * threshold);
    }
    
    // Returns the value associated with a key else returns 'NA'
    string get(string key) {
        // Modular tablesize is used to get the index because it is an even number and not many collisions occur
        // It might be useful to find the nearest prime around tablesize instead
//        int hash = (str_hash(key) % tableSize);
        int hash = (hashMe(key) % tableSize);
        if (table[hash] == NULL) {
            return "Undeclared-Variable";
        }
        // If the position is not null we travel the linked list looking for the same key
        else {
            LinkedHashEntry *entry = table[hash];
            while (entry != NULL && entry->getKey() != key) {
                entry = entry->getNext();
            }
            if (entry == NULL) {
                return "Undeclared-Variable";
            }
            else {
                return entry->getValue();
            }
        }
    }
    
    // This method sets a value for a particular key
    void put(string key, int value) {
//        int hash = (str_hash(key) % tableSize);
        int hash = (hashMe(key) % tableSize);
        
        // If the index is null we make a new node in that bucket with the key/value pair
        if (table[hash] == NULL) {
            table[hash] = new LinkedHashEntry(key, value);
            size++;
        }
        
        // Else we search the bucket to make sure it does not exist before adding it
        else {
            LinkedHashEntry *entry = table[hash];
            while (entry->getNext() != NULL && entry->getKey() != key) {
                entry = entry->getNext();
            }
            if (entry->getKey() == key) {
                entry->setValue(value);
            }
            else {
                entry->setNext(new LinkedHashEntry(key, value));
                size++;
            }
        }
        
        // If our size ever reaches the max size we double the table and copy the data over.
        if (size >= maxSize) {
            resize();
        }
    }
};
// Make a global hashtable so every method can use the same one
HashTable ht;

class Node {
public:
    string data;
    Node *leftChild;
    Node *rightChild;
    Node *parent;
    
    Node(string x) {
        data = x;
        leftChild = NULL;
        rightChild = NULL;
    }
    Node(string x, Node *left, Node *right) {
        data = x;
        leftChild = left;
        rightChild = right;
    }
};

class BinaryTree {
private:
    Node *head;
    
public:
    Node *publicHead;
    
    BinaryTree() {
        head = NULL;
        publicHead = NULL;
    }
    
    Node* constructTree(string inorder[], string postorder[], int maxSize) {
        int inStart = 0;
        int inEnd = maxSize - 1;
        int postStart = 0;
        int postEnd = maxSize - 1;
        
        return constructTreeRecursion(inorder, inStart, inEnd, postorder, postStart, postEnd, maxSize);
    }
    
    Node* constructTreeRecursion(string inorder[], int inStart, int inEnd, string postorder[], int postStart, int postEnd, int maxSize) {
        
        // If we have recursed our max limit for either inorder[] or postorder[]
        if (inStart > inEnd || postStart > postEnd) {
            return NULL;
        }
        
        // Last element in the postorder is the root of the tree
        string rootValue = postorder[postEnd];
        Node *root = new Node(rootValue);
        
        // The location of the string (started in postorder) found in the inorder array
        // O(n) every call making it O(n^2)
//        int j = 0;
//        for (int i = 0; i < maxSize; i++) {
//            if (inorder[i] == rootValue) {
//                j = i;
//                break;
//            }
//        }
        
        // O(1) to grab average case
        string index = ht.get(rootValue);
//        int j = stoi(index);
        int j;
        
        std::stringstream convert;
        convert << index;
        convert >> j;
        
        // Need to set the left of the tree from the smaller array to the left of the root
        root->leftChild = constructTreeRecursion(inorder, inStart, j - 1, postorder, postStart, postStart + j - (inStart + 1), maxSize);
        
        // Need to set the right of the tree from the smaller array to the right of the root
        root->rightChild = constructTreeRecursion(inorder, j + 1, inEnd, postorder, postStart + j - inStart, postEnd - 1, maxSize);
        
        return root;
    }
    
    // O(n)
    void printLevelOrder(Node *root) {
        if (root == NULL) {
            return;
        }
        
        queue<Node*> myQueue;
        
        // Push the root of the tree first
        myQueue.push(root);
        
        while (myQueue.empty() == false) {
            // cout the front and delete it
            Node *node = myQueue.front();
            cout << node->data << " ";
            myQueue.pop();
            
            // Push all children in order. The queue will keep them in place
            if (node->leftChild != NULL) {
                myQueue.push(node->leftChild);
            }
            if (node->rightChild != NULL) {
                myQueue.push(node->rightChild);
            }
        }
    }
    
};

int main() {
    
//    std::ios::sync_with_stdio(false);
    
    BinaryTree bt;
    
    int numOfNodes = 0;
    cin >> numOfNodes;
    
    string data = "";
    
    string *postorder = new string[numOfNodes];
    string *inorder = new string[numOfNodes];
    
    // O(n)
    for (int i = 0; i < numOfNodes; i++) {
        cin >> data;
        postorder[i] = data;
    }
    // O(n)
    for (int i = 0; i < numOfNodes; i++) {
        cin >> data;
        inorder[i] = data;
        
        // O(1) average case unless they all cache to one bin but that would only happen if the same data
        ht.put(data, i);
        
    }
    
    // O(n)
    Node *root = bt.constructTree(inorder, postorder, numOfNodes);
    
    
    // Traverse the tree for the output where the first element is the root O(n)
    bt.printLevelOrder(root);
    
    // Final time complexity O(n)
    cout << "\n";
    return 0;
}
