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
    else {
        return -2;
    }
}

//string infixToPostfix(string infix) {
//    stack<char> myStack;
//    string postfix = "";
//    int prec = 0;
//    
//    int i = 0;
//    
//    for (i = 0; i < infix.size(); i++) {
//
//        if (infix[i] != ' ' ) {
//            prec = getPrecedence(infix[i]);
//            
//            if (prec == -1) {
//                while (!myStack.empty() && myStack.top() != '(') {
//                    postfix = postfix + myStack.top() + ' ';
//                    myStack.pop();
//                }
//                if (myStack.top() == '(') {
//                    myStack.pop();
//                }
//            }
//            else if (prec == 0) {
//                myStack.push(infix[i]);
//            }
//            else if (prec == 1) {
//                while (getPrecedence(infix[i]) == 1) {
//                    postfix = postfix + infix[i];
//                    i++;
//                }
//                postfix = postfix + ' ';
//            }
//            else if (prec == 2) {
//                if (!myStack.empty()) {
//                    if (prec > (getPrecedence(myStack.top()))) {
//                        myStack.push(infix[i]);
//                    }
//                    else {
//                        postfix = postfix + myStack.top() + ' ';
//                        myStack.pop();
//                        myStack.push(infix[i]);
//                    }
//                }
//                else {
//                    myStack.push(infix[i]);
//                }
//            }
//            else if (prec == 3) {
//                if (!myStack.empty()) {
//                    if (prec > (getPrecedence(myStack.top()))) {
//                        myStack.push(infix[i]);
//                    }
//                    else {
//                        postfix = postfix + myStack.top() + ' ';
//                        myStack.pop();
//                        myStack.push(infix[i]);
//                    }
//                }
//                else {
//                    myStack.push(infix[i]);
//                }
//            }
//            else if (prec == 4) {
//                if (!myStack.empty()) {
//                    if (prec >= (getPrecedence(myStack.top()))) {
//                        myStack.push(infix[i]);
//                    }
//                }
//                else {
//                    myStack.push(infix[i]);
//                }
//            }
//        }
//        
//        if (i >= infix.size() - 1) {
//            while (!myStack.empty()) {
//                postfix = postfix + myStack.top() + ' ';
//                myStack.pop();
//            }
//        }
//    }
//    
//    return postfix;
//}

queue<string> infixToPostfix(string infix) {
    queue<string> myQueue;
    
    stack<char> myStack;
    int prec = 0;
    
    int i = 0;
    
    for (i = 0; i < infix.size(); i++) {
        
        if (infix[i] != ' ' ) {
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

int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    
    string infix;
    getline(cin, infix);
    
//    string postfix = infixToPostfix(infix);
//    cout << postfix;
    
    queue<string> myQueue;
    myQueue = infixToPostfix(infix);
    int size = int(myQueue.size());
    
    string *infixArray = new string[myQueue.size()];
    int i = 0;
    while (!myQueue.empty()) {
        infixArray[i] = myQueue.front();
        myQueue.pop();
        i++;
    }
    
    cout << "\n";
    return 0;
}
