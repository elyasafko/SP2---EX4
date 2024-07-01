#include <SFML/Graphics.hpp>
#include <iostream>
#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"

using namespace std;

int main()
{
    Tree<int, 3> tree_int_three; // Create a 3-ary tree
    auto root_int_three = make_unique<Node<int>>(1);
    tree_int_three.add_root(move(root_int_three));

    auto child1 = make_unique<Node<int>>(2);
    auto child2 = make_unique<Node<int>>(3);
    auto child3 = make_unique<Node<int>>(4);
    auto child4 = make_unique<Node<int>>(5);
    auto child5 = make_unique<Node<int>>(6);
    auto child6 = make_unique<Node<int>>(7);
    auto child7 = make_unique<Node<int>>(8);

    tree_int_three.add_sub_node(*tree_int_three.get_root(), move(child1));
    tree_int_three.add_sub_node(*tree_int_three.get_root(), move(child2));
    tree_int_three.add_sub_node(*tree_int_three.get_root(), move(child3));
    tree_int_three.add_sub_node(*tree_int_three.get_root()->get_children()[0], move(child4));
    tree_int_three.add_sub_node(*tree_int_three.get_root()->get_children()[0], move(child5));
    tree_int_three.add_sub_node(*tree_int_three.get_root()->get_children()[0], move(child6));

    tree_int_three.drawTree();

    Tree<Complex, 5> tree_complex; // 5-ary tree that contains Complex numbers.
    auto root_complex = make_unique<Node<Complex>>(Complex(1.1, 2.2));

    // Create additional nodes with complex numbers
    auto n1 = make_unique<Node<Complex>>(Complex(1.2, 2));
    auto n2 = make_unique<Node<Complex>>(Complex(1.3, 2));
    auto n3 = make_unique<Node<Complex>>(Complex(1, 2));
    auto n4 = make_unique<Node<Complex>>(Complex(1, 2));
    auto n5 = make_unique<Node<Complex>>(Complex(1.6, 2.7));

    tree_complex.add_root(move(root_complex));

    // Add sub-nodes to the tree
    tree_complex.add_sub_node(*tree_complex.get_root(), move(n1));
    tree_complex.add_sub_node(*tree_complex.get_root(), move(n2));
    tree_complex.add_sub_node(*tree_complex.get_root(), move(n3));
    tree_complex.add_sub_node(*tree_complex.get_root(), move(n4));
    tree_complex.add_sub_node(*tree_complex.get_root(), move(n5));

    tree_complex.drawTree();

    // *****************************************************************************************************************

    Tree<int> tree_int;
    auto root_int_two = make_unique<Node<int>>(1);
    auto child8 = make_unique<Node<int>>(2);
    auto child9 = make_unique<Node<int>>(3);
    auto child10 = make_unique<Node<int>>(4);
    auto child11 = make_unique<Node<int>>(5);
    auto child12 = make_unique<Node<int>>(6);
    tree_int.add_root(move(root_int_two));

    tree_int.add_sub_node(*tree_int.get_root(), move(child8));
    tree_int.add_sub_node(*tree_int.get_root(), move(child9));
    tree_int.add_sub_node(*tree_int.get_root()->get_children()[0], move(child10));
    tree_int.add_sub_node(*tree_int.get_root()->get_children()[0], move(child11));
    tree_int.add_sub_node(*tree_int.get_root()->get_children()[1], move(child12));

    tree_int.drawTree(); // Starting position of the root
    // The tree should look like:
    /*
     *       root = 1
     *     /       \
     *     2       3
     *   /  \      /
     *  4    5    6
     */

    cout << "PreOrder: ";
    for (auto node = tree_int.begin_pre_order(); node != tree_int.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1, 2 , 4, 5, 3, 6
    cout << endl
         << "PostOrder: ";

    for (auto node = tree_int.begin_post_order(); node != tree_int.end_post_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 4, 5, 2, 6, 3, 1
    cout << endl
         << "InOrder: ";

    for (auto node = tree_int.begin_in_order(); node != tree_int.end_in_order(); ++node)
    {
        cout << node->get_value() << ", ";

    } // prints: 4, 2, 5, 1, 6, 3
    cout << endl
         << "BFS: ";

    for (auto node = tree_int.begin_bfs(); node != tree_int.end_bfs(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1, 2, 3, 4, 5, 6
    cout << endl
         << "DFS: ";

    for (auto node = tree_int.begin_dfs(); node != tree_int.end_dfs(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1, 2, 4, 5, 3, 6
    cout << endl
         << "Range-based for loop(BFS): ";

    for (auto node : tree_int)
    {
        cout << node << ", ";
    } // same as BFS: 1, 2, 3, 4, 5, 6
    cout << endl
         << "Heap Iterator: ";
    for (auto node = tree_int.begin_heap(); node != tree_int.end_heap(); ++node)
    {
        cout << node->get_value() << ", ";
    }
    cout << endl;

    // Now let's create a 3-ary tree.
    Tree<double, 3> three_ary_tree; // 3-ary tree.
    auto root_node_d = make_unique<Node<double>>(1.1);
    auto n1_d = make_unique<Node<double>>(1.2);
    auto n2_d = make_unique<Node<double>>(1.3);
    auto n3_d = make_unique<Node<double>>(1.4);
    auto n4_d = make_unique<Node<double>>(1.5);
    auto n5_d = make_unique<Node<double>>(1.6);
    three_ary_tree.add_root(move(root_node_d));
    three_ary_tree.add_sub_node(*three_ary_tree.get_root(), move(n1_d));
    three_ary_tree.add_sub_node(*three_ary_tree.get_root(), move(n2_d));
    three_ary_tree.add_sub_node(*three_ary_tree.get_root(), move(n3_d));
    three_ary_tree.add_sub_node(*three_ary_tree.get_root()->get_children()[0], move(n4_d));
    three_ary_tree.add_sub_node(*three_ary_tree.get_root()->get_children()[1], move(n5_d));
    three_ary_tree.drawTree(); // Starting position of the root

    cout << "PreOrder(DFS): ";
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } 
    cout << endl
         << "PostOrder(DFS): ";

    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } 
    cout << endl
         << "InOrder(DFS): ";

    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node->get_value() << ", ";

    } 
    cout << endl
         << "BFS: ";

    for (auto node = three_ary_tree.begin_bfs(); node != three_ary_tree.end_bfs(); ++node)
    {
        cout << node->get_value() << ", ";
    } 
    cout << endl
         << "DFS: ";

    for (auto node = three_ary_tree.begin_dfs(); node != three_ary_tree.end_dfs(); ++node)
    {
        cout << *node << ", ";
    } 
    cout << endl
         << "Range-based for loop(BFS): ";

    for (auto node : three_ary_tree)
    {
        cout << node << ", ";
    }
    cout << endl
         << "Heap Iterator(DFS): ";
    for (auto node = three_ary_tree.begin_heap(); node != three_ary_tree.end_heap(); ++node)
    {
        cout << node->get_value() << ", ";
    }
    cout << endl;

    auto root_str = make_unique<Node<string>>("root");
    auto child1_str = make_unique<Node<string>>("child1");
    auto child2_str = make_unique<Node<string>>("child2");
    auto child3_str = make_unique<Node<string>>("child3");
    auto child4_str = make_unique<Node<string>>("child4");
    auto child5_str = make_unique<Node<string>>("child5");
    Tree<string, 3> tree_str;
    tree_str.add_root(move(root_str));
    tree_str.add_sub_node(*tree_str.get_root(), move(child1_str));
    tree_str.add_sub_node(*tree_str.get_root(), move(child2_str));
    tree_str.add_sub_node(*tree_str.get_root(), move(child3_str));
    tree_str.add_sub_node(*tree_str.get_root()->get_children()[0], move(child4_str));
    tree_str.add_sub_node(*tree_str.get_root()->get_children()[1], move(child5_str));
    tree_str.drawTree(); // Starting position of the root
    cout << "PreOrder(DFS): ";
    for (auto node = tree_str.begin_pre_order(); node != tree_str.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } 
    cout << endl
         << "PostOrder(DFS): ";

    for (auto node = tree_str.begin_post_order(); node != tree_str.end_post_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } 
    cout << endl
         << "InOrder(DFS): ";

    for (auto node = tree_str.begin_in_order(); node != tree_str.end_in_order(); ++node)
    {
        cout << node->get_value() << ", ";

    } 
    cout << endl
         << "BFS: ";

    for (auto node = tree_str.begin_bfs(); node != tree_str.end_bfs(); ++node)
    {
        cout << *node << ", ";
    } 
    cout << endl
         << "DFS: ";

    for (auto node = tree_str.begin_dfs(); node != tree_str.end_dfs(); ++node)
    {
        cout << node->get_value() << ", ";
    } 
    cout << endl
         << "Range-based for loop(BFS): ";

    for (auto node : tree_str)
    {
        cout << node << ", ";
    } 
    cout << endl
         << "Heap Iterator(DFS): ";
    for (auto node = tree_str.begin_heap(); node != tree_str.end_heap(); ++node)
    {
        cout << node->get_value() << ", ";
    }
    cout << endl;


    return 0;
}
