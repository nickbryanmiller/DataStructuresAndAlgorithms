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

using std::string;
using std::cout;
using std::cin;
using std::queue;

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
        
        // The location of the parent (found in postorder) in the inorder array
        int j = 0;
        for (int i = 0; i < maxSize; i++) {
            if (inorder[i] == rootValue) {
                j = i;
                break;
            }
        }
        
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
    
    string *postorder = new string[numOfNodes];
    string *inorder = new string[numOfNodes];
    
    for (int i = 0; i < numOfNodes; i++) {
        cin >> data;
        postorder[i] = data;
    }
    for (int i = 0; i < numOfNodes; i++) {
        cin >> data;
        inorder[i] = data;
    }
    
    Node *root = bt.constructTree(inorder, postorder, numOfNodes);
    
    
    // Traverse the tree for the output where the first element is the root O(n)
    bt.printLevelOrder(root);
    
    // Final time complexity O(n)
    cout << "\n";
    return 0;
}
