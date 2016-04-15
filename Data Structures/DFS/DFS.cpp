//
//  main.cpp
//  DFS
//
//  Created by Nicholas Miller on 4/11/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>
#include <list>

bool isATree = true;

class Graph {
    
    int numOfVertices;
    std::list<int> *adjList;
    
    void doDFS(int vertexIndex, bool visited[]) {
        // Mark the current vertex as visited
        visited[vertexIndex] = true;
        
        // Go through the vertices adjacent to the vertex
        std::list<int>::iterator i;
        for (i = adjList[vertexIndex].begin(); i != adjList[vertexIndex].end(); ++i) {
            if (!visited[*i]) {
                doDFS(*i, visited);
            }
            else if (visited[*i]) {
                isATree = false;
            }
        }
    }
    
public:
    
    Graph(int numOfVertices) {
        this->numOfVertices = numOfVertices;
        adjList = new std::list<int>[numOfVertices];
    }
    
    void addEdge(int v1, int v2) {
        // Add v2 to v1’s list.
        adjList[v1].push_back(v2);
    }
    
    void dFSParticular(int v) {
        // Mark all the nodes as not visited
        bool *visited = new bool[numOfVertices];
        for (int i = 0; i < numOfVertices; i++) {
            visited[i] = false;
        }
        
        doDFS(v, visited);
    }
    
    void dFSAll() {
        // Mark all vertices as not visited
        bool *visited = new bool[numOfVertices];
        for (int i = 0; i < numOfVertices; i++) {
            visited[i] = false;
        }
        
        for (int i = 0; i < numOfVertices; i++) {
            if (visited[i] == false) {
                doDFS(i, visited);
            }
        }
    }
};

int main() {
    
    int numOfVertices = 0;
    int numOfEdges = 0;
    
    std::cin >> numOfVertices;
    std::cin >> numOfEdges;
    
    // Because the array starts at zero
    Graph myG(numOfVertices + 1);
    
    for (int i = 0; i < numOfEdges; i++) {
        int v1 = 0;
        int v2 = 0;
        
        std::cin >> v1;
        std::cin >> v2;
        
        myG.addEdge(v1, v2);
    }
    
    myG.dFSAll();
    
    if (isATree) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    
    std::cout << "\n";
    return 0;
}
