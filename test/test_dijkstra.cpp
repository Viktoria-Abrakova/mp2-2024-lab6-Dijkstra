#include <gtest.h>
#include "dijkstra.h"

TEST(DijkstraTest, ShortestPathBasic) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[3], 6);
    EXPECT_EQ(dist_d[3], 6);
}

TEST(DijkstraTest, DisconnectedGraph) {
    Graph g_disconnected(3);
    g_disconnected.addEdge(0, 1, 1);
    Dijkstra d(g_disconnected);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[2], -1);
    EXPECT_EQ(dist_d[2], -1);
}

TEST(DijkstraTest, SingleNodeGraph) {
    Graph g_single(1);
    Dijkstra d(g_single);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[0], 0);
    EXPECT_EQ(dist_d[0], 0);
}

TEST(DijkstraTest, CheckAllPaths) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[0], 0);
    EXPECT_EQ(dist_binom[1], 1);
    EXPECT_EQ(dist_binom[2], 3);
    EXPECT_EQ(dist_binom[3], 6);
    EXPECT_EQ(dist_d[0], 0);
    EXPECT_EQ(dist_d[1], 1);
    EXPECT_EQ(dist_d[2], 3);
    EXPECT_EQ(dist_d[3], 6);
}

TEST(DijkstraTest, StartFromMiddle) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(1, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(1, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[3], 5);
    EXPECT_EQ(dist_d[3], 5);
}

TEST(DijkstraTest, CompareHeaps) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[3], dist_d[3]);
}

TEST(DijkstraTest, InvalidStartVertex) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);
    Dijkstra d(g);
    myVector<int> pred;
    EXPECT_THROW(d.shortestPathsWithPredecessors(-1, Dijkstra::D_HEAP, pred, 2), std::out_of_range);
}

TEST(DijkstraTest, CyclicGraph) {
    Graph g_cycle(3);
    g_cycle.addEdge(0, 1, 1);
    g_cycle.addEdge(1, 2, 1);
    g_cycle.addEdge(2, 0, 1);
    Dijkstra d(g_cycle);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[2], 1);
    EXPECT_EQ(dist_d[2], 1);
}

TEST(DijkstraTest, CompleteGraph) {
    Graph g_complete(3);
    g_complete.addEdge(0, 1, 1);
    g_complete.addEdge(1, 2, 1);
    g_complete.addEdge(0, 2, 1);
    Dijkstra d(g_complete);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[2], 1);
    EXPECT_EQ(dist_d[2], 1);
}

TEST(DijkstraTest, DifferentDValues) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);
    Dijkstra d(g);
    myVector<int> pred_d;
    auto dist_d2 = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 22);
    auto dist_d4 = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 4);
    EXPECT_EQ(dist_d2[3], dist_d4[3]);
}

TEST(HeapNodeTest, Comparison) {
    HeapNode n1{ 0, 5 };
    HeapNode n2{ 1, 10 };
    EXPECT_TRUE(n1 < n2);
}

TEST(DijkstraPerformanceTest, LargeGraph) {
    const int N = 100;
    Graph g(N);
    for (int i = 0; i < N - 1; ++i) {
        g.addEdge(i, i + 1, 1);
    }
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[N - 1], N - 1);
    EXPECT_EQ(dist_d[N - 1], N - 1);
}

TEST(DijkstraTest, MultiplePaths) {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 3);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[2], 2);
    EXPECT_EQ(dist_d[2], 2);
}

TEST(DijkstraTest, TwoNodeGraph) {
    Graph g(2);
    g.addEdge(0, 1, 5);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[1], 5);
    EXPECT_EQ(dist_d[1], 5);
}

TEST(DijkstraTest, EqualDistances) {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[1], 1);
    EXPECT_EQ(dist_binom[2], 1);
    EXPECT_EQ(dist_d[1], 1);
    EXPECT_EQ(dist_d[2], 1);
}

TEST(DijkstraTest, LargeWeight) {
    Graph g(3);
    g.addEdge(0, 1, 1000);
    g.addEdge(1, 2, 1000);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[2], 2000);
    EXPECT_EQ(dist_d[2], 2000);
}

TEST(DijkstraPerformanceTest, DHeapPerformance) {
    const int N = 1000;
    Graph g(N);
    for (int i = 0; i < N - 1; ++i) {
        g.addEdge(i, i + 1, 1);
    }
    Dijkstra d(g);
    myVector<int> pred;
    auto start = std::clock();
    auto dist = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred, 2);
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    EXPECT_LT(duration, 1.0);
}

TEST(DijkstraPerformanceTest, BinomialHeapPerformance) {
    const int N = 1000;
    Graph g(N);
    for (int i = 0; i < N - 1; ++i) {
        g.addEdge(i, i + 1, 1);
    }
    Dijkstra d(g);
    myVector<int> pred;
    auto start = std::clock();
    auto dist = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred, 2);
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    EXPECT_LT(duration, 1.0);
}

TEST(DijkstraTest, FiveNodeGraph) {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    Dijkstra d(g);
    myVector<int> pred;
    auto dist = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred, 2);
    EXPECT_EQ(dist[4], 4);
}

TEST(DijkstraTest, ChooseShortestPath) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 3, 2);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[3], 2);
    EXPECT_EQ(dist_d[3], 2);
}

TEST(DijkstraTest, ComplexTest) {
    Graph g(6);
    g.addEdge(0, 1, 7);
    g.addEdge(0, 2, 9);
    g.addEdge(0, 5, 14);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 11);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, 6);
    g.addEdge(4, 5, 9);
    Dijkstra d(g);
    myVector<int> pred_binom, pred_d;
    auto dist_binom = d.shortestPathsWithPredecessors(0, Dijkstra::BINOMIAL_HEAP, pred_binom, 2);
    auto dist_d = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred_d, 2);
    EXPECT_EQ(dist_binom[4], 20);
    EXPECT_EQ(dist_binom[5], 11);
    EXPECT_EQ(dist_d[4], 20);
    EXPECT_EQ(dist_d[5], 11);
}

TEST(DijkstraTest, PathReconstruction) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);
    Dijkstra d(g);
    myVector<int> pred;
    auto dist = d.shortestPathsWithPredecessors(0, Dijkstra::D_HEAP, pred, 2);

    auto path = g.getPath(0, 3, pred);
    ASSERT_EQ(path.size(), 4);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 2);
    EXPECT_EQ(path[3], 3);
}