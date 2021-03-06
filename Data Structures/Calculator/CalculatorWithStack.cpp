//
//  main.cpp
//  CalculatorWithHash
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
//#include <unordered_map>

using std::string;
using std::cout;
using std::cin;
using std::stack;
using std::queue;
using std::stringstream;
using std::istringstream;
using std::endl;
//using std::unordered_map;
using std::stoi;
using std::stod;

bool didDivideByZero = false;
bool variableDoesNotExist = false;

// This is just like our node class with a few slight changes
class LinkedHashEntry {
private:
    string key;
    double value;
    LinkedHashEntry *next;
public:
    // This is our constructor and how we are going to make a new node for that particular bucket
    LinkedHashEntry(string key, double value) {
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
    void setValue(double value) {
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
                    put(entry->getKey(), stod(entry->getValue()));
                    oldEntry = entry;
                    entry = entry->getNext();
                    delete oldEntry;
                }
            }
        }
        // Use the system deallocator function so we do not reach memory capacity
        delete[] oldTable;
    }
    
    // This method turns a string into a number so that we can do modulo tablesize to get it into a bucket
    // This is the RSHash function
    // It uses a and b (prime numbers) to manipulate the the numerical value of 'hash'
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
    void put(string key, double value) {
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
// Make a global hashmap so every method can use the same one
// Called it ht because that is the name of my original hashtable implementation below
HashTable ht;

/* This is a basic node class
 *  It constains a string value and two node pointers to its two children
 */
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

/* This is an extension of the buit in unordered map
 *  There is two methods defined so the user can put a value associated with a key
 *  The other is so that you can return a value associated with a key
 */
//class Hashtable {
//    std::unordered_map<string, double> htmap;
//
//public:
//
//    // If the key has no value then set a value else it should change the value at that key
//    void put(string key, double value) {
//        if (get(key) == "NA") {
//            htmap.insert({key,value});
//        }
//        else {
//            htmap.at(key) = value;
//        }
//    }
//
//    // Returns the value of a key or NA if it does not exist
//    string get(string key) {
//        std::unordered_map<std::string,double>::const_iterator got = htmap.find(key);
//        if ( got == htmap.end() ) {
//            return "NA";
//        }
//        else {
//            stringstream ss;
//            ss << got->second;
//            return ss.str();
//        }
//    }
//
//};
//// Make a global hashtable so every method can use the same one
//Hashtable ht;

// This sets a precedence for each token you can encounter
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
        
        // If a right parenthesis is encountered
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
        // If a left parenthesis is encountered
        else if (prec == 0) {
            myStack.push(infix[i]);
        }
        // If a number or decimal is encountered
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
        // If + or - is encountered
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
        // If * or / is encountered
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
        // If ^ is encountered
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
        // If a letter is encountered (it will check the word to see if it is a variable)
        if (prec == -3) {
            string postfix = "";
            
            while (getPrecedence(infix[i]) == -3 && i < infix.size()) {
                postfix += infix[i];
                i++;
            }
            string vari = ht.get(postfix);
            if (vari != "Undeclared-Variable") {
                myQueue.push(vari);
            }
            else if (vari == "Undeclared-Variable") {
                myQueue.push("0");
                variableDoesNotExist = true;
            }
            if (getPrecedence(infix[i]) > -2) {
                i--;
            }
        }
        
        // If there are still operators on the stack at the end it should pop them all
        if (i >= infix.size() - 1) {
            string postfix = "";
            
            while (!myStack.empty()) {
                postfix = myStack.top();
                myQueue.push(postfix);
                myStack.pop();
            }
        }
    }
    
    // We return a queue instead of a string so that we don't ever have to worry about spaces
    // It is easier to differentiate the numbers
    return myQueue;
}

// This is a simple method that returns if a character is a operator or operand
bool isOperator(string token) {
    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
        return true;
    }
    else {
        return false;
    }
}

/* We can do the same evaluation as above but with a stack instead of constructing a tree
 *  The stack computes the result faster than the tree because you don't need to contruct the unique tree
 *  I did the tree just because I wanted to get experience with binary trees because they are a very
 *  common in technical interviews and I am already comfortable with stacks
 */
