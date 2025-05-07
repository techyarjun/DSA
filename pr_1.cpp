#include <iostream>
#include <list>
using namespace std;

const int TABLE_SIZE = 10;

int hashFunction(int key) {
     return key % TABLE_SIZE; 
    }

class LinearProbing {
    int table[TABLE_SIZE];

public:
    LinearProbing() { 
        for (int i = 0; i < TABLE_SIZE; i++)
         table[i] = -1; }

    void insert(int key) {
        int index = hashFunction(key);
        while (table[index] != -1)
        index = (index + 1) % TABLE_SIZE;
        table[index] = key;
    }

    void display() {
        cout << "\nLinear Probing Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++)
        cout << i << " : " << table[i] << endl;
    }

    void search(int key) {
        int index = hashFunction(key),
        comparisons = 1;
        while (table[index] != -1 && table[index] != key) {
            index = (index + 1) % TABLE_SIZE;
            comparisons++;
        }
        if (table[index] == key)
        cout << "Found in " << comparisons << " comparisons.\n";
        else 
        cout << "Not found after " << comparisons << " comparisons.\n";
    }
};

class Chaining {
    list<int> table[TABLE_SIZE];

public:
    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    void display() {
        cout << "\nChaining Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : ";
            for (int val : table[i]) 
            cout << val << " -> ";
            cout << "NULL\n";
        }
    }

    void search(int key) {
        int index = hashFunction(key), 
        comparisons = 0;
        for (int val : table[index]) {
            comparisons++;
            if (val == key) {
                cout << "Found in " << comparisons << " comparisons.\n";
                return;
            }
        }
        cout << "Not found after " << comparisons << " comparisons.\n";
    }
};

int main() {

    LinearProbing lp;
    Chaining ch;

    int keys[] = {21, 32, 43, 54, 65, 76, 87, 98, 10};

    for (int key : keys) {
        lp.insert(key);
        ch.insert(key);
    }

    lp.display();
    ch.display();

    cout << "\nSearching for 54:\n"; lp.search(54); ch.search(54);
    cout << "\nSearching for 99:\n"; lp.search(99); ch.search(99);

    return 0;
}
