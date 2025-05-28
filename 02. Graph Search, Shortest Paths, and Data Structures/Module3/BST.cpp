/*
 * File Name    : BST.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-28
 *
 * Description  : BST implementation
 */

#include <bits/stdc++.h>

using namespace std;

struct BSTNode
{
    int key;         // The data stored in the node
    BSTNode *left;   // Pointer to left subtree
    BSTNode *right;  // Pointer to right subtree
    BSTNode *parent; // Pointer to parent

    BSTNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BinarySearchTree
{
private:
    BSTNode *root = nullptr;

public:
    BinarySearchTree() {}

    BSTNode *search(int k)
    {
        return searchHelper(root, k);
    }

private:
    BSTNode *searchHelper(BSTNode *node, int k)
    {
        if (node == nullptr || node->key == k)
        {
            return node;
        }

        if (k < node->key)
        {
            return searchHelper(node->left, k);
        }
        else
        {
            return searchHelper(node->right, k);
        }
    }

public:
    void insert(int k)
    {
        root = insertHelper(root, k);
    }

private:
    BSTNode *insertHelper(BSTNode *node, int k)
    {
        if (node == nullptr)
        {
            return new BSTNode(k);
        }

        if (k < node->key)
        {
            node->left = insertHelper(node->left, k);
            if (node->left != nullptr)
            {
                node->left->parent = node;
            }
        }
        else if (k > node->key)
        {
            node->right = insertHelper(node->right, k);
            if (node->right != nullptr)
            {
                node->right->parent = node;
            }
        }
        return node;
    }

public:
    BSTNode *findMin()
    {
        return findMinHelper(root);
    }

    BSTNode *findMax()
    {
        return findMaxHelper(root);
    }

private:
    BSTNode *findMinHelper(BSTNode *node)
    {
        if (node == nullptr)
            return nullptr;

        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    BSTNode *findMaxHelper(BSTNode *node)
    {
        if (node == nullptr)
            return nullptr;

        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node;
    }

public:
    BSTNode *predecessor(int k)
    {
        BSTNode *node = search(k);
        if (node == nullptr)
            return nullptr;

        if (node->left != nullptr)
        {
            return findMaxHelper(node->left);
        }

        BSTNode *parent = node->parent;
        while (parent != nullptr && node == parent->left)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }
    BSTNode *successor(int k)
    {
        BSTNode *node = search(k);
        if (node == nullptr)
            return nullptr;

        if (node->right != nullptr)
        {
            return findMinHelper(node->right);
        }
        BSTNode *parent = node->parent;
        while (parent != nullptr && node == parent->right)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    void deleteKey(int k)
    {
        root = deleteHelper(root, k);
    }

private:
    BSTNode *deleteHelper(BSTNode *node, int k)
    {
        if (node == nullptr)
            return nullptr;

        if (k < node->key)
        {
            node->left = deleteHelper(node->left, k);
        }
        else if (k > node->key)
        {
            node->right = deleteHelper(node->right, k);
        }
        else
        {
            // Case 1: Node has no children (leaf)
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }

            // Case 2: Node has one child
            if (node->left == nullptr)
            {
                BSTNode *temp = node->right;
                if (temp != nullptr)
                    temp->parent = node->parent;
                delete node;
                return temp;
            }
            if (node->right == nullptr)
            {
                BSTNode *temp = node->left;
                if (temp != nullptr)
                    temp->parent = node->parent;
                delete node;
                return temp;
            }

            // Case 3: Node has two children
            // Find the predecessor (or could use successor)
            BSTNode *pred = findMaxHelper(node->left);

            // Replace node's key with predecessor's key
            node->key = pred->key;

            // Delete the predecessor (which has at most one child)
            node->left = deleteHelper(node->left, pred->key);
        }
        return node;
    }

public:
    void inOrderTraversal()
    {
        cout << "In-order traversal: ";
        inOrderHelper(root);
        cout << endl;
    }

private:
    void inOrderHelper(BSTNode *node)
    {
        if (node != nullptr)
        {
            inOrderHelper(node->left);  // Visit left subtree
            cout << node->key << " ";   // Process current node
            inOrderHelper(node->right); // Visit right subtree
        }
    }

public:
    bool isEmpty()
    {
        return root == nullptr;
    }

    int getHeight()
    {
        return getHeightHelper(root);
    }

private:
    int getHeightHelper(BSTNode *node)
    {
        if (node == nullptr)
            return -1;

        int leftHeight = getHeightHelper(node->left);
        int rightHeight = getHeightHelper(node->right);

        return 1 + max(leftHeight, rightHeight);
    }

public:
    ~BinarySearchTree()
    {
        destroyTree(root);
    }

private:
    void destroyTree(BSTNode *node)
    {
        if (node != nullptr)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};
int main()
{
    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    bst.inOrderTraversal();

    BSTNode *found = bst.search(40);
    if (found != nullptr)
    {
        cout << "Found: " << found->key << endl;
    }

    BSTNode *minNode = bst.findMin();
    BSTNode *maxNode = bst.findMax();
    cout << "Min: " << minNode->key << ", Max: " << maxNode->key << endl;

    BSTNode *pred = bst.predecessor(50);
    if (pred != nullptr)
    {
        cout << "Predecessor of 50: " << pred->key << endl;
    }
    BSTNode *succ = bst.successor(50);
    if (pred != nullptr)
    {
        cout << "Successor of 50: " << succ->key << endl;
    }

    bst.deleteKey(30);
    bst.inOrderTraversal();

    cout << "Tree height: " << bst.getHeight() << endl;

    return 0;
}
