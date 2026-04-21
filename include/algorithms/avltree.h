#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <functional>

template<typename Key, typename Value>
class AVLTree {
private:
    struct Node {
        Key key;
        Value value;
        int height;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(const Key& k, const Value& v)
            : key(k), value(v), height(1) {}
    };

    std::unique_ptr<Node> root;

    int getHeight(const std::unique_ptr<Node>& node) const {
        return node ? node->height : 0;
    }

    int getBalance(const std::unique_ptr<Node>& node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(std::unique_ptr<Node>& node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> y) {
        auto x = std::move(y->left);
        y->left = std::move(x->right);
        updateHeight(y);
        x->right = std::move(y);
        updateHeight(x);
        return x;
    }

    std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> x) {
        auto y = std::move(x->right);
        x->right = std::move(y->left);
        updateHeight(x);
        y->left = std::move(x);
        updateHeight(y);
        return y;
    }

    std::unique_ptr<Node> insertNode(std::unique_ptr<Node> node, const Key& key, const Value& value) {
        if (!node) {
            return std::make_unique<Node>(key, value);
        }

        if (key < node->key) {
            node->left = insertNode(std::move(node->left), key, value);
        } else if (key > node->key) {
            node->right = insertNode(std::move(node->right), key, value);
        } else {
            // Update existing value if key already exists
            node->value = value;
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        // Left-Left case
        if (balance > 1 && key < node->left->key) {
            return rotateRight(std::move(node));
        }

        // Right-Right case
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(std::move(node));
        }

        // Left-Right case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(std::move(node->left));
            return rotateRight(std::move(node));
        }

        // Right-Left case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(std::move(node->right));
            return rotateLeft(std::move(node));
        }

        return node;
    }

    void inorderTraversal(const std::unique_ptr<Node>& node, std::function<void(const Key&, const Value&)> callback) const {
        if (!node) return;
        inorderTraversal(node->left, callback);
        callback(node->key, node->value);
        inorderTraversal(node->right, callback);
    }

    Node* search(const std::unique_ptr<Node>& node, const Key& key) const {
        if (!node) return nullptr;
        if (key < node->key) {
            return search(node->left, key);
        } else if (key > node->key) {
            return search(node->right, key);
        } else {
            return node.get();
        }
    }

public:
    AVLTree() = default;

    void insert(const Key& key, const Value& value) {
        root = insertNode(std::move(root), key, value);
    }

    bool find(const Key& key, Value& result) const {
        Node* node = search(root, key);
        if (node) {
            result = node->value;
            return true;
        }
        return false;
    }

    void traverse(std::function<void(const Key&, const Value&)> callback) const {
        inorderTraversal(root, callback);
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

#endif // AVLTREE_H
