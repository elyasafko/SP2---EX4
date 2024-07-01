#pragma once

#include <vector>
#include <utility> // for std::move
#include <string>

template <typename T>
class Node
{
private:
    T value;
    std::vector<Node<T> *> children;

public:
    Node(const T &value, const std::vector<Node<T> *> &children = {})
        : value(value), children(children) {}

    Node(const T &value, std::vector<Node<T> *> &&children)
        : value(value), children(std::move(children)) {}

    Node(Node<T> &&) = default;
    Node<T> &operator=(Node<T> &&) = default;

    virtual ~Node() = default;

    void add_child(Node<T> *child)
    {
        children.push_back(child);
    }

    std::vector<Node<T> *> get_children() const
    {
        return children;
    }

    void set_value(const T &new_value)
    {
        value = new_value;
    }

    const T &get_value() const
    {
        return value;
    }

    T &get_value()
    {
        return value;
    }

    size_t get_children_size() const
    {
        return children.size();
    }
};
