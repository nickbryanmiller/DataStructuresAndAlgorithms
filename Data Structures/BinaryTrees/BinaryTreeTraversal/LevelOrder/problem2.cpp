//
//  main.cpp
//  BinaryTreeTraversal2
//  problem2.cpp is the file name
//
//  Created by Nicholas Miller on 3/18/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>
#include <queue>

using std::string;
using std::cout;
using std::cin;
using std::queue;

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
    
//    // O(n^2)
//    int height(Node* node) {
//        if (node == NULL) {
//            return 0;
//        }
//        else {
//            // compute the height of the two subtrees
//            int leftHeight = height(node->leftChild);
//            int rightHeight = height(node->rightChild);
//            
//            // return the larger of the two
//            if (leftHeight > rightHeight) {
//                return(leftHeight+1);
//            }
//            else {
//                return(rightHeight+1);
//            }
//        }
//    }
//    void printLevel(Node* root, int level) {
//        if (root == NULL) {
//            return;
//        }
//        if (level == 1) {
//            cout << root->data << " ";
//        }
//        else if (level > 1) {
//            printLevel(root->leftChild, level-1);
//            printLevel(root->rightChild, level-1);
//        }
//    }
//    void printLevelOrder(Node* root) {
//        
//        // grab the height of the larger subtree
//        int h = height(root);
//        
//        // i = 1 because the root is level one
//        for (int i = 1; i <= h; i++) {
//            printLevel(root, i);
//        }
//    }

    
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
    
    // Traverse the tree for the output where the first element is the root O(n)
    bt.printLevelOrder(nodeArray[0]);
    
    // Final time complexity O(n)
    cout << "\n";
    return 0;
}
