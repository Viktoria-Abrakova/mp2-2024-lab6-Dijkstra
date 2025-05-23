#pragma once
#include "stack.h"

class Graph {
private:
    size_t numVertices;
    myVector<myVector<int>> adjacencyMatrix;

public:
    explicit Graph(size_t vertices);

    void addEdge(size_t u, size_t v, int weight);
    bool isConnected() const;
    void printGraph() const;

    size_t getNumVertices() const { return numVertices; }
    int getEdgeWeight(size_t u, size_t v) const;
    const myVector<myVector<int>>& getAdjacencyMatrix() const { return adjacencyMatrix; }
    myVector<int> getPath(int start, int end, const myVector<int>& predecessors) const;
};