// This is a method that does all of our operations
float evalFromStack(float op1, float op2, string op) {
    double answer = 0;
    
    if (op == "+") {
        answer = op2 + op1;
    }
    else if (op == "-") {
        answer = op2 - op1;
    }
    else if (op == "*") {
        answer = op2 * op1;
    }
    else if (op == "/") {
        
        // If there is a division by zero flag that this occured and return a zero instead of 'inf'
        if (op1 == 0) {
            didDivideByZero = true;
            answer = 0;
        }
        else if (op1 != 0) {
            answer = op2 / op1;
        }
    }
    else if (op == "^") {
        answer = pow(op2, op1);
    }
    
    return answer;
}

// This makes a stack and does the math based on that
float evalPostfixWithStack(string postfix[], int size) {
    stack<float> s;
    int i = 0;
    string ch;
    float val = 0;
    
    if (size == 1) {
        ch = postfix[0];
        return std::stof(ch);
    }
    
    while (i < size) {
        ch = postfix[i];
        
        // If it is an operand we push it to that stack
        if (!isOperator(ch)) {
            s.push(std::stof(ch));
        }
        
        // If it is an operator we pop off the last two operands and call our stack math function with the operand
        else {
            float op1 = s.top();
            s.pop();
            float op2 = s.top();
            s.pop();
            val = evalFromStack(op1, op2, ch);
            
            // We push the result of the math onto the stack to be used in the next case
            s.push(val);
        }
        i++;
    }

    return val;
}

int main(int argc, const char * argv[]) {
    
    // So that cin and cout are as fast as scanf
    std::ios::sync_with_stdio(false);
    
    string infix = "";
    
    while (infix != "quit") {
        
        didDivideByZero = false;
        variableDoesNotExist = false;
        bool isVari = true;
        
        // Take in a line and delete all of the spaces in it
        getline(cin, infix);
        infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());
        
        // Create an array of size two where ele 1 is the variable and ele 2 is the equation
        string *expression = new string[2];
        expression[0] = "";
        expression[1] = "";
        
        // If the first 3 characters are 'let' set the variable name and equation to right ele's
        if (infix.substr(0,3) == "let") {
            int positionEqual = int(infix.find('='));
            expression[0] = infix.substr(3, positionEqual - 3);
            expression[1] = infix.substr(positionEqual + 1);
            
            isVari = false;
        }
        
        // If there is no let then we assume that only an equation was entered
        else if (infix.substr(0,3) != "let") {
            expression[0] = "";
            expression[1] = infix.substr(0);
        }
        
        // Check to see if there is an equation or if the user wants a value of one variable
        for (int i = 0; i < infix.size(); i++) {
            string s = "";
            s = infix[i];
            if (isOperator(s)) {
                isVari = false;
                i = int(infix.size());
            }
        }
        
        // If one variable is entered only then print that value
        if (isVari) {
            if (infix != "quit") {
                cout << ht.get(&infix[0]) << "\n";
            }
        }
        
        // If there is an equation then do all the changes and math
        if (!isVari) {
            
            // Go from the infix string to a queue of the postfix where each ele of the queue is an ele of the postfix
            queue<string> myQueue;
            myQueue = infixToPostfix(expression[1]);
            
            // If there are no undeclared variables make the tree and do the math
            if (!variableDoesNotExist) {
                
                // Put the results of the queue into an array so it is easier to deal with for me
                int size = int(myQueue.size());
                string *postfixArray = new string[myQueue.size()];
                int i = 0;
                while (!myQueue.empty()) {
                    postfixArray[i] = myQueue.front();
                    myQueue.pop();
                    i++;
                }
                
                // Compute the answer of the binary expression tree
                double answer = evalPostfixWithStack(postfixArray, size);
                
                // If the result is not a division by zero and the user is not setting a variable print the answer
                if (infix.substr(0,3) != "let" && !didDivideByZero) {
                    cout << answer << "\n";
                }
                
                // If the result is not a division by zero store the answer into the hashtable with key 'ans'
                if (!didDivideByZero) {
                    ht.put("ans", answer);
                    
                    // If there was a let (variable name) entered then store the result to that variable with that key
                    if (expression[0] != "") {
                        ht.put(expression[0], answer);
                    }
                }
                else if (didDivideByZero){
                    cout << "Division-By-Zero\n";
                }
            }
            else if (variableDoesNotExist) {
                cout << "Undeclared-Variable\n";
            }
        }
    }
    
    cout << "\n";
    return 0;
}