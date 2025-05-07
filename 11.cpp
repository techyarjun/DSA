#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student {
    int rollNo;
    string name;
    string division;
    string address;

public:
    void getData() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore(); // To ignore the newline character left in input buffer
        getline(cin, name);
        cout << "Enter Division: ";
        getline(cin, division);
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void displayData() {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nDivision: " << division;
        cout << "\nAddress: " << address << endl;
    }

    int getRollNo() {
        return rollNo;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app); // Open file in append mode
    if (!file) {
        cout << "File could not be opened!" << endl;
        return;
    }
    s.getData();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student record added successfully.\n";
}

void displayStudent(int rollNo) {
    Student s;
    ifstream file("students.txt");
    if (!file) {
        cout << "File could not be opened!" << endl;
        return;
    }
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollNo) {
            cout << "Student record found:\n";
            s.displayData();
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Student record not found.\n";
}

void deleteStudent(int rollNo) {
    Student s;
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollNo) {
            found = true;
            cout << "Student record deleted successfully.\n";
        }
        else {
            temp.write((char*)&s, sizeof(s));
        }
    }
    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (!found)
        cout << "Student record not found.\n";
}

int main() {
    int choice, rollNo;
    do {
        cout << "\n----- Student Information System -----\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            cout << "Enter Roll No to display: ";
            cin >> rollNo;
            displayStudent(rollNo);
            break;
        case 3:
            cout << "Enter Roll No to delete: ";
            cin >> rollNo;
            deleteStudent(rollNo);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
