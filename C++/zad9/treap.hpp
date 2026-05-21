#pragma once
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <utility>

namespace data_structures {

template<typename T>
class Treap {
    class Node {
        using pNN = std::pair<Node*, Node*>;

        T key;
        int priority;
        Node* left;
        Node* right;

        static pNN split(Node* t, const T& piv) {
            if (!t) return {nullptr, nullptr};

            if (t->key < piv) {
                auto res = split(t->right, piv);

                t->right = res.first;

                return {t, res.second};
            } else {
                auto res = split(t->left, piv);

                t->left = res.second;

                return {res.first, t};
            }
        }

        static Node* merge(Node* l, Node* r) {
            if (!l) return r;
            if (!r) return l;

            if (l->priority < r->priority) {
                r->left = merge(l, r->left);

                return r;
            } else {
                l->right = merge(l->right, r);

                return l;
            }
        }

        static Node* rm(Node* t, const T& key) {
            if (!t) return nullptr;

            if (!(t->key < key) && !(key < t->key)) { 
                Node* merged = Node::merge(t->left, t->right);

                t->left = t->right = nullptr; 
                delete t;

                return merged;
            }

            if (key < t->key) t->left = rm(t->left, key);
            else t->right = rm(t->right, key);

            return t;
        }

    public:
        Node(const T& k) : key(k), priority(std::rand()), left(nullptr), right(nullptr) {}

        Node(const Node& other) : key(other.key), priority(other.priority), left(nullptr), right(nullptr) {
            if (other.left) left = new Node(*other.left);
            if (other.right) right = new Node(*other.right);
        }

        ~Node() {
            delete left;
            delete right;
        }

        static Node* insert(Node* t, const T& key) {
            if (search(t, key)) return t;

            Node* n = new Node(key);
            pNN splitted = split(t, key);

            return merge(merge(splitted.first, n), splitted.second);
        }

        static Node* remove(Node* t, const T& key) {
            if (!t) return nullptr;

            if (!(t->key < key) && !(key < t->key)) { 
                Node* merged = merge(t->left, t->right);

                t->left = t->right = nullptr;
                delete t;

                return merged;
            }

            if (key < t->key) t->left = remove(t->left, key);
            else t->right = remove(t->right, key);

            return t;
        }

        static bool search(Node* t, const T& key) {
            Node* curr = t;

            while (curr) {
                if (key < curr->key) curr = curr->left;
                else if (curr->key < key) curr = curr->right;
                else return true;
            }

            return false;
        }

        static T get_min(Node* t) {
            if (!t) throw std::runtime_error("Drzewiec jest pusty!");

            Node* curr = t;

            while (curr->left) curr = curr->left;

            return curr->key;
        }

        static T get_max(Node* t) {
            if (!t) throw std::runtime_error("Drzewiec jest pusty!");

            Node* curr = t;

            while (curr->right) curr = curr->right;

            return curr->key;
        }

        static void print(Node* t, std::ostream& os) {
            if (!t) return;

            print(t->left, os);
            os << t->key << " ";
            print(t->right, os);
        }
    };

    Node *root;

public:
    Treap() : root(nullptr) {}
    
    Treap(std::initializer_list<T> list) : root(nullptr) {
        for (const auto& x : list) insert(x);
    }
    
    Treap(const Treap& other) : root(nullptr) {
        if (other.root) root = new Node(*other.root);
    }

    Treap& operator=(const Treap& other) {
        if (this != &other) {
            delete root;
            root = other.root ? new Node(*other.root) : nullptr;
        }

        return *this;
    }

    Treap(Treap&& other) noexcept : root(other.root) {
        if (this != &other) other.root = nullptr;
    }

    Treap& operator=(Treap&& other) noexcept {
        if (this != &other) {
            delete root;
            root = other.root;
            other.root = nullptr;
        }

        return *this;
    }

    ~Treap() {
        delete root;
    }

    void insert(const T& x) {
        root = Node::insert(root, x);
    }

    void remove(const T& x) {
        root = Node::remove(root, x);
    }

    bool search(const T& x) const {
        return Node::search(root, x);
    }

    T get_min() const {
        return Node::get_min(root);
    }

    T get_max() const {
        return Node::get_max(root);
    }

    void remove_min() {
        if (root) root = Node::remove(root, get_min());
    }

    void remove_max() {
        if (root) root = Node::remove(root, get_max());
    }

    friend std::ostream& operator<<(std::ostream& os, const Treap& t) {
        if (!t.root) {
            os << "<pusty>";

            return os;
        }

        Node::print(t.root, os);
        return os;
    }
};

}
