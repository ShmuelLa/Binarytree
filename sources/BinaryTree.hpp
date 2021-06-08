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
#include <stack>
#include <new>
#include <sstream>
using std::ostream;
using std::endl;
using std::stack;
using std::move;

namespace ariel {

    template<typename T> class BinaryTree {

        class Node {
            public:
                Node *_right;
                Node *_left;
                T _content;

                Node(T content) : _content(content), _right(nullptr), _left(nullptr) {};
        };

        Node *_root = nullptr;

        public:
            class Preorder_iterator {
                private:
                    stack <Node*> _memory;
                    Node *_current;

                public:
                    Preorder_iterator(Node *root = nullptr) {
                        if (root != nullptr) {
                            _memory.push(root);
                            _current = _memory.top();
                            return;
                        }
                        _current = nullptr;
                    }

                    Preorder_iterator& operator++() {
                        if (!_memory.empty()) {
                            Node* tmp_node = _current;
                            _memory.pop();
                            if (tmp_node->_right != nullptr) {
                                _memory.push(tmp_node->_right);
                            }
                            if (tmp_node->_left != nullptr) {
                                _memory.push(tmp_node->_left);
                            }
                            if (!_memory.empty()) {
                                _current = _memory.top();
                            }
                            else {
                                _current = nullptr;
                            }
                        }
                        else {
                            _current = nullptr;
                        }
                        return *this;
                    }

                    Preorder_iterator operator++(int) {
                        Preorder_iterator previous_state = *this;
                        *this->operator++();
                        return previous_state;
                    }

                    T& operator*() const {
                        return _current->_content;
                    }

                    T* operator->() const {
                        return &(_current->_content);
                    }

                    bool operator==(const Preorder_iterator& other) const {
                        return (_current == other._current);
                    }

                    bool operator!=(const Preorder_iterator& other) const {
                        return !(_current == other._current);
                    }
            };

            class Inorder_iterator {
                private:
                    stack <Node*> _memory;
                    Node *_current;

                public:
                    Node* get_node() {
                        return this->_current;
                    }

                    Inorder_iterator(Node *root = nullptr) {
                        while (root != nullptr) {
                            _memory.push(root);
                            root = root->_left;
                        }
                        if (!_memory.empty()) {
                            _current = _memory.top();
                            _memory.pop();
                            return;
                        }
                        _current = nullptr;
                    }

                    Inorder_iterator& operator++() {
                        if(_memory.empty() && _current == nullptr) {
                            _current = nullptr;
                        }
                        else {
                            if(_current->_right == nullptr && !_memory.empty()) {
                                _current = _memory.top();
                                _memory.pop();
                            }
                            else if (_current->_right == nullptr && _memory.empty()) {
                                _current = nullptr;
                            } 
                            else {
                                _current = _current->_right;
                                while(_current != nullptr){
                                    _memory.push(_current);
                                    _current = _current->_left;
                                }
                                _current = _memory.top();
                                _memory.pop();
                            }
                        }
                        return *this;
                    }

                    Inorder_iterator operator++(int) {
                        Inorder_iterator previous_state = *this;
                        *this->operator++();
                        return previous_state;
                    }

                    T& operator*() const {
                        return _current->_content;
                    }

                    T* operator->() const {
                        return &(_current->_content);
                    }

                    bool operator==(const Inorder_iterator& other) const {
                        return (_current == other._current);
                    }

                    bool operator!=(const Inorder_iterator& other) const {
                        return !(_current == other._current);
                    }
            };

            class Postorder_iterator {
                private:
                    Node* _current;
                    Node* _next;
                    stack <Node*> _memory;

                public:
                    Postorder_iterator(Node *root = nullptr) {
                        if (root != nullptr) {
                            stack<Node*> iteration_stack;
                            iteration_stack.push(root);
                            while (!iteration_stack.empty()) {
                                _next = iteration_stack.top();
                                iteration_stack.pop();
                                _memory.push(_next);
                                if (_next->_left) {
                                    iteration_stack.push(_next->_left);
                                }
                                if (_next->_right) {
                                    iteration_stack.push(_next->_right);
                                }
                            }
                            _current = _memory.top();
                        }
                        else {
                            _current = nullptr;
                        }
                    }

                    Postorder_iterator& operator++() {
                        if (_memory.empty()) {
                            _current = nullptr;
                            return *this;
                        }
                        _memory.pop();
                        if (!_memory.empty()) {
                            _current = _memory.top();
                        }
                        else {
                            _current = nullptr;
                        }
                        return *this;
                    }

                    Postorder_iterator operator++(int) {
                        Postorder_iterator previous_state = *this;
                        *this->operator++();
                        return previous_state;
                    }

                    T& operator*() const {
                        return _current->_content;
                    }

                    T* operator->() const {
                        return &(_current->_content);
                    }

                    bool operator==(const Postorder_iterator& other) const {
                        return (_current == other._current);
                    }

                    bool operator!=(const Postorder_iterator& other) const {
                        return !(_current == other._current);
                    }
            };

            BinaryTree() : _root(nullptr) {}

            BinaryTree(const BinaryTree& other) {
                // delete this;
                if (other._root) {
                    _root = new Node(other._root->_content);
                    recursive_tree_copy(other._root, _root);
                }
            }

            BinaryTree(BinaryTree&& other) noexcept {
                _root = other._root;
                other._root = nullptr;
            }

            ~BinaryTree() {
                recursive_delete_tree(_root);
                _root = nullptr;
            }

            /**
             * @brief Used to recursively iterate through the tree and delete all its node
             * This method is used in the destructor.
             * 
             * @param next the next node to delete
             */
            void recursive_delete_tree(Node* next) {
                if (next == nullptr) {
                    return;
                }
                recursive_delete_tree(next->_left);
                recursive_delete_tree(next->_right);
                delete next;
            }

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
            
            /**
             * @brief Recursively iterate through the binary tree in order to copy it
             * This is a tree recursion function that calls itself on the right and 
             * left paths accordingly
             * 
             * @param source_node source node to iterate from the target tree
             * @param other source node to iterate from the source tree
             */
            void recursive_tree_copy(Node* source_node, Node* other) {
                if (other->_left) {
                    source_node->_left = new Node(other->_left->_content);
                    recursive_tree_copy(source_node->_left, other->_left);
                }
                if (other->_right) {
                    source_node->_right = new Node(other->_right->_content);
                    recursive_tree_copy(source_node->_right, other->_right);
                }
            }

            BinaryTree& add_root(const T & content) {
                if (this->_root == nullptr) {
                    this->_root = new Node(content);
                    return *this;
                }
                this->_root->_content = content;
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
                if (tree._root == nullptr) {
                    stream << "Empty Tree" << endl;
                    return stream; 
                }
                stream << "Tree: " << endl;
                return stream;
            }

            BinaryTree& operator=(const BinaryTree& other) {
                if (this == &other || !other._root) {
                    return *this;
                }
                delete this;
                _root = new Node(other._root->_content);
                recursive_tree_copy(_root, other._root);
                return *this;
            }

            BinaryTree& operator=(BinaryTree&& other) noexcept {
                _root = other._root;
                other._root = nullptr;
                return *this;
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
                return Postorder_iterator(_root);
            }

            Postorder_iterator end_postorder() {
                return Postorder_iterator(nullptr);
            }
    };
}