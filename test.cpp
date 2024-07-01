#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"

using namespace std;

class Complex;

TEST_CASE("Tree operations and traversals with integers")
{
    auto root = make_unique<Node<int>>(20);
    auto child1 = make_unique<Node<int>>(10);
    auto child2 = make_unique<Node<int>>(30);
    auto child3 = make_unique<Node<int>>(5);
    auto child4 = make_unique<Node<int>>(15);
    auto child5 = make_unique<Node<int>>(25);
    auto child6 = make_unique<Node<int>>(35);
    Tree<int> tree;
    tree.add_root(move(root));
    tree.add_sub_node(*tree.get_root(), move(child1));
    tree.add_sub_node(*tree.get_root(), move(child2));
    tree.add_sub_node(*tree.get_root()->get_children()[0], move(child3));
    tree.add_sub_node(*tree.get_root()->get_children()[0], move(child4));
    tree.add_sub_node(*tree.get_root()->get_children()[1], move(child5));
    tree.add_sub_node(*tree.get_root()->get_children()[1], move(child6));

    SUBCASE("In-order Traversal")
    {
        vector<int> expected = {5, 10, 15, 20, 25, 30, 35};
        vector<int> actual;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("Pre-order Traversal")
    {
        vector<int> expected = {20, 10, 5, 15, 30, 25, 35};
        vector<int> actual;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("Post-order Traversal")
    {
        vector<int> expected = {5, 15, 10, 25, 35, 30, 20};
        vector<int> actual;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("BFS Traversal")
    {
        vector<int> expected = {20, 10, 30, 5, 15, 25, 35};
        vector<int> actual;
        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("DFS Traversal")
    {
        vector<int> expected = {20, 10, 5, 15, 30, 25, 35};
        vector<int> actual;
        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }
}

TEST_CASE("Tree operations and traversals with Complex numbers")
{
    auto root = make_unique<Node<Complex>>(Complex(8, 8));
    auto child1 = make_unique<Node<Complex>>(Complex(4, 4));
    auto child2 = make_unique<Node<Complex>>(Complex(12, 12));
    auto child3 = make_unique<Node<Complex>>(Complex(2, 2));
    auto child4 = make_unique<Node<Complex>>(Complex(6, 6));
    auto child5 = make_unique<Node<Complex>>(Complex(10, 10));
    auto child6 = make_unique<Node<Complex>>(Complex(14, 14));
    Tree<Complex> tree;
    tree.add_root(move(root));
    tree.add_sub_node(*tree.get_root(), move(child1));
    tree.add_sub_node(*tree.get_root(), move(child2));
    tree.add_sub_node(*tree.get_root()->get_children()[0], move(child3));
    tree.add_sub_node(*tree.get_root()->get_children()[0], move(child4));
    tree.add_sub_node(*tree.get_root()->get_children()[1], move(child5));
    tree.add_sub_node(*tree.get_root()->get_children()[1], move(child6));

    SUBCASE("In-order Traversal")
    {
        vector<Complex> expected = {Complex(2, 2), Complex(4, 4), Complex(6, 6), Complex(8, 8), Complex(10, 10), Complex(12, 12), Complex(14, 14)};
        vector<Complex> actual;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("Pre-order Traversal")
    {
        vector<Complex> expected = {Complex(8, 8), Complex(4, 4), Complex(2, 2), Complex(6, 6), Complex(12, 12), Complex(10, 10), Complex(14, 14)};
        vector<Complex> actual;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("Post-order Traversal")
    {
        vector<Complex> expected = {Complex(2, 2), Complex(6, 6), Complex(4, 4), Complex(10, 10), Complex(14, 14), Complex(12, 12), Complex(8, 8)};
        vector<Complex> actual;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("BFS Traversal")
    {
        vector<Complex> expected = {Complex(8, 8), Complex(4, 4), Complex(12, 12), Complex(2, 2), Complex(6, 6), Complex(10, 10), Complex(14, 14)};
        vector<Complex> actual;
        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("DFS Traversal")
    {
        vector<Complex> expected = {Complex(8, 8), Complex(4, 4), Complex(2, 2), Complex(6, 6), Complex(12, 12), Complex(10, 10), Complex(14, 14)};
        vector<Complex> actual;
        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }
}

TEST_CASE("Tree operations and traversals with a 3-ary tree of integers")
{
    auto root = make_unique<Node<int>>(100);
    auto child1 = make_unique<Node<int>>(50);
    auto child2 = make_unique<Node<int>>(150);
    auto child3 = make_unique<Node<int>>(25);
    auto child4 = make_unique<Node<int>>(75);
    auto child5 = make_unique<Node<int>>(125);
    auto child6 = make_unique<Node<int>>(175);
    auto child7 = make_unique<Node<int>>(60);
    Tree<int, 3> tree;
    tree.add_root(move(root));
    tree.add_sub_node(*tree.get_root(), move(child1));
    tree.add_sub_node(*tree.get_root(), move(child2));
    tree.add_sub_node(*tree.get_root()->get_children()[0], move(child3));
    tree.add_sub_node(*tree.get_root()->get_children()[0], move(child4));
    tree.add_sub_node(*tree.get_root()->get_children()[1], move(child5));
    tree.add_sub_node(*tree.get_root()->get_children()[1], move(child6));
    tree.add_sub_node(*tree.get_root()->get_children()[0]->get_children()[1], move(child7));

    SUBCASE("DFS Traversal")
    {
        vector<int> expected = {100, 50, 25, 75, 60, 150, 125, 175};
        vector<int> actual;
        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("BFS Traversal")
    {
        vector<int> expected = {100, 50, 150, 25, 75, 125, 175, 60};
        vector<int> actual;
        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it)
        {
            actual.push_back(it->get_value());
        }
        CHECK(actual == expected);
    }

    SUBCASE("Tree Drawing")
    {
        tree.drawTree();
    }
}
