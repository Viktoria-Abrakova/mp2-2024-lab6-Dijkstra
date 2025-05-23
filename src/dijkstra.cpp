#include "dijkstra.h"
#include <iostream>

myVector<int> Dijkstra::shortestPaths(int start, HeapType heapType, int d) {
    const int numVertices = static_cast<int>(graph.getNumVertices());

    if (start < 0 || start >= numVertices) {
        throw std::out_of_range("Start vertex out of range");
    }

    myVector<int> dist(numVertices, std::numeric_limits<int>::max());
    myVector<bool> visited(numVertices, false);

    dist[start] = 0;

    if (heapType == D_HEAP) {
        DHeap<HeapNode> pq(d);
        pq.push({ start, 0 });
        processQueue(pq, dist, visited);
    }
    else {
        BinomialHeap<HeapNode> pq;  
        pq.push({ start, 0 });
        processQueue(pq, dist, visited);
    }

    for (int i = 0; i < numVertices; ++i) {
        if (dist[i] == std::numeric_limits<int>::max()) {
            dist[i] = -1;
        }
    }

    return dist;
}

void Dijkstra::printResults(int start, const myVector<int>& dist) const {
    std::cout << "���������� ���� �� ������� " << start << ":\n";
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == -1) {
            std::cout << "  �� " << i << ": �����������\n";
        }
        else {
            std::cout << "  �� " << i << ": " << dist[i] << "\n";
        }
    }
}

template void Dijkstra::processQueue<DHeap<HeapNode>>(
    DHeap<HeapNode>&, myVector<int>&, myVector<bool>&);

template void Dijkstra::processQueue<BinomialHeap<HeapNode>>(  
    BinomialHeap<HeapNode>&, myVector<int>&, myVector<bool>&);