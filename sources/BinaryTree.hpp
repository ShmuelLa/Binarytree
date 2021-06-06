/**
 * @file BinaryTree.hpp
 * @author Shmuel.Lavian
 * @brief Binary tree with iterators implementations
 * @version 0.1
 * @date 2021-05-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <iterator>
#include <iostream>
#include <vector>
#include <stack>
using std::ostream;
using std::vector;
using std::endl;
using std::stack;
using std::move;

namespace ariel {

    template <typename T>

    class BinaryTree {

        class Node {
            friend class BinaryTree;
            Node *_parent;
            Node *_right;
            Node *_left;
            T _content;

            Node(T content) : _content(content), _parent(nullptr), _right(nullptr), _left(nullptr) {};

            // ~Node() {
            //     delete this->_left;
            //     delete this->_right;
            //     // delete this->_parent;
            //     // delete this->_content;
            // }

            // Node& operator= (const Node &other){
            //     if (this != &other) {
            //         this = new Node(other);
            //     }
            //     return *this;
            // }
        };

        Node *_root = nullptr;

        public:

            class Generic_Iterator {
                public:
                    Node *_current;
                    T& operator*() const {
                        return _current->_content;
                    }

                    T* operator->() const {
                        return &(_current->_content);
                    }

                    bool operator==(const Generic_Iterator& other) const {
                        return (_current == other._current);
                    }

                    bool operator!=(const Generic_Iterator& rhs) const {
                        return false;
                    }
            };

            class Preorder_iterator : public Generic_Iterator {
                private:
                    stack <Node*> _memory;

                public:
                    Preorder_iterator(Node *root = nullptr) {
                        if (root != nullptr) {
                            _memory.push(root);
                            Generic_Iterator::_current = _memory.top();
                        }
                    }

                    Preorder_iterator& operator++() {
                        if (!_memory.empty()) {
                            Node* tmp_node = Generic_Iterator::_current;
                            _memory.pop();
                            if (tmp_node->_right != nullptr) {
                                _memory.push(tmp_node->_right);
                            }
                            if (tmp_node->_left != nullptr) {
                                _memory.push(tmp_node->_left);
                            }
                            if (!_memory.empty()) {
                                Generic_Iterator::_current = _memory.top();
                            }
                        }
                        return *this;
                    }

                    Preorder_iterator operator++(int) {
                        Preorder_iterator previous_state = *this;
                        *this->operator++();
                        return previous_state;
                    }
            };

            class Inorder_iterator : public Generic_Iterator {
                public:
                    Inorder_iterator(Node *root = nullptr) {
                        if (root == nullptr) {
                            Generic_Iterator::_current = nullptr;
                            return;
                        }
                    }

                    Inorder_iterator& operator++() {
                        return *this;
                    }

                    const Inorder_iterator& operator++(int) {
                        return *this;
                    }
            };

            class Postorder_iterator : public Generic_Iterator {
                public:
                    Postorder_iterator(Node *root = nullptr) {
                        if (root == nullptr) {
                            Generic_Iterator::_current = nullptr;
                            return;
                        }
                    }

                    Postorder_iterator& operator++() {
                        return *this;
                    }

                    const Postorder_iterator& operator++(int) {
                        return *this;
                    }
            };

            BinaryTree() : _root(nullptr) {}

            /**
             * @brief recursively scans for a specific node in the tree on all left and right nodes
             * this function will be call each time when trying to add a new node
             * 
             * @param parent_content the content of the node to scan, usually a parent to add child to
             * @param current_node the current node the function is pointing at
             * @return Node* the node found, null pointer otherwise
             */
            Node* locate_node(const T &parent_content, Node *current_node) const {
                if (current_node == nullptr) {
                    return nullptr;
                }
                if (current_node->_content == parent_content) {
                    return current_node;
                }
                Node *scanner = this->locate_node(parent_content, current_node->_right);
                if (scanner != nullptr) {
                    return scanner;
                }
                return locate_node(parent_content, current_node->_left);
            }

            BinaryTree& add_root(const T & num) {
                if (this->_root == nullptr) {
                    this->_root = new Node(num);
                    return *this;
                }
                this->_root->_content = num;
                return *this;
            }

            BinaryTree<T> & add_left(const T & parent_content, const T & num) {
                Node* parent = locate_node(parent_content, this->_root);
                if (parent == nullptr) {
                    throw("Parent not found in tree");
                }
                if (parent->_left == nullptr) {
                    parent->_left = new Node(num);
                    return *this;
                }
                parent->_left->_content = num;
                return *this;
            }

            BinaryTree<T> & add_right(const T & parent_content, const T & num) {
                Node* parent = locate_node(parent_content, this->_root);
                if (parent == nullptr) {
                    throw("Parent not found in tree");
                }
                if (parent->_right == nullptr) {
                    parent->_right = new Node(num);
                    return *this;
                }
                parent->_right->_content = num;
                return *this;
            }

            friend ostream &operator<<(ostream &stream, const BinaryTree<T> &tree) {
                if (tree->_root == nullptr) {
                    stream << "Empty Tree" << endl;
                    return stream; 
                }
                stream << "Tree" << endl;
                return stream;
            }

            Inorder_iterator begin() {
                return Inorder_iterator(_root);
            }

            Inorder_iterator end() {
                return Inorder_iterator(nullptr);
            }

            Preorder_iterator begin_preorder() {
                return Preorder_iterator(_root);
            }

            Preorder_iterator end_preorder() {
                return Preorder_iterator(nullptr);
            }

            Inorder_iterator begin_inorder() {
                return Inorder_iterator(_root);
            }

            Inorder_iterator end_inorder() {
                return Inorder_iterator(nullptr);
            }

            Postorder_iterator begin_postorder() {
                return Postorder_iterator(nullptr);
            }

            Postorder_iterator end_postorder() {
                return Postorder_iterator(_root);
            }
    };
}