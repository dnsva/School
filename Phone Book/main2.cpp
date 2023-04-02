
#include <iostream>
#include <string.h>

using namespace std;

struct person {
    char name[50];
    char address[50];
    char phone[15];
    char city[30];
    char postal_code[7];



    char name[]; //max 20 chars
    char number[]; //max 10 chars
    char address[]; //max 30 chars
    char city[]; //max 20 chars
    char pc[]; //max 6 chars

    
};

person people[5];

// Function prototypes
void display_menu();
void add_person();
void remove_person();
void edit_person();
void display_people();

// Main function
int main() {

    cout<<"Hello??";
    
    char choice;

    do {
        display_menu();
        cin >> choice;

        switch(choice) {
            case '1':
                add_person();
                break;
            case '2':
                remove_person();
                break;
            case '3':
                edit_person();
                break;
            case '4':
                display_people();
                break;
            case '5':
                cout<<"Goodbye!"<< endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != '5');

    return 0;
}

// Display menu function
void display_menu() {
    cout << "Phone Book" << endl;
    cout << "1. Add Person" << endl;
    cout << "2. Remove Person" << endl;
    cout << "3. Edit Person" << endl;
    cout << "4. Display People" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter your choice: ";
}

// Add person function
void add_person() {
    for (int i = 0; i < 5; i++) {
        if (strlen(people[i].name) == 0) {
            cout << "Enter name: ";
            cin.ignore();
            cin.getline(people[i].name, 50);
            cout << "Enter address: ";
            cin.getline(people[i].address, 50);
            cout << "Enter phone number: ";
            cin.getline(people[i].phone, 15);
            cout << "Enter city: ";
            cin.getline(people[i].city, 30);
            cout << "Enter postal code: ";
            cin.getline(people[i].postal_code, 7);
            cout << "Person added." << endl;
            return;
        }
    }
    cout << "Phone book is full. Cannot add more people." << endl;
}

// Remove person function
void remove_person() {
    char name[50];
    cout << "Enter name of person to remove: ";
    cin.ignore();
    cin.getline(name, 50);

    for (int i = 0; i < 5; i++) {
        if (strcmp(people[i].name, name) == 0) {
            memset(&people[i], 0, sizeof(person));
            cout << "Person removed." << endl;
            return;
        }
    }
    cout << "Person not found." << endl;
}

// Edit person function
void edit_person() {
    char name[50];
    cout << "Enter name of person to edit: ";
    cin.ignore();
    cin.getline(name, 50);

    for (int i = 0; i < 5; i++) {
        if (strcmp(people[i].name, name) == 0) {
            cout << "Enter new name (leave blank to keep existing name): ";
            cin.getline(people[i].name, 50);
            cout << "Enter new address (leave blank to keep existing address): ";
            cin.getline( people[i].address, 50);
            cout << "Enter new phone number (leave blank to keep existing phone number): ";
            cin.getline(people[i].phone, 15);
            cout << "Enter new city (leave blank to keep existing city): ";
            cin.getline(people[i].city, 30);
            cout << "Enter new postal code (leave blank to keep existing postal code): ";
            cin.getline(people[i].postal_code, 7);
            cout << "Person updated." << endl;
            return;
        }
    }
}
cout << "Person not found." << endl;

}

// Display people function
void display_people() {
for (int i = 0; i < 5; i++) {
if (strlen(people[i].name) > 0) {
cout << "Name: " << people[i].name << endl;
cout << "Address: " << people[i].address << endl;
cout << "Phone Number: " << people[i].phone << endl;
cout << "City: " << people[i].city << endl;
cout << "Postal Code: " << people[i].postal_code << endl;
cout << endl;
}
}
}