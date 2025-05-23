#pragma once
#include <stdexcept>
#include "myvector.h"

template <typename T>
class BinomialHeap {
private:
    struct Node {
        T key;
        int degree;
        Node* parent;
        Node* child;
        Node* sibling;

        explicit Node(const T& k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
    };

    Node* head;
    size_t heap_size;

    Node* copyTree(Node* node) {
        if (!node) return nullptr;

        Node* newNode = new Node(node->key);
        newNode->degree = node->degree;

        if (node->child) {
            newNode->child = copyTree(node->child);
            Node* child = newNode->child;
            while (child) {
                child->parent = newNode;
                child = child->sibling;
            }
        }

        if (node->sibling) {
            newNode->sibling = copyTree(node->sibling);
        }

        return newNode;
    }

    void linkTrees(Node* y, Node* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    Node* mergeHeaps(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* head = nullptr;
        Node* tail = nullptr;
        Node* x = h1;
        Node* y = h2;

        if (x->degree <= y->degree) {
            head = x;
            x = x->sibling;
        }
        else {
            head = y;
            y = y->sibling;
        }
        tail = head;

        while (x && y) {
            if (x->degree <= y->degree) {
                tail->sibling = x;
                x = x->sibling;
            }
            else {
                tail->sibling = y;
                y = y->sibling;
            }
            tail = tail->sibling;
        }

        tail->sibling = x ? x : y;
        return head;
    }

    Node* unionHeaps(Node* h1, Node* h2) {
        Node* heap = mergeHeaps(h1, h2);
        if (!heap) return nullptr;

        Node* prev = nullptr;
        Node* x = heap;
        Node* next = x->sibling;

        while (next) {
            if (x->degree != next->degree ||
                (next->sibling && next->sibling->degree == x->degree)) {
                prev = x;
                x = next;
            }
            else if (!(next->key < x->key)) {  
                x->sibling = next->sibling;
                linkTrees(next, x);
            }
            else {
                if (!prev) {
                    heap = next;
                }
                else {
                    prev->sibling = next;
                }
                linkTrees(x, next);
                x = next;
            }
            next = x->sibling;
        }

        return heap;
    }

    Node* reverseList(Node* node) {
        Node* prev = nullptr;
        Node* next = nullptr;
        while (node) {
            next = node->sibling;
            node->sibling = prev;
            prev = node;
            node = next;
        }
        return prev;
    }

    Node* findMinNode() const {
        if (!head) return nullptr;

        Node* minNode = head;
        Node* current = head->sibling;
        while (current) {
            if (current->key < minNode->key) {
                minNode = current;
            }
            current = current->sibling;
        }
        return minNode;
    }

public:
    BinomialHeap() : head(nullptr), heap_size(0) {}

    ~BinomialHeap() {
        clear();
    }

    void push(const T& key) {
        Node* newNode = new Node(key);
        head = unionHeaps(head, newNode);
        heap_size++;
    }

    const T& top() const {
        Node* minNode = findMinNode();
        if (!minNode) throw std::runtime_error("Heap is empty");
        return minNode->key;
    }

    void pop() {
        if (!head) throw std::runtime_error("Heap is empty");

        Node* minPrev = nullptr;
        Node* minNode = head;
        Node* prev = nullptr;
        Node* current = head;
        while (current->sibling) {
            if (current->sibling->key < minNode->key) {
                minPrev = current;
                minNode = current->sibling;
            }
            current = current->sibling;
        }

        if (minPrev) {
            minPrev->sibling = minNode->sibling;
        }
        else {
            head = minNode->sibling;
        }

        Node* childHeap = reverseList(minNode->child);

        head = unionHeaps(head, childHeap);

        delete minNode;
        heap_size--;
    }

    void merge(BinomialHeap& other) {
        head = unionHeaps(head, other.head);
        other.head = nullptr;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    BinomialHeap(const BinomialHeap& other) : head(nullptr) {
        Node* current = other.head;
        Node* last = nullptr;

        while (current) {
            Node* copied = copyTree(current);
            if (!head) {
                head = copied;
            }
            else {
                last->sibling = copied;
            }
            last = copied;
            current = current->sibling;
        }
    }

    BinomialHeap(BinomialHeap&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    BinomialHeap& operator=(BinomialHeap&& other) noexcept {
        if (this != &other) {
            clear(); 
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

    BinomialHeap& operator=(const BinomialHeap& other) {
        if (this != &other) {
            BinomialHeap temp(other);
            std::swap(head, temp.head);
        }
        return *this;
    }

    size_t size() const {
        return heap_size;
    }
};