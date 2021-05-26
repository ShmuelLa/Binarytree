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
using std::ostream;

namespace ariel {

    template <typename T>

    class BinaryTree {

        class Node {
            friend class BinaryTree;
            Node *_parent;
            Node *_right;
            Node *_left;
            T _content;
            Node(T content) : _content(content), _parent(NULL), _right(NULL), _left(NULL) {};
        };

        Node *root;

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
                        return true;
                    }
                    bool operator!=(const Preorder_iterator& rhs) const {
                        return true;
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
                        return true;
                    }
                    bool operator!=(const Inorder_iterator& rhs) const {
                        return true;
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
                        return true;
                    }
                    bool operator!=(const Postorder_iterator& rhs) const {
                        return true;
                    }
            };

            BinaryTree& add_root(const T & num) {
                this->root = new Node(num);
                return *this;
            }
            BinaryTree& add_left(const T & parent, const T & num) {
                return *this;
            }
            BinaryTree& add_right(const T & parent, const T & num) {
                return *this;
            }
            friend ostream &operator<<(ostream &stream, const BinaryTree<T> &tree) {
                return stream;
            }
            Inorder_iterator begin() {
                return Inorder_iterator(nullptr);
            }
            Inorder_iterator end() {
                return Inorder_iterator(nullptr);
            }
            Preorder_iterator begin_preorder() {
                return Preorder_iterator(nullptr);
            }
            Preorder_iterator end_preorder() {
                return Preorder_iterator(nullptr);
            }
            Inorder_iterator begin_inorder() {
                return Inorder_iterator(nullptr);
            }
            Inorder_iterator end_inorder() {
                return Inorder_iterator(nullptr);
            }
            Postorder_iterator begin_postorder() {
                return Postorder_iterator(nullptr);
            }
            Postorder_iterator end_postorder() {
                return Postorder_iterator(nullptr);
            }
    };
}