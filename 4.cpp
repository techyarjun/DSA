#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }

    Node* insert(Node* node, int val) {
        if (node == nullptr) 
        return new Node(val);
        if (val < node -> data) 
        node -> left = insert(node->left, val);
        else 
        node -> right = insert(node->right, val);
        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    // (ii) Find number of nodes in longest path
    int longestPath(Node* node) {
        if (node == nullptr) 
        return 0;
        int left = longestPath(node->left);
        int right = longestPath(node->right);
        return max(left, right) + 1;
    }

    // (iii) Minimum data value found in the tree
    int findMin(Node* node) {
        if (node == nullptr) 
        return -1;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->data;
    }

    // (iv) Swap left and right pointers at every node
    Node* mirror(Node* node) {
        if (node == nullptr) 
        return nullptr;
        Node* left = mirror(node->left);
        Node* right = mirror(node->right);
        node->left = right;
        node->right = left;
        return node;
    }

    // (v) Search a value
    bool search(Node* node, int key) {
        if (node == nullptr) 
        return false;
        if (key == node->data) 
        return true;
        if (key < node->data) 
        return search(node->left, key);
        else 
        return search(node->right, key);
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }
};

int main() {
    BST tree;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : values) {
        tree.insert(val);
    }

    // (i) Insert new node
    tree.insert(25);

    cout << "Inorder traversal: ";
    tree.inorder(tree.root);
    cout << endl;

    cout << "Longest path: " << tree.longestPath(tree.root) << endl;
    cout << "Minimum value: " << tree.findMin(tree.root) << endl;

    tree.root = tree.mirror(tree.root);
    cout << "Inorder after mirror: ";
    tree.inorder(tree.root);
    cout << endl;

    int key = 60;
    // cout << "Search " << key << ": " << (tree.search(tree.root, key) ? "Found" : "Not Found") << endl;
    bool found = tree.search(tree.root, key);
    if (found) {
        cout << "Search " << key << ": Found" << endl;
    } else {
        cout << "Search " << key << ": Not Found" << endl;
    }

    return 0;
}
