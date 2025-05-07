#include<iostream>
#include<queue>
using namespace std;

class Node {
public:
    string data;
    string means;
    Node* left;
    Node* right;
    int height, bf;

    Node(string data, string means) : data(data), means(means), left(nullptr), right(nullptr), height(1), bf(0) {}
};

class AVL {
private:
    Node* root;

    int height(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    void updateHeightAndBF(Node* node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->height = 1 + max(leftHeight, rightHeight);
        node->bf = leftHeight - rightHeight;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeightAndBF(y);
        updateHeightAndBF(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeightAndBF(x);
        updateHeightAndBF(y);

        return y;
    }

    Node* insert(Node* node, string data, string means) {
        if (node == nullptr)
            return new Node(data, means);
        if (data < node->data)
            node->left = insert(node->left, data, means);
        else if (data > node->data)
            node->right = insert(node->right, data, means);
        else
            return node; // Duplicate not allowed

        updateHeightAndBF(node);

        // Balancing
        if (node->bf > 1) {
            if (data < node->left->data) // Left-Left
                return rotateRight(node);
            else { // Left-Right
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        if (node->bf < -1) {
            if (data > node->right->data) // Right-Right
                return rotateLeft(node);
            else { // Right-Left
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, string key) {
        if (node == nullptr)
            return node;

        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // Node with one or no child
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->means = temp->means;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr)
            return node;

        updateHeightAndBF(node);

        // Balancing
        if (node->bf > 1) {
            if (node->left->bf >= 0)
                return rotateRight(node);
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        if (node->bf < -1) {
            if (node->right->bf <= 0)
                return rotateLeft(node);
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << ": " << node->means << endl;
        inorder(node->right);
    }

    void revorder(Node* node) {
        if (node == nullptr) return;
        revorder(node->right);
        cout << node->data << ": " << node->means << endl;
        revorder(node->left);
    }

    Node* search(Node* node, string key) {
        while (node != nullptr) {
            if (key == node->data)
                return node;
            else if (key < node->data)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

public:
    AVL() : root(nullptr) {}

    void insert(string data, string means) {
        root = insert(root, data, means);
    }

    void deleteKeyword(string key) {
        root = deleteNode(root, key);
    }

    void inorder() {
        cout << "\nIn ascending order:\n";
        inorder(root);
    }

    void revorder() {
        cout << "\nIn descending order:\n";
        revorder(root);
    }

    void search(string key) {
        Node* result = search(root, key);
        if (result != nullptr)
            cout << "Found: " << result->data << ": " << result->means << endl;
        else
            cout << "Key not found.\n";
    }

    void updateMeaning(string key) {
        Node* node = search(root, key);
        if (node != nullptr) {
            cout << "Enter new meaning for " << key << ": ";
            cin >> node->means;
            cout << "Meaning updated.\n";
        } else {
            cout << "Key not found.\n";
        }
    }

    void levelOrder() {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                Node* current = q.front();
                q.pop();
                cout << current->data << ": " << current->means << "  ";
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            cout << endl;
        }
    }
};

int main() {
    AVL dictionary;
    int choice;
    string word, meaning, key;
    do {
        cout << "\nMenu:\n1. Insert\n2. Ascending Order\n3. Descending Order\n4. Search\n5. Update Meaning\n6. Level Order\n7. Delete Keyword\n8. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin >> meaning;
                dictionary.insert(word, meaning);
                break;
            case 2:
                dictionary.inorder();
                break;
            case 3:
                dictionary.revorder();
                break;
            case 4:
                cout << "Enter word to search: ";
                cin >> key;
                dictionary.search(key);
                break;
            case 5:
                cout << "Enter word to update: ";
                cin >> key;
                dictionary.updateMeaning(key);
                break;
            case 6:
                dictionary.levelOrder();
                break;
            case 7:
                cout << "Enter word to delete: ";
                cin >> key;
                dictionary.deleteKeyword(key);
                cout << "Keyword deleted (if present).\n";
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
