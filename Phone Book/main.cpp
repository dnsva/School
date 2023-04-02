#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

struct person;
person people [5];

struct person{
    char name[]; //max 20 chars
    char number[]; //max 10 chars
    char address[]; //max 30 chars
    char city[]; //max 20 chars
    char pc[]; //max 6 chars
    

    bool exists = false;


    void display(){ //print own contact

        cout<<left<<setw(21)<<name;

        cout<<left<<setw(14)<<"("<<number[0]<<number[1]<<number[2]<<")"<<number[3]<<number[4]<<number[5]<<"-"<<number[6]<<number[7]<<number[8]<<number[9];

        cout<<left<<setw(31)<<address;

        cout<<left<<setw(16)<<city;

        cout<<left<<setw(8)<<pc[0]<<pc[1]<<pc[2]<<" "<<pc[3]<<pc[4]<<pc[5]<<"\n";
        
    }

    void clear(int pos){ //clear all contents

        memset(&people[pos], 0, sizeof(Person));

        /*for(int i = 0; i<strlen(name); ++i){
            name[i] = '\0';
        }

        for(int i = 0; i<strlen(number); ++i){
            number[i] = '\0';
        }

        for(int i = 0; i<strlen(address); ++i){
            address[i] = '\0';
        }

        for(int i = 0; i<strlen(city); ++i){
            city[i] = '\0';
        }

        for(int i = 0; i<strlen(pc); ++i){
            pc[i] = '\0';
        }*/

    }

}



//FUNCTIONS

void display_all();

void add_contact();

void remove_contact();

void edit_contact();

//=

int main(){

}

//=

void display_all(){

    cout<<left<<setw(5)<<"Index"
    <<setw(21)<<"Name"
    <<setw(14)<<"Phone"
    <<setw(31)<<"Address"
    <<setw(16)<<"City"
    <<setw(8)<<"Postal Code\n";

    for (int i = 0; i < 5; i++){
        if(people[i].exists){
            cout<<left<<setw(5)<<nth_person;
            people[i].display();
        }


    }
}

void add_contact(){

    int existing_people = 0; //will store total amount of existing people
    person new_person;
    

    for(int i = 0; i<5; ++i){
        if(person[i].exists){
            ++existing_people;
        }
    }

    if(existing_people == 5){ //you cant add anyone if 5
        cout<<"No more space for another contact. 5 is max.\n";
        return; //get out 
    }


    cout<<"-> Enter name: ";
    string temp_name;
    getline(cin, temp_name);
    cin>>ws;
    strncpy(new_person.name, temp_name.c_str(), 20); //truncate if too long
    new_person.name[20] = '\0';


    cout<<"-> Enter phone number (NO SPACES, NO FORMATTING, NOTHING - JUST THE NUMBERS): ";
    string temp_num;
    getline(cin, temp_num);
    cin>>ws;
    while(temp_num.length() > 10){ //check for correct size
        cout<<"  -> Bad input. Try again: ";
        getline(cin, temp_num);
        cin>>ws;
    }
    while(!(isdigit(temp_num.at(0)) &&
        isdigit(temp_num.at(1)) &&
        isdigit(temp_num.at(2)) &&
        isdigit(temp_num.at(3)) &&
        isdigit(temp_num.at(4)) &&
        isdigit(temp_num.at(5)) &&
        isdigit(temp_num.at(6)) &&
        isdigit(temp_num.at(7)) &&
        isdigit(temp_num.at(8)) &&
        isdigit(temp_num.at(9)))){
        cout<<"  -> Only numbers allowed. Try again: ";
        getline(cin, temp_num);
        cin>>ws;
    }
    strcpy(new_person.number, temp_num.c_str());

    cout<<"-> Enter address: ";
    string temp_add;
    getline(cin, temp_add);
    cin>>ws;
    while(temp_name.length() > 30){
        cout<<"  -> Adress is way too long. Try again: ";
        getline(cin, temp_add);
        cin>>ws;
    }
    bool good_case = false; //for this error check
    while(!good_case){
        bool found_space = false; //between numbers and streetname
        for(int i = 0; i<temp_name.length(); ++i){

            if(temp_name.at(i) == ' '){
                found_space = true;
            }
            if(!found_space){ //has to be digit
                if(!isdigit(temp_name.at(i))){
                    good_case = false;
                    break;
                }
            }else{ //has to be alpha or a space
                if(!(isalpha(temp_name.at(i)) || temp_name.at(i) == ' ')){
                    good_case = false;
                    break;
                }
            }

            good_case = true;

        }

        if(!good_case){
            cout<<"  -> Bad format. Try again: ";
            getline(cin, temp_add);
            cin>>ws;
        }
    }
    strcpy(new_person.address, temp_add.c_str());

    cout<<"-> Enter city: ";
    string temp_city;
    cin>>temp_city;
    strncpy(new_person.city, temp_city.c_str(), 20); //truncate if too long
    new_person.city[20] = '\0';

    strcpy(new_person.city, temp_city.c_str());

    cout<<"-> Enter postal code (NO SPACES, NO FORMATTING, NOTHING): ";
    string temp_pc;
    getline(cin, temp_pc);
    cin>>ws;
    while(temp_pc.length() > 6){
        cout<<"  -> Postal code is in wrong format. Try again: ";
        getline(cin, temp_pc);
        cin>>ws;
    }
    while(!(isalpha(temp_pc.at(0)) && isdigit(temp_pc.at(1)) && isalpha(temp_pc.at(2)) && isdigit(temp_pc.at(3)) && isalpha(temp_pc.at(4)) && isdigit(temp_pc.at(5)))){
        cout<<"  -> Has to be letter, number, letter, etc. Try again: ";
        getline(cin, temp_pc);
        cin>>ws;
    }
    strcpy(new_person.pc, temp_pc.c_str());

    new_person.exists = 1;

    person[existing_people] = new_person;
    
}

