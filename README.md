# K-ary Tree Container Project

## Overview

This project implements a container representing a k-ary tree in C++. The container supports various types of tree traversals, including Pre-Order, Post-Order, In-Order, BFS, DFS, and Heap. By default, the tree is a binary tree (k=2). The project also includes a class named `Complex` to represent complex numbers, extensive tests, and a demonstration of the functionality using the SFML library for a graphical user interface.

## File Structure

- `complex.cpp`: Implementation of the Complex class.
- `complex.hpp`: Header file for the Complex class.
- `doctest.h`: Header file for the Doctest testing framework.
- `iterators.hpp`: Header file containing iterator classes for various tree traversals.
- `main.cpp`: Main file demonstrating the functionality of the k-ary tree.
- `node.hpp`: Header file defining the Node class used in the k-ary tree.
- `test.cpp`: File containing extensive tests for the k-ary tree and its components.
- `tree.hpp`: Header file defining the Tree class, which represents the k-ary tree.

## Requirements

- C++17 or later
- A C++ compiler (e.g., g++, clang++)
- SFML library (for graphical user interface)
- CMake (optional, for build configuration)

## Installation

To build and run the project, follow these steps:

1. **Clone the repository**:
    ```sh
    git clone https://github.com/elyasafko/SP2---EX4.git
    ```

2. **Install SFML**:
    Follow the instructions on the [SFML website](https://www.sfml-dev.org/download.php) to install SFML for your operating system.

3. **Compile the project**:
    ```sh
    make all
    ```

4. **Run the executable**:
    ```sh
    ./output
    ```

## Usage

### Demonstration

The `main.cpp` file provides a demonstration of the k-ary tree functionality. It creates a binary tree and a 3-ary tree, adds nodes, and iterates over the tree using various traversal methods. Additionally, it uses the SFML library to display the tree graphically.

### Complex Class

The `Complex` class in `complex.cpp` and `complex.hpp` represents complex numbers. It supports basic arithmetic operations, comparison operators, and stream insertion for easy output.

### Tree Traversals

The `iterators.hpp` file contains classes for different tree traversal methods. These iterators can be used to traverse the tree in various orders.

### Testing

The `test.cpp` file contains tests to ensure the correctness of the k-ary tree and its components. The tests are written using the Doctest framework.

