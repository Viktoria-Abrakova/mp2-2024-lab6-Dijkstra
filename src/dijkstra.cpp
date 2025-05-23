#include "dijkstra.h"
#include <iostream>

myVector<int> Dijkstra::shortestPathsWithPredecessors(int start, HeapType heapType, myVector<int>& predecessors, int d) {
    const int numVertices = static_cast<int>(graph.getNumVertices());
    predecessors.resize(numVertices, -1);

    if (start < 0 || start >= numVertices) {
        throw std::out_of_range("Start vertex out of range");
    }

    myVector<int> dist(numVertices, std::numeric_limits<int>::max());
    myVector<bool> visited(numVertices, false);

    dist[start] = 0;

    if (heapType == D_HEAP) {
        DHeap<HeapNode> pq(d);
        pq.push({ start, 0 });
        processQueueWithPredecessors(pq, dist, visited, predecessors);
    }
    else {
        BinomialHeap<HeapNode> pq;
        pq.push({ start, 0 });
        processQueueWithPredecessors(pq, dist, visited, predecessors);
    }

    for (int i = 0; i < numVertices; ++i) {
        if (dist[i] == std::numeric_limits<int>::max()) {
            dist[i] = -1;
        }
    }

    return dist;
}

void Dijkstra::printResults(int start, const myVector<int>& dist) const {
    std::cout << "Кратчайшие пути от вершины " << start << ":\n";
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == -1) {
            std::cout << "  до " << i << ": недостижима\n";
        }
        else {
            std::cout << "  до " << i << ": " << dist[i] << "\n";
        }
    }
}

template void Dijkstra::processQueueWithPredecessors<DHeap<HeapNode>>(
    DHeap<HeapNode>&, myVector<int>&, myVector<bool>&, myVector<int>&);

template void Dijkstra::processQueueWithPredecessors<BinomialHeap<HeapNode>>(
    BinomialHeap<HeapNode>&, myVector<int>&, myVector<bool>&, myVector<int>&);