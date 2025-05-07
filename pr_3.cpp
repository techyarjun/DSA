#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    string name;
    vector<Node*> children;

    Node(string name) {
        this->name = name;
    }

    void addChild(Node* child) {
        children.push_back(child);
    }

    void printTree(int level = 0) {
        for (int i = 0; i < level; i++) 
        cout << "  ";
        cout << "- " << name << endl;
        for (Node* child : children) {
            child->printTree(level + 1);
        }
    }
};

int main() {
    Node* book = new Node("Book");

    Node* chapter1 = new Node("Chapter 1");
    Node* section1 = new Node("Section 1.1");
    Node* subsection1 = new Node("Subsection 1.1.1");
    Node* subsection2 = new Node("Subsection 1.1.2");
    section1->addChild(subsection1);
    section1->addChild(subsection2);

    Node* section2 = new Node("Section 1.2");
    chapter1->addChild(section1);
    chapter1->addChild(section2);

    Node* chapter2 = new Node("Chapter 2");
    Node* section3 = new Node("Section 2.1");
    chapter2->addChild(section3);

    book->addChild(chapter1);
    book->addChild(chapter2);

    book->printTree();

    return 0;
}
