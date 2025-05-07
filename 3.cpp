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
    string bookName;
    cout << "Enter book name: ";
    // getline(cin, bookName);
    cin>>bookName;

    Node* book = new Node(bookName);

    int numChapters;
    cout << "Enter number of chapters: ";
    cin >> numChapters;
    cin.ignore(); // Clear input buffer

    for (int i = 0; i < numChapters; i++) {
        string chapterName;
        cout << "\nEnter name of Chapter " << i + 1 << ": ";
        // getline(cin, chapterName);
        cin>>chapterName;
        Node* chapter = new Node(chapterName);

        int numSections;
        cout << "Enter number of sections in " << chapterName << ": ";
        cin >> numSections;
        cin.ignore();

        for (int j = 0; j < numSections; j++) {
            string sectionName;
            cout << "  Enter name of Section " << j + 1 << ": ";
            getline(cin, sectionName);
            Node* section = new Node(sectionName);

            int numSubsections;
            cout << "  Enter number of subsections in " << sectionName << ": ";
            cin >> numSubsections;
            cin.ignore();

            for (int k = 0; k < numSubsections; k++) {
                string subsectionName;
                cout << "    Enter name of Subsection " << k + 1 << ": ";
                getline(cin, subsectionName);
                Node* subsection = new Node(subsectionName);
               
                section->addChild(subsection);
            }

            chapter->addChild(section);
        }

        book->addChild(chapter);
    }

    cout << "\n\nBook Structure:\n";
    book->printTree();

    return 0;
}

