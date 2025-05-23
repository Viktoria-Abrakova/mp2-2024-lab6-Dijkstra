#include <gtest.h>
#include "dHeap.h"

TEST(DHeapTest, Constructor) {
    DHeap<int> heap(3);
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
    EXPECT_EQ(heap.getArity(), 3);
}

TEST(DHeapTest, InvalidDValue) {
    EXPECT_THROW(DHeap<int> heap(1), std::invalid_argument);
    EXPECT_THROW(DHeap<int> heap(0), std::invalid_argument);
    EXPECT_THROW(DHeap<int> heap(-1), std::invalid_argument);
}

TEST(DHeapTest, PushElements) {
    DHeap<int> heap(2);
    heap.push(5);
    heap.push(3);
    heap.push(7);
    EXPECT_EQ(heap.size(), 3);
}

TEST(DHeapTest, TopElement) {
    DHeap<int> heap(3);
    heap.push(5);
    EXPECT_EQ(heap.top(), 5);
    heap.push(3);
    EXPECT_EQ(heap.top(), 3);
    heap.push(7);
    EXPECT_EQ(heap.top(), 3);
}

TEST(DHeapTest, PopElements) {
    DHeap<int> heap(2);
    heap.push(5);
    heap.push(3);
    heap.push(7);
    heap.push(1);

    EXPECT_EQ(heap.top(), 1);
    heap.pop();
    EXPECT_EQ(heap.top(), 3);
    heap.pop();
    EXPECT_EQ(heap.top(), 5);
    heap.pop();
    EXPECT_EQ(heap.top(), 7);
    heap.pop();
    EXPECT_TRUE(heap.empty());
}

TEST(DHeapTest, EmptyHeap) {
    DHeap<int> heap(4);
    EXPECT_TRUE(heap.empty());
    EXPECT_THROW(heap.top(), std::out_of_range);
    EXPECT_THROW(heap.pop(), std::out_of_range);
}

TEST(DHeapTest, ChangeArity) {
    DHeap<int> heap(2);
    heap.push(5);
    heap.push(3);
    heap.push(7);
    heap.push(1);
    heap.push(9);

    heap.setArity(3);
    EXPECT_EQ(heap.getArity(), 3);
    EXPECT_EQ(heap.top(), 1);

    heap.setArity(4);
    EXPECT_EQ(heap.getArity(), 4);
    EXPECT_EQ(heap.top(), 1);
}

TEST(DHeapTest, HeapSort) {
    DHeap<int> heap(3);
    std::vector<int> input = { 5, 3, 8, 1, 2, 7, 4, 6 };
    std::vector<int> sorted = input;
    std::sort(sorted.begin(), sorted.end());

    for (int num : input) {
        heap.push(num);
    }

    std::vector<int> result;
    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }

    EXPECT_EQ(result, sorted);
}

TEST(DHeapTest, CustomStruct) {
    struct Point {
        int x, y;
        bool operator<(const Point& other) const {
            return x + y < other.x + other.y;
        }
    };

    DHeap<Point> heap(2);
    heap.push({ 1, 2 });
    heap.push({ 3, 0 });
    heap.push({ 0, 0 });

    EXPECT_EQ(heap.top().x, 0);
    EXPECT_EQ(heap.top().y, 0);
    heap.pop();
    EXPECT_EQ(heap.top().x, 1);
    EXPECT_EQ(heap.top().y, 2);
}

TEST(DHeapTest, Performance) {
    DHeap<int> heap(2);
    for (int i = 0; i < 10000; ++i) {
        heap.push(rand() % 10000);
    }

    int prev = heap.top();
    while (!heap.empty()) {
        int current = heap.top();
        heap.pop();
        EXPECT_LE(prev, current);
        prev = current;
    }
}

TEST(DHeapTest, SingleElement) {
    DHeap<int> heap(5);
    heap.push(42);
    EXPECT_EQ(heap.size(), 1);
    EXPECT_EQ(heap.top(), 42);
    heap.pop();
    EXPECT_TRUE(heap.empty());
}

TEST(DHeapTest, SequentialPushPop) {
    DHeap<int> heap(2);
    for (int i = 0; i < 10; ++i) {
        heap.push(i);
        EXPECT_EQ(heap.top(), 0);
    }

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(heap.top(), i);
        heap.pop();
    }
}

TEST(DHeapTest, EqualElements) {
    DHeap<int> heap(3);
    for (int i = 0; i < 10; ++i) {
        heap.push(5);
    }

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(heap.top(), 5);
        heap.pop();
    }
}

TEST(DHeapTest, SizeChanges) {
    DHeap<int> heap(4);
    EXPECT_EQ(heap.size(), 0);
    heap.push(1);
    EXPECT_EQ(heap.size(), 1);
    heap.push(2);
    EXPECT_EQ(heap.size(), 2);
    heap.pop();
    EXPECT_EQ(heap.size(), 1);
    heap.pop();
    EXPECT_EQ(heap.size(), 0);
}

