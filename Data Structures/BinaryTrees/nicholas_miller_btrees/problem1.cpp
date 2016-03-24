//
//  main.cpp
//  problem1.cpp is the file name
//  BinaryTreeTraversal1
//
//  Created by Nicholas Miller on 3/18/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>

using std::string;
using std::cout;
using std::cin;

class Node {
public:
    string data;
    int index;
    Node *leftChild;
    Node *rightChild;
    Node *parent;
    
    Node(string x) {
        data = x;
        leftChild = NULL;
        rightChild = NULL;
    }
    Node(int myIndex, string x, Node *left, Node *right) {
        index = myIndex;
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
    
    // LVR
    void inorder() {
        printInorder(publicHead);
    }
    void printInorder(Node* node) {
        if (node == NULL) {
            return;
        }
        printInorder(node->leftChild);
        cout << node->data << " ";
        printInorder(node->rightChild);
    }
    
    // LRV
    void postorder() {
        printPostorder(publicHead);
    }
    void printPostorder(Node* node) {
        if (node == NULL) {
            return;
        }
        printPostorder(node->leftChild);
        printPostorder(node->rightChild);
        cout << node->data << " ";
    }
    
    // VLR
    void preorder() {
        printPreorder(publicHead);
    }
    void printPreorder(Node* node) {
        if (node == NULL) {
            return;
        }
        cout << node->data << " ";
        printPreorder(node->leftChild);
        printPreorder(node->rightChild);
    }
};

int main() {
    
    BinaryTree bt;
    
    int numOfNodes = 0;
    cin >> numOfNodes;
    
    string data = "";
    int leftIndex = 0;
    int rightIndex = 0;
    
    // Array of Node pointers
    Node **nodeArray = new Node*[numOfNodes];
    
    // Make n blank leaf nodes O(n)
    for (int i = 0; i < numOfNodes; i++) {
        Node *temp = new Node(-1, "", NULL, NULL);
        nodeArray[i] = temp;
    }
    
    // Based on the left and right index set the left and right child properly O(n)
    for (int index = 0; index < numOfNodes; index++) {
        cin >> data;
        cin >> leftIndex;
        cin >> rightIndex;
        
        nodeArray[index]->data = data;
        nodeArray[index]->index = index;
        
        // If there is supposed to be a node
        if (leftIndex != -1) {
            nodeArray[index]->leftChild = nodeArray[leftIndex];
        }
        if (rightIndex != -1) {
            nodeArray[index]->rightChild = nodeArray[rightIndex];
        }
    }
    
    // Traverse the tree for the output where the first element is the root O(n) for each
    bt.printPostorder(nodeArray[0]);
    cout << "\n";
    bt.printInorder(nodeArray[0]);
    cout << "\n";
    bt.printPreorder(nodeArray[0]);
    
    // Final time complexity O(n)
    cout << "\n";
    return 0;
}