void remove_contact(){

    int removal_index; //will store who to remove

    int existing_people = 0; //will store total amount of existing people

    //when contact removed, slide all the ones to the right of it over

    //display all contacts
    for(int i = 0; i<5; ++i){
        if(person[i].exists){
            cout<<"["<<i<<"] - "<<person[i].name;
            ++existing_people;
        }
    }

    if(existing_people == 0){ //if no people, you cant remove anyone
        cout<<"There are no people. You can't remove anyone.\n";
        return; //get out 
    }

    cout<<"Select the index of the person to remove: ";
    cin>>removal_index;
    while(removal_index < 0 || removal_index > 5 || !person[removal_index].exists){
        cout<<"Bad input. Try again: ";
        cin>>removal_index;
    }

    for(int i = removal_index; i<5; ++i){ //move the empty pos to the end and shift everything up
        if(i == 4){ //if the last make it empty
            person[4].clear(4);
        }else{ //otherwise shift everything up
            person[i] = person[i+1];
        }
    }
}

void edit_contact(){
    int edit_index; //will store who to remove
    int edit_choice; //what will they edit, name address, etc. 

    int existing_people = 0; //will store total amount of existing people

    //display all contacts
    for(int i = 0; i<5; ++i){
        if(person[i].exists){
            cout<<"["<<i<<"] - "<<person[i].name;
            ++existing_people;
        }
    }

    if(existing_people == 0){ //if no people, you cant remove anyone
        cout<<"There are no people. You can't edit anything.\n";
        return; //get out 
    }

    cout<<"Select the index of the person to edit: ";
    cin>>edit_index;
    while(edit_index < 0 || edit_index > 5 || !person[edit_index].exists){
        cout<<"Bad input. Try again: ";
        cin>>edit_index;
    }

    cout<<"What do you want to edit?\n";
    cout<<"[0] - Name\n[1] - Number\n[2] - Address\n[3] - City\n[4] - Postal Code\n";
    cout<<"(Enter -1 to exit edit mode)\n> "
    cin>>edit_choice;
    while(choice < -1 || choice > 5){
        cout<<"Bad input. Try again\n> ";
        cin>>edit_choice;
    }

    if(edit_choice == -1){ //QUIT
        return;
    }

    if(edit_choice == 0){ //NAME
        cout<<"-> Enter name: ";
        string temp_name;
        getline(cin, temp_name);
        cin>>ws;
        while(temp_name.length() > 20){
            cout<<"  -> Name is way too long. Try again: ";
            getline(cin, temp_name);
            cin>>ws;
        }
        strcpy(person[edit_index].name, temp_name.c_str());

    }else if(edit_choice == 1){ //NUMBER

        cout<<"-> Enter phone number (NO SPACES, NO FORMATTING, NOTHING - JUST THE NUMBERS): ";
        string temp_num;
        getline(cin, temp_num);
        cin>>ws;
        while(temp_num.length() > 10){ //check for correct size
            cout<<"  -> Bad input. Try again: ";
            getline(cin, temp_num);
            cin>>ws;
        }
        while(!(isdigit(temp_num.at(0)) &&
            isdigit(temp_num.at(1)) &&
            isdigit(temp_num.at(2)) &&
            isdigit(temp_num.at(3)) &&
            isdigit(temp_num.at(4)) &&
            isdigit(temp_num.at(5)) &&
            isdigit(temp_num.at(6)) &&
            isdigit(temp_num.at(7)) &&
            isdigit(temp_num.at(8)) &&
            isdigit(temp_num.at(9)))){
            cout<<"  -> Only numbers allowed. Try again: ";
            getline(cin, temp_num);
            cin>>ws;
        }
        strcpy(person[edit_index].number, temp_num.c_str());

    }else if(edit_choice == 2){ //ADDRESS

        cout<<"-> Enter address: ";
        string temp_add;
        getline(cin, temp_add);
        cin>>ws;
        while(temp_name.length() > 30){
            cout<<"  -> Adress is way too long. Try again: ";
            getline(cin, temp_add);
            cin>>ws;
        }
        bool good_case = false; //for this error check
        while(!good_case){
            bool found_space = false; //between numbers and streetname
            for(int i = 0; i<temp_name.length(); ++i){

                if(temp_name.at(i) == ' '){
                    found_space = true;
                }
                if(!found_space){ //has to be digit
                    if(!isdigit(temp_name.at(i))){
                        good_case = false;
                        break;
                    }
                }else{ //has to be alpha or a space
                    if(!(isalpha(temp_name.at(i)) || temp_name.at(i) == ' ')){
                        good_case = false;
                        break;
                    }
                }

                good_case = true;

            }

            if(!good_case){
                cout<<"  -> Bad format. Try again: ";
                getline(cin, temp_add);
                cin>>ws;
            }
        }
        strcpy(people[edit_index].address, temp_add.c_str());           

    }else if(edit_choice == 3){ //CITY

        cout<<"-> Enter city: ";
        string temp_city;
        cin>>temp_city;
        while(temp_city.length() > 20){
            cout<<"  -> City name is way too long. Try again: ";
            cin>>temp_city;
        }
        strcpy(people[edit_index].city, temp_city.c_str());

    }else if(edit_choice == 4){ //POSTAL CODE 
        cout<<"-> Enter postal code (NO SPACES, NO FORMATTING, NOTHING): ";
        string temp_pc;
        getline(cin, temp_pc);
        cin>>ws;
        while(temp_pc.length() > 6){
            cout<<"  -> Postal code is in wrong format. Try again: ";
            getline(cin, temp_pc);
            cin>>ws;
        }
        while(!(isalpha(temp_pc.at(0)) && isdigit(temp_pc.at(1)) && isalpha(temp_pc.at(2)) && isdigit(temp_pc.at(3)) && isalpha(temp_pc.at(4)) && isdigit(temp_pc.at(5)))){
            cout<<"  -> Has to be letter, number, letter, etc. Try again: ";
            getline(cin, temp_pc);
            cin>>ws;
        }
        strcpy(people[edit_index].pc, temp_pc.c_str());
    }

}