TEST(DHeapTest, HeapProperty) {
    DHeap<int> heap(2);
    for (int i = 0; i < 100; ++i) {
        heap.push(rand() % 1000);
    }

    while (heap.size() > 1) {
        int top = heap.top();
        heap.pop();
        EXPECT_LE(top, heap.top());
    }
}

TEST(DHeapTest, LargeArity) {
    DHeap<int> heap(10);
    for (int i = 0; i < 100; ++i) {
        heap.push(rand() % 1000);
    }

    int prev = heap.top();
    while (!heap.empty()) {
        int current = heap.top();
        heap.pop();
        EXPECT_LE(prev, current);
        prev = current;
    }
}

TEST(DHeapTest, MixedOperations) {
    DHeap<int> heap(3);
    heap.push(5);
    heap.push(3);
    EXPECT_EQ(heap.top(), 3);
    heap.pop();
    heap.push(7);
    heap.push(1);
    EXPECT_EQ(heap.top(), 1);
    heap.pop();
    heap.push(2);
    EXPECT_EQ(heap.top(), 2);
}

TEST(DHeapTest, NegativeNumbers) {
    DHeap<int> heap(2);
    heap.push(-5);
    heap.push(-3);
    heap.push(-7);
    heap.push(-1);

    EXPECT_EQ(heap.top(), -7);
    heap.pop();
    EXPECT_EQ(heap.top(), -5);
    heap.pop();
    EXPECT_EQ(heap.top(), -3);
    heap.pop();
    EXPECT_EQ(heap.top(), -1);
}

TEST(DHeapTest, ClearByPop) {
    DHeap<int> heap(3);
    heap.push(1);
    heap.push(2);
    heap.push(3);

    heap.pop();
    heap.pop();
    heap.pop();

    EXPECT_TRUE(heap.empty());
    EXPECT_THROW(heap.top(), std::out_of_range);
}

TEST(DHeapTest, ChangeArityEmptyHeap) {
    DHeap<int> heap(2);
    heap.setArity(5);
    EXPECT_EQ(heap.getArity(), 5);

    heap.push(3);
    heap.push(1);
    heap.push(2);

    EXPECT_EQ(heap.top(), 1);
}

TEST(DHeapTest, MultipleArityChanges) {
    DHeap<int> heap(2);
    heap.push(5);
    heap.push(3);
    heap.push(7);

    heap.setArity(3);
    EXPECT_EQ(heap.top(), 3);

    heap.setArity(4);
    EXPECT_EQ(heap.top(), 3);

    heap.setArity(2);
    EXPECT_EQ(heap.top(), 3);
}

TEST(DHeapTest, ArityChangePreservesOrder) {
    DHeap<int> heap(2);
    for (int i = 0; i < 100; ++i) {
        heap.push(rand() % 1000);
    }

    heap.setArity(5);
    int prev = heap.top();
    while (!heap.empty()) {
        int current = heap.top();
        heap.pop();
        EXPECT_LE(prev, current);
        prev = current;
    }
}

TEST(DHeapTest, ArityChangeExceptions) {
    DHeap<int> heap(2);
    EXPECT_THROW(heap.setArity(1), std::invalid_argument);
    EXPECT_THROW(heap.setArity(0), std::invalid_argument);
    EXPECT_THROW(heap.setArity(-1), std::invalid_argument);
}

TEST(DHeapTest, LargeScalePerformance) {
    DHeap<int> heap(2);
    const int N = 100000;
    for (int i = 0; i < N; ++i) {
        heap.push(rand() % N);
    }

    int prev = heap.top();
    for (int i = 0; i < N; ++i) {
        int current = heap.top();
        heap.pop();
        EXPECT_LE(prev, current);
        prev = current;
    }
}

TEST(DHeapTest, ComprehensiveTest) {
    DHeap<int> heap(2);
    EXPECT_TRUE(heap.empty());

    heap.push(5);
    heap.push(3);
    heap.push(7);
    EXPECT_EQ(heap.size(), 3);
    EXPECT_EQ(heap.top(), 3);

    heap.setArity(3);
    EXPECT_EQ(heap.getArity(), 3);
    EXPECT_EQ(heap.top(), 3);

    heap.pop();
    EXPECT_EQ(heap.top(), 5);

    heap.push(1);
    EXPECT_EQ(heap.top(), 1);

    heap.pop();
    heap.pop();
    heap.pop();
    EXPECT_TRUE(heap.empty());
}

TEST(DHeapTest, DifferentDataTypes) {
    DHeap<double> heap(3);
    heap.push(3.14);
    heap.push(2.71);
    heap.push(1.41);

    EXPECT_DOUBLE_EQ(heap.top(), 1.41);
    heap.pop();
    EXPECT_DOUBLE_EQ(heap.top(), 2.71);
}

TEST(DHeapTest, MoveSemantics) {
    DHeap<int> heap1(2);
    heap1.push(5);
    heap1.push(3);

    DHeap<int> heap2 = std::move(heap1);
    EXPECT_EQ(heap2.top(), 3);
    EXPECT_TRUE(heap1.empty());
}