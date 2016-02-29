//
//  main.cpp
//  ScientificCalculator
//
//  Created by Nicholas Miller on 2/29/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <iterator>

using std::string;
using std::cout;
using std::cin;
using std::stack;
using std::queue;
using std::stringstream;
using std::istringstream;
using std::endl;

class Node{
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

int getPrecedence(char token) {
    if (token == ')') {
        return -1;
    }
    else if (token == '(') {
        return 0;
    }
    else if (token == '^') {
        return 4;
    }
    else if (token == '*' || token == '/') {
        return 3;
    }
    else if (token == '+' || token == '-') {
        return 2;
    }
    else if (token == '0' || token == '1' || token == '2' || token == '3' || token == '4' || token == '5' || token == '6' || token == '7' || token == '8' || token == '9' || token == '.') {
        return 1;
    }
    else if (token == ' '){
        return -2;
    }
    else {
        return -3;
    }
}

queue<string> infixToPostfix(string infix) {
    queue<string> myQueue;
    
    stack<char> myStack;
    int prec = 0;
    
    int i = 0;
    
    for (i = 0; i < infix.size(); i++) {
        
        prec = getPrecedence(infix[i]);
        
        if (prec == -1) {
            string postfix = "";
            
            while (!myStack.empty() && myStack.top() != '(') {
                postfix = myStack.top();
                myQueue.push(postfix);
                myStack.pop();
            }
            if (myStack.top() == '(') {
                myStack.pop();
            }
        }
        else if (prec == 0) {
            myStack.push(infix[i]);
        }
        else if (prec == 1) {
            string postfix = "";
            
            while (getPrecedence(infix[i]) == 1) {
                postfix = postfix + infix[i];
                i++;
            }
            myQueue.push(postfix);
            if (getPrecedence(infix[i]) > -2) {
                i--;
            }
        }
        else if (prec == 2) {
            
            string postfix = "";
            
            if (!myStack.empty()) {
                if (prec > (getPrecedence(myStack.top()))) {
                    myStack.push(infix[i]);
                }
                else {
                    postfix = myStack.top();
                    myQueue.push(postfix);
                    myStack.pop();
                    while (!myStack.empty() && getPrecedence(myStack.top()) == 2) {
                        postfix = myStack.top();
                        myQueue.push(postfix);
                        myStack.pop();
                    }
                    myStack.push(infix[i]);
                }
            }
            else {
                myStack.push(infix[i]);
            }
        }
        else if (prec == 3) {
            string postfix = "";
            
            if (!myStack.empty()) {
                if (prec > (getPrecedence(myStack.top()))) {
                    myStack.push(infix[i]);
                }
                else {
                    postfix = myStack.top();
                    myQueue.push(postfix);
                    myStack.pop();
                    while (!myStack.empty() && getPrecedence(myStack.top()) == 3) {
                        postfix = myStack.top();
                        myQueue.push(postfix);
                        myStack.pop();
                    }
                    myStack.push(infix[i]);
                }
            }
            else {
                myStack.push(infix[i]);
            }
        }
        else if (prec == 4) {
            string postfix = "";
            
            if (!myStack.empty()) {
                if (prec >= (getPrecedence(myStack.top()))) {
                    myStack.push(infix[i]);
                }
            }
            else {
                myStack.push(infix[i]);
            }
        }
        
        if (i >= infix.size() - 1) {
            string postfix = "";
            
            while (!myStack.empty()) {
                postfix = myStack.top();
                myQueue.push(postfix);
                myStack.pop();
            }
        }
    }
    
    return myQueue;
}

bool isOperator(string token) {
    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
        return true;
    }
    else {
        return false;
    }
}

Node* createTreeWithPostfix(string postfix[], int size) {
    stack<Node*> st;
    
    Node *root;
    Node *right;
    Node *left;
    
    // Traverse through every character
    for (int i=0; i< size; i++) {
        // If operand push to stack
        if (!isOperator(postfix[i])) {
            root = new Node(postfix[i]);
            st.push(root);
        }
        else {
            root = new Node(postfix[i]);
            
            // Pop two top nodes
            right = st.top(); // Store top
            st.pop();      // Remove top
            left = st.top();
            st.pop();
            
            //  make them children
            root->rightChild = right;
            root->leftChild = left;
            
            // Add this subexpression to stack
            st.push(root);
        }
    }

    root = st.top();
    st.pop();
    
    return root;
}

void inorder(Node *t) {
    if(t) {
        inorder(t->leftChild);
        cout << t->data << " ";
        inorder(t->rightChild);
    }
}

double doMathFromTree(double a, double b, string op) {
    double answer = 0;
    
    if (op == "+") {
        answer = a + b;
    }
    else if (op == "-") {
        answer = a - b;
    }
    else if (op == "*") {
        answer = a * b;
    }
    else if (op == "/") {
        answer = a / b;
    }
    else if (op == "^") {
        answer = pow(a, b);
    }

    return answer;
}

double evaluatetree(Node *x){
    
    if (x != NULL) {
        if (!isOperator(x->data)) {
            return stod(x->data);
        }
        else if (isOperator(x->data)) {
            
            double a = evaluatetree(x->leftChild);
            double b = evaluatetree(x->rightChild);
            
            return doMathFromTree(a, b, x->data);
        }
    }
    
    return 0;
}

//int evalFromStack(int op1, int op2, string operate) {
//    switch (operate[0]) {
//        case '*': return op2 * op1;
//        case '/': return op2 / op1;
//        case '+': return op2 + op1;
//        case '-': return op2 - op1;
//        default : return 0;
//    }
//}
//int evalPostfixWithStack(string postfix[], int size) {
//    stack<int> s;
//    int i = 0;
//    string ch;
//    int val = 0;
//    while (i < size) {
//        ch = postfix[i];
//        if (!isOperator(ch)) {
//            // we saw an operand
//            // push the digit onto stack
//            s.push(std::stoi(ch));
//        }
//        else {
//            // we saw an operator
//            // pop off the top two operands from the
//            // stack and evalute them using the current
//            // operator
//            int op1 = s.top();
//            s.pop();
//            int op2 = s.top();
//            s.pop();
//            val = evalFromStack(op1, op2, ch);
//            // push the value obtained after evaluating
//            // onto the stack
//            s.push(val);
//        }
//        i++;
//    }
//    return val;
//}


int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    
    string infix = "";
    getline(cin, infix);
    infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());
    cout << infix << "\n";
    
//    string *expression = new string[2];
//    expression[0] = "";
//    expression[1] = "";
//    if (infix.substr(0,3) == "let") {
//        int positionEqual = int(infix.find('='));
//        expression[0] = infix.substr(3, positionEqual - 3);
//        expression[1] = infix.substr(positionEqual + 1);
//    }
//    cout << expression[0] << "\t" << expression[1];
    
    queue<string> myQueue;
    myQueue = infixToPostfix(infix);
    int size = int(myQueue.size());
    
    string *postfixArray = new string[myQueue.size()];
    int i = 0;
    while (!myQueue.empty()) {
        postfixArray[i] = myQueue.front();
        myQueue.pop();
        i++;
    }
    
    Node *root = createTreeWithPostfix(postfixArray, size);
    double answer = evaluatetree(root);
    cout << "\n" << answer;
    
//    int answer = evalPostfixWithStack(postfixArray, size);
//    cout << "\n" << answer;
    
//    for (int i = 0; i < size; i++) {
//        cout << postfixArray[i] << " ";
//    }
    
    cout << "\n";
    return 0;
}
