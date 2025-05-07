#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

// Key-Value pair structure
struct Entry {
    int key;
    string value;
};

// Hash Table with Chaining
class Dictionary {
    list<Entry> table[TABLE_SIZE];  // array of linked lists

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Insert key-value pair
    void insert(int key, string value) {
        int index = hashFunction(key);

        // Check if key already exists
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                cout << "Key already exists. Updating value.\n";
                entry.value = value;
                return;
            }
        }

        Entry newEntry = {key, value};
        table[index].push_back(newEntry);
        cout << "Inserted (" << key << ", " << value << ") at index " << index << ".\n";
    }

    // Find value by key
    void find(int key) {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                cout << "Found: " << entry.value << " (key: " << key << ")\n";
                return;
            }
        }
        cout << "Key " << key << " not found.\n";
    }

    // Delete key-value pair
    void remove(int key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                cout << "Deleted key " << key << ".\n";
                return;
            }
        }
        cout << "Key " << key << " not found.\n";
    }

    // Display the table
    void display() {
        cout << "\nHash Table Contents:\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "[" << i << "]: ";
            for (auto& entry : table[i]) {
                cout << "(" << entry.key << ", " << entry.value << ") -> ";
            }
            cout << "NULL\n";
        }
    }
};

// Main function to test dictionary
int main() {
    Dictionary dict;

    dict.insert(10, "Alice");
    dict.insert(20, "Bob");
    dict.insert(30, "Charlie");
    dict.insert(21, "David"); // causes collision with key 10 if TABLE_SIZE = 10

    dict.display();

    dict.find(20);
    dict.find(99);

    dict.remove(30);
    dict.remove(99);

    dict.display();

    return 0;
}
