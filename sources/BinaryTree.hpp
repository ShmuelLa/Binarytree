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
#include <iostream>
#include <vector>
using std::ostream;
using std::vector;
using std::endl;

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
        };

        Node *_root = nullptr;

        public:
            class Preorder_iterator {
                private: 
                    Node *_current;
                
                public:
                    Preorder_iterator(Node *ptr = nullptr) : _current(ptr) {};
                    T& operator*() const {
                        return _current->_content;
                    }

                    T* operator->() const {
                        return &(_current->_content);
                    }

                    Preorder_iterator& operator++() {
                        return *this;
                    }

                    const Preorder_iterator& operator++(int) {
                        return *this;
                    }

                    bool operator==(const Preorder_iterator& other) const {
                        return false;
                    }

                    bool operator!=(const Preorder_iterator& rhs) const {
                        return false;
                    }
            };

            class Inorder_iterator {
                private: 
                    Node *_current;
                
                public:
                    Inorder_iterator(Node *ptr = nullptr) : _current(ptr) {};
                    T& operator*() const {
                        return _current->_content;
                    }

                    T* operator->() const {
                        return &(_current->_content);
                    }

                    Inorder_iterator& operator++() {
                        return *this;
                    }

                    const Inorder_iterator& operator++(int) {
                        return *this;
                    }

                    bool operator==(const Inorder_iterator& other) const {
                        return false;
                    }

                    bool operator!=(const Inorder_iterator& rhs) const {
                        return false;
                    }
            };

            class Postorder_iterator {
                private: 
                    Node *_current;
                
                public:
                    Postorder_iterator(Node *ptr = nullptr) : _current(ptr) {};
                    T& operator*() const {
                        return _current->_content;
                    }

                    T* operator->() const {
                        return &(_current->_content);
                    }

                    Postorder_iterator& operator++() {
                        return *this;
                    }

                    const Postorder_iterator& operator++(int) {
                        return *this;
                    }

                    bool operator==(const Postorder_iterator& other) const {
                        return false;
                    }

                    bool operator!=(const Postorder_iterator& rhs) const {
                        return false;
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