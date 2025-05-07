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

class Dictionary {
protected:
    list<Entry> table[TABLE_SIZE];  // array of linked lists

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    virtual void insert(int key, string value) = 0;
    virtual void find(int key) = 0;
    virtual void remove(int key) = 0;
    virtual void display() = 0;
};

// Without Replacement (Simple chaining)
class WithoutReplacement : public Dictionary {
public:
    void insert(int key, string value) override {
        int index = hashFunction(key);

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

    void find(int key) override {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                cout << "Found: " << entry.value << " (key: " << key << ")\n";
                return;
            }
        }
        cout << "Key " << key << " not found.\n";
    }

    void remove(int key) override {
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

    void display() override {
        cout << "\nHash Table (Without Replacement):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "[" << i << "]: ";
            for (auto& entry : table[i]) {
                cout << "(" << entry.key << ", " << entry.value << ") -> ";
            }
            cout << "NULL\n";
        }
    }
};

// With Replacement (Simple logic: replace if collision on same index)
class WithReplacement : public Dictionary {
public:
    void insert(int key, string value) override {
        int index = hashFunction(key);

        // Check if same index has an entry that does NOT belong here
        if (!table[index].empty() && hashFunction(table[index].front().key) != index) {
            Entry displaced = table[index].front();
            table[index].pop_front(); // remove wrongly placed

            Entry newEntry = {key, value};
            table[index].push_front(newEntry);
            cout << "Replaced old entry and inserted (" << key << ", " << value << ") at index " << index << ".\n";

            // Reinsert displaced entry properly
            insert(displaced.key, displaced.value);
        } else {
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
    }

    void find(int key) override {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                cout << "Found: " << entry.value << " (key: " << key << ")\n";
                return;
            }
        }
        cout << "Key " << key << " not found.\n";
    }

    void remove(int key) override {
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

    void display() override {
        cout << "\nHash Table (With Replacement):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "[" << i << "]: ";
            for (auto& entry : table[i]) {
                cout << "(" << entry.key << ", " << entry.value << ") -> ";
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    Dictionary* dict = nullptr;
    int choice;

    cout << "Choose Hashing Method:\n";
    cout << "1. Chaining Without Replacement\n";
    cout << "2. Chaining With Replacement\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
        dict = new WithoutReplacement();
    else if (choice == 2)
        dict = new WithReplacement();
    else {
        cout << "Invalid choice. Exiting.\n";
        return 0;
    }

    int key;
    string value;
    int option;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Find\n";
        cout << "3. Delete\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Enter key (integer): ";
                cin >> key;
                cout << "Enter value (string): ";
                cin >> value;
                dict->insert(key, value);
                break;
            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                dict->find(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict->remove(key);
                break;
            case 4:
                dict->display();
                break;
            case 5:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (option != 5);

    delete dict;
    return 0;
}
'''Topic	Concept	Key Points	Example
Hash Table	A structure to store key-value pairs efficiently.	Uses hashing function to map keys to an index.	index = key % table_size
Chaining	Handle collisions by maintaining a linked list at each index.	Easy insertion, can have multiple entries at same index.	list<Entry> table[TABLE_SIZE];
With Replacement	If wrong key is at wrong index, replace it with correct one.	Displace wrong key, reinsert it properly.	table[index].pop_front(); and re-insert.
Without Replacement	Simple chaining, no moving entries.	Just add new entry at the end of list at that index.	table[index].push_back(newEntry);
Classes and Inheritance	Dictionary is abstract base class.	Child classes inherit and override insert, find, remove, display.	class WithoutReplacement : public Dictionary
Virtual Functions	Used to achieve polymorphism.	virtual void insert() = 0; // Pure virtual function	
Virtual Destructor	Ensures correct destruction of child classes.	Write virtual ~Dictionary() {}	
Dynamic Allocation	Use new to create objects dynamically.	dict = new WithoutReplacement();	
Delete Keyword	Free memory to prevent memory leaks.	delete dict;	
✨ Bonus Short Notes for Main Function

Step	Action	Code
1	Choose method (with/without replacement)	cin >> choice;
2	Create appropriate object dynamically	dict = new WithoutReplacement();
3	Menu-driven actions: Insert, Find, Delete, Display	switch(option) { case 1: ... }
4	Properly free memory	delete dict;
'''