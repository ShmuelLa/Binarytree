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
#include <unordered_set>
using std::ostream;
using std::vector;
using std::endl;
using std::stack;
using std::move;
using std::unordered_set;

namespace ariel {

    template <typename T>

    class BinaryTree {

        class Node {
            friend class BinaryTree;
            Node *_right;
            Node *_left;
            T _content;

            Node(T content) : _content(content), _right(nullptr), _left(nullptr) {};

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
                    unordered_set <Node*> _memory;

                public:
                    Postorder_iterator(Node *root = nullptr) {
                        if (root != nullptr) {
                            _current = root;
                            while (_current != nullptr && _memory.find(_current) == _memory.end()) {
                                if (_current->_left != nullptr && _memory.find(_current->_left) == _memory.end()) {
                                    _current = _current->_left;
                                }
                                else if (_current->_right && _memory.find(_current->_right) == _memory.end()) {
                                    _current = _current->_right;
                                }
                                else {
                                    _current = root;
                                    _memory.insert(_current);
                                    _current = root;
                                    return;
                                }
                            }
                        }
                    }

                    Postorder_iterator& operator++() {
                        Node* tmp = _current;
                        if (_current && _memory.find(_current) == _memory.end()) {
                            while (_current != nullptr && _memory.find(_current) == _memory.end()) {
                                if (_current->_left != nullptr && _memory.find(_current->_left) == _memory.end()) {
                                    _current = _current->_left;
                                }
                                else if (_current->_right && _memory.find(_current->_right) == _memory.end()) {
                                    _current = _current->_right;
                                }
                                else {
                                    _current = tmp;
                                    _memory.insert(_current);
                                    _current = tmp;
                                    return *this;
                                }
                            }
                        }
                        return *this;
                    }

                    Postorder_iterator operator++(int) {
                        Postorder_iterator previous_state = *this;
                        *this->operator++();
                        return *this;
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