#include "sources/BinaryTree.hpp"
#include "doctest.h"
#include <string>
#include <iostream>
using namespace std;
using namespace ariel;

TEST_CASE("Basic Iteration Test") {
    BinaryTree<int> tree;
    tree.add_root(3).
    add_left(3, 1).
    add_left(1, 0).
    add_right(1, 2).
    add_right(3, 4);
    int tester = 0;
    for (int element : tree) {
        CHECK_EQ(tester, element);
        tester++;
    }
    CHECK_THROWS(tree.add_right(50, 4));
    CHECK_THROWS(tree.add_right(50, 3));
    CHECK_THROWS(tree.add_left(50, 30));
    CHECK_THROWS(tree.add_left(50, 3));
}

TEST_CASE("Preorder Test") {
    BinaryTree<int> tree;
    tree.add_root(0).
    add_left(0, 9).
    add_left(9, 2).
    add_right(9, 3).
    add_right(0, 4).
    add_left(0, 1);
    int tester = 0;
    for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
        CHECK_EQ(tester, (*it));
        tester++;
    }
    CHECK_THROWS(tree.add_right(100, 4));
    CHECK_THROWS(tree.add_right(100, 3));
    CHECK_THROWS(tree.add_left(100, 30));
    CHECK_THROWS(tree.add_left(100, 3));
}

TEST_CASE("Inorder Test") {
    BinaryTree<int> tree;
    tree.add_root(3).
    add_left(3, 1).
    add_left(1, 0).
    add_right(1, 2).
    add_right(3, 4);
    int tester = 0;
    for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
        CHECK_EQ(tester, (*it));
        tester++;
    }
}

TEST_CASE("Postorder Test") {
    BinaryTree<int> tree;
    tree.add_root(4).
    add_left(4, 2).
    add_left(2, 0).
    add_right(2, 1).
    add_right(4, 3);
    int tester = 0;
    for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
        CHECK_EQ(tester, (*it));
        tester++;
    }
}

TEST_CASE("Inorder String Test") {
    BinaryTree<string> tree;
    tree.add_root("3").
    add_left("3", "1").
    add_left("1", "0").
    add_right("1", "2").
    add_right("3", "4");
    int tester = 0;
    for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
        CHECK_EQ(to_string(tester), (*it));
        tester++;
    }
    CHECK_THROWS(tree.add_left("11", "1"));
    CHECK_THROWS(tree.add_right("11", "1"));
}

TEST_CASE("Basic iteration String Test") {
    BinaryTree<string> tree;
    tree.add_root("3").
    add_left("3", "1").
    add_left("1", "0").
    add_right("1", "2").
    add_right("3", "4");
    int tester = 0;
    for (string element : tree) {
        CHECK_EQ(to_string(tester), element);
        tester++;
    }
    CHECK_THROWS(tree.add_left("11", "1"));
    CHECK_THROWS(tree.add_right("11", "1"));
}

TEST_CASE("Exceptions") {
    BinaryTree<int> tree_int;
    tree_int.add_root(0);
    CHECK_THROWS(tree_int.add_left(1, 2));
    CHECK_THROWS(tree_int.add_left(40, 0));
    CHECK_THROWS(tree_int.add_right(1, 2));
    CHECK_THROWS(tree_int.add_right(1, 0));
}

TEST_CASE("Corrent Actions") {
    BinaryTree<int> tree_int;
    tree_int.add_root(0);
    CHECK_NOTHROW(tree_int.add_root(0));
    CHECK_NOTHROW(tree_int.add_left(0, 1));
    CHECK_NOTHROW(tree_int.add_right(0, 2));
    CHECK_NOTHROW(tree_int.add_left(0, 3));
    CHECK_NOTHROW(tree_int.add_right(0, 4));
    CHECK_NOTHROW(tree_int.add_left(0, 5));
    CHECK_NOTHROW(tree_int.add_right(0, 6));
}