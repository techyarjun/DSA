#include<iostream>
#include<list>
using namespace std;

const int T_S = 5;

int hashfunction(int number){
    return number % T_S;
}

struct Client {
    string name;
    int number;
    bool isOccupied;

    Client() {
        name = "";
        number = -1;
        isOccupied = false;
    }
};

class linear{
    Client table[T_S];

public:
    void insert( string name, int number){
        int index = hashfunction(number);
        int startindex = index;
        while( table[index].isOccupied){
            index = (index + 1) % T_S;
            if( startindex == index){
                cout<<"List full \n";
                return;
            }
        }
        table[index].number = number;
        table[index].name = name;
        table[index].isOccupied = true;
    }

    void display(){
        cout<<"\n\nDisplay linear : "<<endl;
        for(int i = 0; i < T_S; i++){
            cout<< i << " : ";
            if(table[i].isOccupied){
                cout<< table[i].name <<" -> "<< table[i].number <<endl;
            }
            else{
                cout<<" Empty !\n";
            }
        }
    }

    void search(string name, int number){
        int index = hashfunction(number);
        int startindex = index;
        while (table[index].isOccupied) {
            if (table[index].name == name && table[index].number == number) {
                cout << "Found at index " << index << ": " << name << " -> " << number << "\n";
                return;
            }
            index = (index + 1) % T_S;
            if (index == startindex)
                break;
        }
        cout << "Entry not found.\n";
    }    

    void remove(string name, int number){
        int index = hashfunction(number);
        int startindex = index;
        while(table[index].isOccupied) {
            if(table[index].number == number && table[index].name == name) {
                table[index].isOccupied = false;
                table[index].name = "";
                table[index].number = -1;
                cout << "Number " << number << " belonging to " << name << " is deleted.\n";
                return;
            }
            index = (index + 1) % T_S;
            if(index == startindex)
                break;
        }
        cout << "Entry not in the list\n";
    }
};

class Chaining {
    list<Client> table[T_S];

public:
    void insert(string name, int number) {
        int index = hashfunction(number);
        Client newClient;
        newClient.name = name;
        newClient.number = number;
        newClient.isOccupied = true;
        table[index].push_back(newClient);
        cout << "Inserted " << name << " -> " << number << " in chain at index " << index << "\n";
    }

    void display() {
        cout << "\nDisplay Chaining:\n";
        for (int i = 0; i < T_S; i++) {
            cout << i << " : ";
            for (const auto& client : table[i]) {
                cout << "[" << client.name << " -> " << client.number << "] ";
            }
            if (table[i].empty()) 
            cout << "Empty";
            cout << endl;
        }
    }

    void remove(string name, int number) {
        int index = hashfunction(number);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->name == name && it->number == number) {
                table[index].erase(it);
                cout << "Deleted " << name << " -> " << number << " from index " << index << endl;
                return;
            }
        }
        cout << "Entry not found for deletion.\n";
    }
    
    void search(string name, int number) {
        int index = hashfunction(number);
        for (const auto& client : table[index]) {
            if (client.name == name && client.number == number) {
                cout << "Found at index " << index << ": " << name << " -> " << number << "\n";
                return;
            }
        }
        cout << "Entry not found.\n";
    }
    

};

int main(){
    linear lp;
    Chaining ch;

    int choice, type, number;
    string name;

    do{
        cout<<"1. Insert\n";
        cout<<"2. Display\n";
        cout<<"3. Search\n";
        cout<<"4. Delete\n";
        cout<<"5. Exit\n ";
        cout<<"Enter choice :";
        cin>>choice;

        cout<<"\nType : \n";
        cout<< "1. linear \n" ;
        cout<< "2. Chaining \n" ;
        cout<< "Enter type : ";
        cin>>type;

        switch(choice){
            case 1:
                if(type == 1){
                    cout << "\nEnter Name: ";
                    cin >> name;
                    cout<<"Enter number : ";
                    cin>>number;
                    lp.insert(name, number);
                    cout<<"Inserted !\n.\n.\n";
                }
                else if(type == 2){
                    cout << "\nEnter Name: ";
                    cin >> name;
                    cout<<"Enter number : ";
                    cin>>number;
                    ch.insert(name, number);
                }
        
                else{
                    cout<< "Not Available !\n.\n.\n";
                }
                break;

            case 2:
                if(type == 1){
                    lp.display();
                    cout<<"\n   .\n   .   \n\n";
                }
                else if( type == 2 ){
                    ch.display();
                }
                break;

            case 3:
                if(type == 1){
                    cout << "\nEnter name to search: ";
                    cin >> name;
                    cout << "Enter number to search: ";
                    cin >> number;
                    lp.search(name, number);
                }
                else if(type == 2){
                    ch.search(name , number);
                }
                break;

            case 4:
                if(type == 1){
                    cout<<"\nEnter name to delete :";
                    cin>>name;
                    cout<<"number to delete :";
                    cin>>number;
                    lp.remove(name, number);
                }
                else if(type == 2){
                    ch.remove(name, number);
                }
                break;             
        }       
    }while(choice != 5);
    cout << "\nProgram exited.\n";
    return 0;
}