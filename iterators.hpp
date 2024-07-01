#pragma once
#include <vector>
#include <stack>
#include <queue>
#include "node.hpp"

// In-Order Iterator
template <typename T>
class inOrderIterator
{
private:
    std::stack<Node<T> *> stack;

    // Helper function to push all left children onto the stack
    void pushLeft(Node<T> *node)
    {
        while (node != nullptr)
        {
            stack.push(node);
            if (node->get_children_size() >= 1)
            {
                node = node->get_children()[0];
            }
            else
            {
                node = nullptr;
            }
        }
    }

public:
    inOrderIterator(Node<T> *root)
    {
        pushLeft(root);
    }

    T operator*() const
    {
        Node<T> *node = stack.top();
        return node->get_value();
    }

    bool operator!=(const inOrderIterator<T> &other) const
    {
        return stack != other.stack;
    }

    bool operator==(const inOrderIterator &other)
    {
        if (stack.empty() && other.stack.empty())
        {
            return true;
        }
        if (stack.empty() != other.stack.empty())
        {
            return false;
        }
        return stack.top() == other.stack.top();
    }

    Node<T> *operator->() { return stack.top(); }

    inOrderIterator &operator++()
    {
        Node<T> *current = stack.top();
        stack.pop();

        if (current->get_children_size() >= 2)
        {
            pushLeft(current->get_children()[1]);
        }

        return *this;
    }
};

// Pre-Order Iterator
template <typename T>
class preOrderIterator
{
private:
    std::stack<Node<T> *> stack;

public:
    preOrderIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            stack.push(root);
        }
    }

    T operator*() const
    {
        return stack.top()->get_value();
    }

    bool operator!=(const preOrderIterator<T> &other) const
    {
        return stack != other.stack;
    }

    bool operator==(const preOrderIterator<T> &other) const
    {
        return stack == other.stack;
    }

    Node<T> *operator->() { return stack.top(); }

    preOrderIterator<T> &operator++()
    {
        Node<T> *current = stack.top();
        stack.pop();

        for (int i = current->get_children_size() - 1; i >= 0; i--)
        {
            stack.push(current->get_children()[i]);
        }

        return *this;
    }
};

// Post-Order Iterator
template <typename T>
class postOrderIterator
{
private:
    std::stack<Node<T> *> stack1, stack2;

public:
    postOrderIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            stack1.push(root);
            while (!stack1.empty())
            {
                Node<T> *node = stack1.top();
                stack1.pop();
                stack2.push(node);
                for (size_t i = 0; i < node->get_children_size(); ++i)
                {
                    stack1.push(node->get_children()[i]);
                }
            }
        }
    }

    Node<T> *operator->() { return stack2.top(); }

    T operator*() const
    {
        if (stack2.empty())
        {
            throw std::out_of_range("Iterator out of range");
        }
        Node<T> *node = stack2.top();
        return node->get_value();
    }

    bool operator!=(const postOrderIterator<T> &other) const
    {
        return stack2 != other.stack2;
    }

    bool operator==(const postOrderIterator<T> &other) const
    {
        return stack2 == other.stack2;
    }

    postOrderIterator<T> &operator++()
    {
        if (!stack2.empty())
        {
            stack2.pop();
        }
        return *this;
    }
};

// Breadth-First Search (BFS) Iterator
template <typename T>
class bfsIterator
{
private:
    std::queue<Node<T> *> queue;

public:
    bfsIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            queue.push(root);
        }
    }

    Node<T> *operator->() { return queue.front(); }

    T operator*() const
    {
        Node<T> *node = queue.front();
        return node->get_value();
    }

    bool operator!=(const bfsIterator<T> &other) const
    {
        return queue != other.queue;
    }

    bool operator==(const bfsIterator<T> &other) const
    {
        return queue == other.queue;
    }

    bfsIterator<T> &operator++()
    {
        if (queue.empty())
        {
            throw std::out_of_range("Iterator out of range");
        }

        Node<T> *current = queue.front();
        queue.pop();

        for (auto &child : current->get_children())
        {
            queue.push(child);
        }

        return *this;
    }
};

// Depth-First Search (DFS) Iterator
template <typename T>
class dfsIterator
{
private:
    std::stack<Node<T> *> stack;

public:
    dfsIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            stack.push(root);
        }
    }

    T operator*() const
    {
        Node<T> *node = stack.top();
        return node->get_value();
    }

    bool operator!=(const dfsIterator<T> &other) const
    {
        return stack != other.stack;
    }

    Node<T> *operator->() { return stack.top(); }

    bool operator==(const dfsIterator<T> &other) const
    {
        return stack == other.stack;
    }

    dfsIterator<T> &operator++()
    {
        if (stack.empty())
        {
            throw std::out_of_range("Iterator out of range");
        }

        Node<T> *current = stack.top();
        stack.pop();

        for (int i = current->get_children_size() - 1; i >= 0; i--)
        {
            stack.push(current->get_children()[i]);
        }

        return *this;
    }
};

template <typename T>
class heapIterator
{
private:
    std::vector<Node<T> *> heap;

public:
    heapIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            std::queue<Node<T> *> nodeQueue;
            nodeQueue.push(root);

            while (!nodeQueue.empty())
            {
                Node<T> *current = nodeQueue.front();
                nodeQueue.pop();
                heap.push_back(current);

                for (size_t i = 0; i < current->get_children_size(); ++i)
                {
                    nodeQueue.push(current->get_children()[i]);
                }
            }

            // Ensure we are using a min-heap property
            std::make_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                           { return a->get_value() > b->get_value(); });
        }
    }

    bool operator==(const heapIterator &other) const
    {
        if (heap.empty() && other.heap.empty())
        {
            return true;
        }
        if (heap.empty() != other.heap.empty())
        {
            return false;
        }
        return heap.front() == other.heap.front();
    }

    bool operator!=(const heapIterator &other) const
    {
        return !(*this == other);
    }

    Node<T> *operator->() { return heap.front(); }
    T operator*() const { return heap.front()->get_value(); }

    heapIterator<T> &operator++()
    {
        if (!heap.empty())
        {
            std::pop_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                          { return a->get_value() > b->get_value(); });
            heap.pop_back();
        }
        return *this;
    }
};
