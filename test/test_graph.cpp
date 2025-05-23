#include <gtest.h>
#include "graph.h"

TEST(GraphTest, ConstructorInitializesCorrectSize) {
    Graph g(5);
    EXPECT_EQ(g.getNumVertices(), 5);
}

TEST(GraphTest, ConstructorInitializesDiagonalZeros) {
    Graph g(3);
    auto matrix = g.getAdjacencyMatrix();
    EXPECT_EQ(matrix[0][0], 0);
    EXPECT_EQ(matrix[1][1], 0);
    EXPECT_EQ(matrix[2][2], 0);
}

TEST(GraphTest, ConstructorInitializesOtherElementsMinusOne) {
    Graph g(2);
    auto matrix = g.getAdjacencyMatrix();
    EXPECT_EQ(matrix[0][1], -1);
    EXPECT_EQ(matrix[1][0], -1);
}

TEST(GraphTest, AddEdgeValidVertices) {
    Graph g(3);
    g.addEdge(0, 1, 5);
    auto matrix = g.getAdjacencyMatrix();
    EXPECT_EQ(matrix[0][1], 5);
    EXPECT_EQ(matrix[1][0], 5);
}

TEST(GraphTest, AddEdgeThrowsForInvalidWeight) {
    Graph g(3);
    EXPECT_THROW(g.addEdge(0, 1, 0), std::invalid_argument);
    EXPECT_THROW(g.addEdge(0, 1, -5), std::invalid_argument);
}

TEST(GraphTest, AddEdgeThrowsForInvalidVertices) {
    Graph g(3);

    EXPECT_THROW(g.addEdge(0, 5, 2), std::out_of_range);
    EXPECT_THROW(g.addEdge(5, 0, 2), std::out_of_range);
    EXPECT_THROW(g.addEdge(-1, 1, 2), std::out_of_range);

    auto matrix = g.getAdjacencyMatrix();
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (i != j) {
                EXPECT_EQ(matrix[i][j], -1);
            }
            else {
                EXPECT_EQ(matrix[i][j], 0);  
            }
        }
    }
}

TEST(GraphTest, EmptyGraphIsConnected) {
    Graph g(1);
    EXPECT_TRUE(g.isConnected());
}

TEST(GraphTest, SingleEdgeGraphIsConnected) {
    Graph g(2);
    g.addEdge(0, 1, 1);
    EXPECT_TRUE(g.isConnected());
}

TEST(GraphTest, DisconnectedGraphIsNotConnected) {
    Graph g(3);
    g.addEdge(0, 1, 1);
    EXPECT_FALSE(g.isConnected());
}

TEST(GraphTest, FullyConnectedGraphIsConnected) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    EXPECT_TRUE(g.isConnected());
}

TEST(GraphTest, LinearConnectedGraphIsConnected) {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    EXPECT_TRUE(g.isConnected());
}

TEST(GraphTest, StarConnectedGraphIsConnected) {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(0, 4, 1);
    EXPECT_TRUE(g.isConnected());
}

TEST(GraphTest, PrintGraphOutput) {
    Graph g(2);
    testing::internal::CaptureStdout();
    g.printGraph();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0 -"), std::string::npos);
    EXPECT_NE(output.find("- 0"), std::string::npos);
}

TEST(GraphTest, LargeGraphConstruction) {
    Graph g(1000);
    EXPECT_EQ(g.getNumVertices(), 1000);
}

TEST(GraphTest, ZeroVertexGraphThrows) {
    EXPECT_THROW(Graph g(0), std::invalid_argument);
}

TEST(GraphTest, AddEdgeMaintainsSymmetry) {
    Graph g(4);
    g.addEdge(1, 2, 3);
    auto matrix = g.getAdjacencyMatrix();
    EXPECT_EQ(matrix[1][2], 3);
    EXPECT_EQ(matrix[2][1], 3);
}

TEST(GraphTest, MultipleEdgesWorkCorrectly) {
    Graph g(3);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(0, 2, 4);
    auto matrix = g.getAdjacencyMatrix();
    EXPECT_EQ(matrix[0][1], 2);
    EXPECT_EQ(matrix[1][2], 3);
    EXPECT_EQ(matrix[0][2], 4);
    EXPECT_TRUE(g.isConnected());
}

TEST(GraphTest, NoEdgesGraphIsNotConnected) {
    Graph g(3);
    EXPECT_FALSE(g.isConnected());
}

TEST(GraphTest, GetExistingEdgeWeight) {
    Graph graph(3);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);

    EXPECT_EQ(graph.getEdgeWeight(0, 1), 10);
    EXPECT_EQ(graph.getEdgeWeight(1, 0), 10); 
    EXPECT_EQ(graph.getEdgeWeight(1, 2), 20);
}

TEST(GraphTest, GetNonExistentEdgeWeight) {
    Graph graph(3);
    graph.addEdge(0, 1, 10);

    EXPECT_EQ(graph.getEdgeWeight(0, 2), -1);
    EXPECT_EQ(graph.getEdgeWeight(2, 2), 0);  
}

TEST(GraphTest, GetEdgeWeightInvalidVertex) {
    Graph graph(3);

    EXPECT_THROW(graph.getEdgeWeight(-1, 0), std::out_of_range);
    EXPECT_THROW(graph.getEdgeWeight(0, 3), std::out_of_range);
    EXPECT_THROW(graph.getEdgeWeight(5, 5), std::out_of_range);
}

TEST(GraphTest, GetEdgeWeightInEmptyGraph) {
    Graph graph(3);

    EXPECT_EQ(graph.getEdgeWeight(0, 1), -1);
    EXPECT_EQ(graph.getEdgeWeight(1, 2), -1);
    EXPECT_EQ(graph.getEdgeWeight(0, 0), 0); 
}