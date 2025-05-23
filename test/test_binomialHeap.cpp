#include <gtest.h>
#include "binomialHeap.h"

TEST(BinomialHeapTest, DefaultConstructor) {
    BinomialHeap<int> heap;
    EXPECT_TRUE(heap.empty());
}

TEST(BinomialHeapTest, SingleElementPush) {
    BinomialHeap<int> heap;
    heap.push(5);
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.top(), 5);
}

TEST(BinomialHeapTest, MultipleElementsPush) {
    BinomialHeap<int> heap;
    heap.push(5);
    heap.push(3);
    heap.push(7);
    EXPECT_EQ(heap.top(), 3);
}

TEST(BinomialHeapTest, PopElements) {
    BinomialHeap<int> heap;
    heap.push(5);
    heap.push(3);
    heap.push(7);

    EXPECT_EQ(heap.top(), 3);
    heap.pop();
    EXPECT_EQ(heap.top(), 5);
    heap.pop();
    EXPECT_EQ(heap.top(), 7);
    heap.pop();

    EXPECT_TRUE(heap.empty());
    EXPECT_THROW(heap.pop(), std::runtime_error);
    EXPECT_THROW(heap.top(), std::runtime_error);
}

TEST(BinomialHeapTest, EmptyHeap) {
    BinomialHeap<int> heap;
    EXPECT_TRUE(heap.empty());
    EXPECT_THROW(heap.top(), std::runtime_error);
    EXPECT_THROW(heap.pop(), std::runtime_error);
}

TEST(BinomialHeapTest, ClearHeap) {
    BinomialHeap<int> heap;
    heap.push(5);
    heap.push(3);
    heap.clear();
    EXPECT_TRUE(heap.empty());
}

TEST(BinomialHeapTest, MergeHeaps) {
    BinomialHeap<int> heap1;
    heap1.push(5);
    heap1.push(3);

    BinomialHeap<int> heap2;
    heap2.push(7);
    heap2.push(2);

    heap1.merge(heap2);
    EXPECT_EQ(heap1.top(), 2);
    EXPECT_TRUE(heap2.empty());
}

TEST(BinomialHeapTest, AssignmentOperator) {
    BinomialHeap<int> heap1;
    heap1.push(5);
    heap1.push(3);
    heap1.push(7);

    BinomialHeap<int> heap2;
    heap2 = heap1;

    EXPECT_EQ(heap2.top(), 3);
    heap2.pop();
    EXPECT_EQ(heap2.top(), 5);
    heap2.pop();
    EXPECT_EQ(heap2.top(), 7);
    heap2.pop();
    EXPECT_TRUE(heap2.empty());

    EXPECT_EQ(heap1.top(), 3);
    heap1.pop();
    EXPECT_EQ(heap1.top(), 5);
    heap1.pop();
    EXPECT_EQ(heap1.top(), 7);
    heap1.pop();
    EXPECT_TRUE(heap1.empty());

    heap1.push(42);
    heap1 = heap1;
    EXPECT_EQ(heap1.top(), 42);
}

TEST(BinomialHeapTest, CustomStruct) {
    struct Point {
        int x, y;
        bool operator<(const Point& other) const {
            return x + y < other.x + other.y;
        }
    };

    BinomialHeap<Point> heap;
    heap.push({ 1, 2 });
    heap.push({ 3, 0 });
    heap.push({ 0, 0 });

    EXPECT_EQ(heap.top().x, 0);
    EXPECT_EQ(heap.top().y, 0);
}

TEST(BinomialHeapTest, LargeNumberOfElements) {
    BinomialHeap<int> heap;
    for (int i = 0; i < 1000; ++i) {
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

TEST(BinomialHeapTest, MoveSemantics) {
    BinomialHeap<int> heap1;
    heap1.push(5);
    heap1.push(3);

    BinomialHeap<int> heap2 = std::move(heap1);
    EXPECT_EQ(heap2.top(), 3);
    EXPECT_TRUE(heap1.empty());
}

TEST(BinomialHeapTest, EqualElements) {
    BinomialHeap<int> heap;
    for (int i = 0; i < 10; ++i) {
        heap.push(5);
    }

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(heap.top(), 5);
        heap.pop();
    }
}

TEST(BinomialHeapTest, SequentialPushPop) {
    BinomialHeap<int> heap;
    for (int i = 0; i < 10; ++i) {
        heap.push(i);
    }

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(heap.top(), i);
        heap.pop();
    }
}

TEST(BinomialHeapTest, NegativeNumbers) {
    BinomialHeap<int> heap;
    heap.push(-5);
    heap.push(-3);
    heap.push(-7);

    EXPECT_EQ(heap.top(), -7);
    heap.pop();
    EXPECT_EQ(heap.top(), -5);
}

TEST(BinomialHeapTest, HeapProperty) {
    BinomialHeap<int> heap;
    for (int i = 0; i < 100; ++i) {
        heap.push(rand() % 100);
    }

    int prev = heap.top();
    while (!heap.empty()) {
        int current = heap.top();
        heap.pop();
        EXPECT_LE(prev, current);
        prev = current;
    }
}

TEST(BinomialHeapTest, SingleElementHeap) {
    BinomialHeap<int> heap;
    heap.push(42);
    EXPECT_EQ(heap.top(), 42);
    heap.pop();
    EXPECT_TRUE(heap.empty());
}

