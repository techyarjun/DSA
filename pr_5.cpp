#include <iostream>
using namespace std;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;
    bool isThreaded; // true if right points to inorder successor

    Node(int val) {
        key = val;
        left = right = nullptr;
        isThreaded = false;
    }
};

// --- Helper: Recursive function to convert to threaded binary tree
Node* convert(Node* node, Node* prev) {
    if (node == nullptr)
        return prev;

    // Process left subtree
    prev = convert(node->left, prev);

    // If previous node exists and its right is NULL, thread it to current node
    if (prev && prev->right == nullptr) {
        prev->right = node;
        prev->isThreaded = true;
    }

    // Update previous
    prev = node;

    // Process right child
    return convert(node->right, prev);
}

// --- Main wrapper to start the threading process
Node* createThreaded(Node* root) {
    convert(root, nullptr);
    return root;
}

// --- Inorder traversal using threading
void inorder(Node* root) {
    Node* current = root;

    // Go to leftmost node
    while (current && current->left)
        current = current->left;

    while (current) {
        cout << current->key << " ";

        // If threaded, go to inorder successor
        if (current->isThreaded)
            current = current->right;
        else {
            // Else, go to the leftmost node in right subtree
            current = current->right;
            while (current && current->left)
                current = current->left;
        }
    }
}

// --- Sample Usage
int main() {
    /*
           10
          /  \
         5    15
        / \     \
       2   7     20
    */
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(2);
    root->left->right = new Node(7);
    root->right->right = new Node(20);

    // Convert to threaded binary tree
    createThreaded(root);

    // Inorder traversal
    cout << "Inorder Traversal using threaded binary tree:\n";
    inorder(root);

    return 0;
}
