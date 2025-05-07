#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class Employee {
public:
    int empID;
    string name, designation;
    float salary;

    void input() {
        cout << "Enter ID, Name, Designation, Salary: ";
        cin >> empID;
        cin.ignore();
        getline(cin, name);
        getline(cin, designation);
        cin >> salary;
    }

    void output() const {
        cout << "\nID: " << empID << "\nName: " << name 
             << "\nDesignation: " << designation << "\nSalary: " << salary << endl;
    }
};

void addEmployee() {
    Employee e;
    fstream f("employee.dat", ios::app | ios::binary);
    e.input();
    f.write((char*)&e, sizeof(e));
    f.close();
}

void displayEmployee(int id) {
    Employee e;
    ifstream f("employee.dat", ios::binary);
    bool found = false;
    while (f.read((char*)&e, sizeof(e))) {
        if (e.empID == id) {
            e.output();
            found = true;
            break;
        }
    }
    if (!found) cout << "Employee not found.\n";
    f.close();
}

void deleteEmployee(int id) {
    Employee e;
    ifstream fin("employee.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    bool found = false;

    while (fin.read((char*)&e, sizeof(e))) {
        if (e.empID == id) found = true;
        else fout.write((char*)&e, sizeof(e));
    }

    fin.close();
    fout.close();
    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    if (found) cout << "Employee deleted successfully.\n";
    else cout << "Employee not found.\n";
}

int main() {
    int ch, id;
    do {
        cout << "\n1. Add  2. Display  3. Delete  4. Exit\nChoice: ";
        cin >> ch;
        switch(ch) {
            case 1: addEmployee(); break;
            case 2: cout << "Enter ID: "; cin >> id; displayEmployee(id); break;
            case 3: cout << "Enter ID: "; cin >> id; deleteEmployee(id); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (ch != 4);

    return 0;
}
