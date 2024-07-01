#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <type_traits>

#include "node.hpp"
#include "iterators.hpp"
#include "complex.hpp"

template <typename T, size_t N = 2>
class Tree
{
private:
    std::unique_ptr<Node<T>> root;
    size_t maxChildren;
    sf::RenderWindow window;
    sf::Font font;

    void deleteTree(Node<T> *node)
    {
        if (!node)
            return;
        for (auto child : node->get_children())
        {
            deleteTree(child);
        }
        delete node;
    }

public:
    // Constructor
    Tree(size_t maxChildren = N) : root(nullptr), maxChildren(maxChildren) {}

    // Destructor
    ~Tree()
    {
        deleteTree(root.release());
    }

    // Add root node
    void add_root(std::unique_ptr<Node<T>> root_node)
    {
        root = std::move(root_node);
    }

    std::unique_ptr<Node<T>> &get_root()
    {
        return root;
    }

    // Add sub-node
    void add_sub_node(Node<T> &parent, std::unique_ptr<Node<T>> child)
    {
        if (parent.get_children_size() >= maxChildren)
        {
            std::cout << "Cannot add sub node, max children reached" << std::endl;
            return;
        }
        parent.add_child(child.get());
        child.release(); // Release ownership since the parent now owns the child node
    }

    // Iterators
    // Pre Order
    preOrderIterator<T> begin_pre_order() { return preOrderIterator<T>(root.get()); }
    preOrderIterator<T> end_pre_order() { return preOrderIterator<T>(nullptr); }
    // Post Order
    postOrderIterator<T> begin_post_order() { return postOrderIterator<T>(root.get()); }
    postOrderIterator<T> end_post_order() { return postOrderIterator<T>(nullptr); }
    // In Order
    inOrderIterator<T> begin_in_order() { return inOrderIterator<T>(root.get()); }
    inOrderIterator<T> end_in_order() { return inOrderIterator<T>(nullptr); }
    // BFS
    bfsIterator<T> begin_bfs() { return bfsIterator<T>(root.get()); }
    bfsIterator<T> end_bfs() { return bfsIterator<T>(nullptr); }
    // DFS
    dfsIterator<T> begin_dfs() { return dfsIterator<T>(root.get()); }
    dfsIterator<T> end_dfs() { return dfsIterator<T>(nullptr); }
    // Heap
    heapIterator<T> begin_heap() { return heapIterator<T>(root.get()); }
    heapIterator<T> end_heap() { return heapIterator<T>(nullptr); }

    // Default iterator
    bfsIterator<T> begin() { return bfsIterator<T>(root.get()); }
    bfsIterator<T> end() { return bfsIterator<T>(nullptr); }

    // Draw the tree
    void drawTree()
    {
        window.create(sf::VideoMode(1920, 1080), "Tree Visualization");

        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        {
            throw std::runtime_error("Font could not be loaded");
        }

        if (!root)
        {
            throw std::runtime_error("Root node is null");
        }

        sf::View view = window.getDefaultView();
        bool isPanning = false;
        sf::Vector2i panStart;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.delta > 0)
                    {
                        view.zoom(0.9f); // Zoom in
                    }
                    else
                    {
                        view.zoom(1.1f); // Zoom out
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Middle)
                    {
                        isPanning = true;
                        panStart = sf::Mouse::getPosition(window);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Middle)
                    {
                        isPanning = false;
                    }
                }

                if (event.type == sf::Event::MouseMoved)
                {
                    if (isPanning)
                    {
                        sf::Vector2i panEnd = sf::Mouse::getPosition(window);
                        sf::Vector2f offset(
                            static_cast<float>(panStart.x - panEnd.x),
                            static_cast<float>(panStart.y - panEnd.y));
                        view.move(offset);
                        panStart = panEnd;
                    }
                }
            }

            window.clear(sf::Color::White);
            window.setView(view);
            drawNode(window, root.get(), window.getSize().x / 2.0f, 50.0f, 200.0f, 80.0f);
            window.display();
        }
    }

    // Draw individual node
    void drawNode(sf::RenderWindow &window, Node<T> *node, float x, float y, float offsetX, float offsetY)
    {
        if (!node)
            return;

        sf::CircleShape shape(30);
        shape.setFillColor(sf::Color::Green);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::Black);
        shape.setPosition(x - shape.getRadius(), y - shape.getRadius());
        window.draw(shape);

        sf::Text text;
        if constexpr (std::is_same<T, Complex>::value)
        {
            text.setString(node->get_value().to_string());
        }
        else
        {
            std::stringstream ss;
            ss << node->get_value();
            std::string str = ss.str();
            text.setString(str);
        }

        text.setFont(font);
        text.setFillColor(sf::Color::Black);

        // Dynamically adjust text size to fit inside the circle
        int characterSize = 15;
        float radius = shape.getRadius();
        while (text.getLocalBounds().width > 2 * radius - 10 || text.getLocalBounds().height > 2 * radius - 10)
        {
            characterSize--;
            text.setCharacterSize(characterSize);
        }
        text.setCharacterSize(characterSize);

        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        text.setPosition(x, y - text.getLocalBounds().height / 2);
        window.draw(text);

        const std::vector<Node<T> *> children = node->get_children();
        size_t numChildren = node->get_children_size();

        if (numChildren == 0)
            return;

        float totalWidth = (numChildren - 1) * offsetX;
        float startX = x - totalWidth / 2;

        for (size_t i = 0; i < numChildren; ++i)
        {
            Node<T> *child = children[i];
            if (child)
            {
                float childX = startX + i * offsetX;
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x, y + shape.getRadius()), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(childX, y + offsetY), sf::Color::Black)};
                window.draw(line, 2, sf::Lines);

                drawNode(window, child, childX, y + offsetY, offsetX / 2, offsetY);
            }
        }
    }
};

#endif // TREE_HPP
