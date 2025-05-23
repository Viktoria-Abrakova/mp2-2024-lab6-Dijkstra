#include "graph.h"
#include <iostream>

Graph::Graph(size_t vertices) : numVertices(vertices), adjacencyMatrix(vertices, myVector<int>(vertices, -1)) {
    if (vertices == 0) {
        throw std::invalid_argument("Number of vertices must be positive");
    }
    for (size_t i = 0; i < vertices; ++i) {
        adjacencyMatrix[i][i] = 0;
    }
}

void Graph::addEdge(size_t u, size_t v, int weight) {
    if (weight <= 0) {
        throw std::invalid_argument("Edge weight must be positive");
    }
    if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
        throw std::out_of_range("Vertex index out of range");
    }
    if (adjacencyMatrix[u][v] != -1) {
        throw std::logic_error("Edge already exists. Multiple edges are not supported.");
    }
    adjacencyMatrix[u][v] = weight;
    adjacencyMatrix[v][u] = weight; 
}

bool Graph::isConnected() const {
    myVector<bool> visited(numVertices, false);
    Stack<size_t> stack;
    stack.push(0);
    visited[0] = true;
    size_t count = 1;

    while (!stack.empty()) {
        size_t current = stack.top();
        stack.pop();

        for (size_t neighbor = 0; neighbor < numVertices; ++neighbor) {
            if (adjacencyMatrix[current][neighbor] != -1 && !visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
                count++;
            }
        }
    }

    return count == numVertices;
}

void Graph::printGraph() const {
    std::cout << "Матрица смежности (" << numVertices << " вершин):\n";
    for (size_t i = 0; i < numVertices; ++i) {
        for (size_t j = 0; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] == -1) std::cout << "- ";
            else std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int Graph::getEdgeWeight(size_t u, size_t v) const {
    if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
        throw std::out_of_range("Vertex index out of range");
    }
    return adjacencyMatrix[u][v];
}

myVector<int> Graph::getPath(int start, int end, const myVector<int>& predecessors) const {
    myVector<int> path;
    Stack<int> tempPath;

    for (int at = end; at != -1; at = predecessors[at]) {
        tempPath.push(at);
        if (at == start) break; 
    }

    if (tempPath.top() != start) {
        return {}; 
    }

    while (!tempPath.empty()) {
        path.push_back(tempPath.top());
        tempPath.pop();
    }

    return path;
}