TEST(BinomialHeapTest, MixedOperations) {
    BinomialHeap<int> heap;
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

TEST(BinomialHeapTest, ClearByPop) {
    BinomialHeap<int> heap;
    heap.push(1);
    heap.push(2);
    heap.push(3);

    heap.pop();
    heap.pop();
    heap.pop();

    EXPECT_TRUE(heap.empty());
    EXPECT_THROW(heap.top(), std::runtime_error);
}

TEST(BinomialHeapTest, LargeScalePerformance) {
    BinomialHeap<int> heap;
    const int N = 10000;
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

TEST(BinomialHeapTest, ComprehensiveTest) {
    BinomialHeap<int> heap;
    EXPECT_TRUE(heap.empty());

    heap.push(5);
    heap.push(3);
    heap.push(7);
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

TEST(BinomialHeapTest, DifferentDataTypes) {
    BinomialHeap<double> heap;
    heap.push(3.14);
    heap.push(2.71);
    heap.push(1.41);

    EXPECT_DOUBLE_EQ(heap.top(), 1.41);
    heap.pop();
    EXPECT_DOUBLE_EQ(heap.top(), 2.71);
}

TEST(BinomialHeapTest, CopyHeap) {
    BinomialHeap<int> heap1;
    heap1.push(5);
    heap1.push(3);

    BinomialHeap<int> heap2(heap1);
    EXPECT_EQ(heap2.top(), 3);
    heap2.pop();
    EXPECT_EQ(heap2.top(), 5);
}

TEST(BinomialHeapTest, HeapSort) {
    BinomialHeap<int> heap;
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

TEST(BinomialHeapTest, ReverseOrderInsert) {
    BinomialHeap<int> heap;
    for (int i = 10; i > 0; --i) {
        heap.push(i);
    }

    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(heap.top(), i);
        heap.pop();
    }
}

TEST(BinomialHeapTest, RandomOrderInsert) {
    BinomialHeap<int> heap;
    std::vector<int> nums = { 7, 3, 9, 2, 5, 1, 8, 4, 6 };

    for (int num : nums) {
        heap.push(num);
    }

    for (int i = 1; i <= 9; ++i) {
        EXPECT_EQ(heap.top(), i);
        heap.pop();
    }
}

TEST(BinomialHeapTest, DuplicateElements) {
    BinomialHeap<int> heap;
    heap.push(5);
    heap.push(5);
    heap.push(3);
    heap.push(3);
    heap.push(7);
    heap.push(7);

    EXPECT_EQ(heap.top(), 3);
    heap.pop();
    EXPECT_EQ(heap.top(), 3);
    heap.pop();
    EXPECT_EQ(heap.top(), 5);
}

TEST(BinomialHeapTest, HeapSize) {
    BinomialHeap<int> heap;
    EXPECT_EQ(heap.size(), 0);

    heap.push(5);
    EXPECT_EQ(heap.size(), 1);

    heap.push(3);
    EXPECT_EQ(heap.size(), 2);

    heap.pop();
    EXPECT_EQ(heap.size(), 1);
}

TEST(BinomialHeapTest, MergeEmptyWithNonEmpty) {
    BinomialHeap<int> heap1;
    BinomialHeap<int> heap2;
    heap2.push(5);
    heap2.push(3);

    heap1.merge(heap2);
    EXPECT_EQ(heap1.top(), 3);
    EXPECT_TRUE(heap2.empty());
}

TEST(BinomialHeapTest, MergeNonEmptyWithEmpty) {
    BinomialHeap<int> heap1;
    heap1.push(5);
    heap1.push(3);

    BinomialHeap<int> heap2;
    heap1.merge(heap2);
    EXPECT_EQ(heap1.top(), 3);
    EXPECT_TRUE(heap2.empty());
}

TEST(BinomialHeapTest, MergeTwoEmptyHeaps) {
    BinomialHeap<int> heap1;
    BinomialHeap<int> heap2;
    heap1.merge(heap2);
    EXPECT_TRUE(heap1.empty());
    EXPECT_TRUE(heap2.empty());
}

TEST(BinomialHeapTest, PushAfterClear) {
    BinomialHeap<int> heap;
    heap.push(5);
    heap.push(3);
    heap.clear();

    heap.push(7);
    heap.push(1);
    EXPECT_EQ(heap.top(), 1);
}

TEST(BinomialHeapTest, MoveEmptyHeap) {
    BinomialHeap<int> heap1;
    BinomialHeap<int> heap2 = std::move(heap1);
    EXPECT_TRUE(heap1.empty());
    EXPECT_TRUE(heap2.empty());
}

TEST(BinomialHeapTest, MoveNonEmptyHeap) {
    BinomialHeap<int> heap1;
    heap1.push(5);
    heap1.push(3);

    BinomialHeap<int> heap2 = std::move(heap1);
    EXPECT_EQ(heap2.top(), 3);
    EXPECT_TRUE(heap1.empty());
}

TEST(BinomialHeapTest, CopyEmptyHeap) {
    BinomialHeap<int> heap1;
    BinomialHeap<int> heap2(heap1);
    EXPECT_TRUE(heap1.empty());
    EXPECT_TRUE(heap2.empty());
}

TEST(BinomialHeapTest, CopyNonEmptyHeap) {
    BinomialHeap<int> heap1;
    heap1.push(5);
    heap1.push(3);

    BinomialHeap<int> heap2(heap1);
    EXPECT_EQ(heap2.top(), 3);
    heap2.pop();
    EXPECT_EQ(heap2.top(), 5);
}

TEST(BinomialHeapTest, AssignEmptyHeap) {
    BinomialHeap<int> heap1;
    BinomialHeap<int> heap2;
    heap2 = heap1;
    EXPECT_TRUE(heap1.empty());
    EXPECT_TRUE(heap2.empty());
}
