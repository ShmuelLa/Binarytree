#include "sources/BinaryTree.hpp"
#include "doctest.h"
using namespace std;
using namespace ariel;

TEST_CASE("Inorder Test") {
    BinaryTree<int> tree;
    tree.add_root(0);
    tree.add_right(0,1);
    tree.add_right(1,2);
}
