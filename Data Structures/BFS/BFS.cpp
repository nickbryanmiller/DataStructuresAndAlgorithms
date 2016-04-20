//
//  main.cpp
//  BFS
//
//  Created by Nicholas Miller on 4/15/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>
#include <queue>

class Node {
private:
    int row = 0;
    int col = 0;
    char id = 'a';
public:
    Node(int r, int c, char identity) {
        row = r;
        col = c;
        id = identity;
    }
    
    int getRow() {
        return row;
    }
    int getCol() {
        return col;
    }
    int getId() {
        return id;
    }
};

void clearBoard(int **myBoard, int numOfRows, int numOfCols) {
    
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < numOfCols; j++) {
            myBoard[i][j] = 0;
        }
    }
}

bool doBFS(int **myBoard, int numOfRows, int numOfCols, std::queue<Node> myQueue) {
    
    int mRow = 0;
    int mCol = 0;
    
    int cRow = 0;
    int cCol = 0;
    
    while (!myQueue.empty()) {
        while (!myQueue.empty() && myQueue.front().getId() == 1) {
            mRow = myQueue.front().getRow();
            mCol = myQueue.front().getCol();
            myQueue.pop();
            
            if (myBoard[mRow][mCol] != 1) {
                continue;
            }
            if (mRow <= 0 || mRow >= numOfRows - 1 || mCol <= 0 || mCol >= numOfCols - 1) {
                return true;
            }
            if (mRow < numOfRows - 1 && myBoard[mRow + 1][mCol] == 0) {
                myBoard[mRow + 1][mCol] = 1;
                myQueue.push(Node(mRow + 1, mCol, 1));
            }
            if (mRow > 0 && myBoard[mRow - 1][mCol] == 0) {
                myBoard[mRow - 1][mCol] = 1;
                myQueue.push(Node(mRow - 1, mCol, 1));
            }
            if (mCol < numOfCols - 1 && myBoard[mRow][mCol + 1] == 0) {
                myBoard[mRow][mCol + 1] = 1;
                myQueue.push(Node(mRow, mCol + 1, 1));
            }
            if (mCol > 0 && myBoard[mRow][mCol - 1] == 0) {
                myBoard[mRow][mCol - 1] = 1;
                myQueue.push(Node(mRow, mCol - 1, 1));
            }
        }
        
        while (!myQueue.empty() && myQueue.front().getId() == 2) {
            cRow = myQueue.front().getRow();
            cCol = myQueue.front().getCol();
            myQueue.pop();
            
            if (cRow < numOfRows - 1 && myBoard[cRow + 1][cCol] != 2) {
                myBoard[cRow + 1][cCol] = 2;
                myQueue.push(Node(cRow + 1, cCol, 2));
            }
            if (cRow > 0 && myBoard[cRow - 1][cCol] != 2) {
                myBoard[cRow - 1][cCol] = 2;
                myQueue.push(Node(cRow - 1, cCol, 2));
            }
            if (cCol < numOfCols - 1 && myBoard[cRow][cCol + 1] != 2) {
                myBoard[cRow][cCol + 1] = 2;
                myQueue.push(Node(cRow, cCol + 1, 2));
            }
            if (cCol > 0 && myBoard[cRow][cCol - 1] != 2) {
                myBoard[cRow][cCol - 1] = 2;
                myQueue.push(Node(cRow, cCol - 1, 2));
            }
        }
    }
    
    return false;
}

int main() {
    
    int numOfRows = 0;
    std::cin >> numOfRows;
    
    int numOfCols = 0;
    std::cin >> numOfCols;
    
    int **myBoard = new int*[numOfRows];
    for(int i = 0; i < numOfRows; ++i) {
        myBoard[i] = new int[numOfCols];
    }
    
    clearBoard(myBoard, numOfRows, numOfCols);
    
    int numOfCases = 0;
    std::cin >> numOfCases;
    
    std::string *outArray = new std::string[numOfCases];
    
    for (int i = 0; i < numOfCases; i++) {
        int mRow = 0;
        std::cin >> mRow;
        mRow = mRow - 1;
        
        int mCol = 0;
        std::cin >> mCol;
        mCol = mCol - 1;
        
        int c1Row = 0;
        std::cin >> c1Row;
        c1Row = c1Row - 1;
        
        int c1Col = 0;
        std::cin >> c1Col;
        c1Col = c1Col - 1;
        
        int c2Row = 0;
        std::cin >> c2Row;
        c2Row = c2Row - 1;
        
        int c2Col = 0;
        std::cin >> c2Col;
        c2Col = c2Col - 1;
        
        myBoard[mRow][mCol] = 1;
        myBoard[c1Row][c1Col] = 2;
        myBoard[c2Row][c2Col] = 2;
        
        std::queue<Node> myQueue;
        myQueue.push(Node(mRow, mCol, 1));
        myQueue.push(Node(c1Row, c1Col, 2));
        myQueue.push(Node(c2Row, c2Col, 2));
        
        bool success = doBFS(myBoard, numOfRows, numOfCols, myQueue);
        
        if (success) {
            outArray[i] = "YES";
        }
        else {
            outArray[i] = "NO";
        }
        
        clearBoard(myBoard, numOfRows, numOfCols);
        
    }
    
    for (int j = 0; j < numOfCases; j++) {
        std::cout << outArray[j] << "\n";
    }
    
    return 0;
}
