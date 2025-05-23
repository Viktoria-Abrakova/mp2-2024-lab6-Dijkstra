#pragma once
#include "graph.h"
#include "dHeap.h"
#include "binomialHeap.h"  

struct HeapNode {
    int vertex;
    int distance;

    bool operator<(const HeapNode& other) const {
        return distance < other.distance;
    }

    bool operator>(const HeapNode& other) const {
        return distance > other.distance;
    }
};

class Dijkstra {
public:
    enum HeapType { D_HEAP, BINOMIAL_HEAP };  

    explicit Dijkstra(const Graph& graph) : graph(graph) {
        if (graph.getNumVertices() == 0) {
            throw std::invalid_argument("Graph cannot be empty");
        }
    }
    ~Dijkstra() = default;

    Dijkstra(const Dijkstra&) = delete;
    Dijkstra& operator=(const Dijkstra&) = delete;

    myVector<int> shortestPathsWithPredecessors(int start, HeapType heapType, myVector<int>& predecessors, int d);
    void printResults(int start, const myVector<int>& dist) const;

private:
    const Graph& graph;

    template <typename Heap>
    void processQueueWithPredecessors(Heap& pq, myVector<int>& dist, myVector<bool>& visited, myVector<int>& predecessors) {
        while (!pq.empty()) {
            HeapNode current = pq.top();
            pq.pop();
            int u = current.vertex;

            if (visited[u]) continue;
            visited[u] = true;

            for (int v = 0; v < graph.getNumVertices(); ++v) {
                int weight = graph.getAdjacencyMatrix()[u][v];
                if (weight != -1 && !visited[v]) {
                    if (dist[v] == -1 || dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        predecessors[v] = u;
                        pq.push({ v, dist[v] });
                    }
                }
            }
        }
    }
};