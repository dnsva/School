#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

struct person{
    char name[20];    //name
    char number[10];  //phone number
    char address[30]; //address
    char city[20];    //city
    char pc[7];       //postal code
    bool exists;      //whether person exists or not 
    void display(){ //print own contact
        /*The following lines print each field with formatting */
        cout<<"Name: "<<name<<"\n";
        cout<<"#: ("<<number[0]<<number[1]<<number[2]<<")"<<number[3]<<number[4]<<number[5]<<"-"<<number[6]<<number[7]<<number[8]<<number[9]<<"\n";
        cout<<"Address: "<<address<<"\n";
        cout<<"City: "<<city<<"\n";
        cout<<"Postal Code: "<<char(toupper(pc[0]))<<pc[1]<<char(toupper(pc[2]))<<" "<<pc[3]<<char(toupper(pc[4]))<<pc[5]<<"\n";
    }
    void clear(int pos); //function to clear contents 
};

person people [5]; //stores everyone 

//FUNCTIONS===============
void add_contact();     //
void remove_contact();  //
void edit_contact();    //
void search_contact();  //
void display_all();     //
void name_sort();       //
//=======================

int main(){

    cout<<"┬ ┬┌─┐┬ ┬┬─┐  ┬  ┬┌─┐┬─┐┬ ┬  ┌─┐┬ ┬┌┐┌ \n";
    cout<<"└┬┘│ ││ │├┬┘  └┐┌┘├┤ ├┬┘└┬┘  │ │││││││ \n";
    cout<<" ┴ └─┘└─┘┴└─   └┘ └─┘┴└─ ┴   └─┘└┴┘┘└┘ \n";
    cout<<"    ┌─┐┬ ┬┌─┐┌┐┌┌─┐  ┌┐ ┌─┐┌─┐┬┌─      \n";
    cout<<"    ├─┘├─┤│ ││││├┤   ├┴┐│ ││ │├┴┐      \n";
    cout<<"    ┴  ┴ ┴└─┘┘└┘└─┘  └─┘└─┘└─┘┴ ┴      \n";

    
    while(true){
        int menu_option;

        cout<<"----------------------------------\n";
        cout<<"[0] - Add Contact\n";
        cout<<"[1] - Remove Contact\n";
        cout<<"[2] - Edit Contact\n";
        cout<<"[3] - Search Contact\n";
        cout<<"[4] - Display All Contacts\n";
        cout<<"[5] - CLOSE PHONEBOOK\n";
        cout<<"> ";

        cin>>menu_option;

        while(menu_option < 0 || menu_option > 5){
            cout<<"Bad input try again:\n> ";
            cin>>menu_option;
        }

        cout<<"----------------------------------\n";

        if(menu_option == 0){
            add_contact();
        }else if(menu_option == 1){
            remove_contact();
        }else if(menu_option == 2){
            edit_contact();
        }else if(menu_option == 3){
            search_contact();
        }else if(menu_option == 4){
            display_all();
        }else{
            break; //exit
        }

        name_sort();
    }

    cout<<"BYE!\n";
    return 0;

}

void person::clear(int pos){ //clear all contents of object
    memset(&people[pos], 0, sizeof(person)); //set everything to 0 bytes 
}

void add_contact(){

    int existing_people = 0;   //will store total amount of existing people
    person new_person;         //makes instance of struct

    for(int i = 0; i<5; ++i){  //for each person
        if(people[i].exists)   //if they exist
            ++existing_people; //add to counter
    }

    if(existing_people == 5){ //you cant add anyone if full
        cout<<"No more space for another contact. 5 is max.\n"; //output
        return; //get out 
    }

    cout<<"-> Enter name: ";
    string temp_name;
    cin.ignore();
    getline(cin, temp_name);
    strncpy(new_person.name, temp_name.c_str(), 20); //truncate if too long
    new_person.name[19] = '\0';
    //cout<<"NAME IS "<<temp_name<<"\n";

    cout<<"-> Enter phone number (NO SPACES, NO FORMATTING, NOTHING - JUST THE NUMBERS): ";
    string temp_num;
    //cin.ignore();
    getline(cin, temp_num);

    //cout<<"length recieved is "<<temp_num.length()<<"\n";
   // cout<<"temp num is "<<temp_num<<"\n";

    while(temp_num.length() != 10){ //check for correct size
        
        cout<<"  -> Bad input. Try again: ";
        //cin.ignore();
        getline(cin, temp_num);
        
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

        cout<<"TEMP NUM IS "<<temp_num<<"\n";

        cout<<"  -> Only numbers allowed. Try again: ";

        //cin.ignore();
        getline(cin, temp_num);
    }
    strcpy(new_person.number, temp_num.c_str());

    cout<<"-> Enter address: ";
    string temp_add;
    getline(cin, temp_add);
    while(temp_add.length() > 30){
        cout<<"  -> Adress is way too long. Try again: ";
        getline(cin, temp_add);
    }
    bool good_case = false; //for this error check
    while(!good_case){
        bool found_space = false; //between numbers and streetname
        for(int i = 0; i<temp_add.length(); ++i){

            if(temp_add.at(i) == ' '){
                found_space = true;
            }
            if(!found_space){ //has to be digit
                if(!isdigit(temp_add.at(i))){
                    good_case = false;
                    break;
                }
            }else{ //has to be alpha or a space
                if(!(isalpha(temp_add.at(i)) || temp_add.at(i) == ' ')){
                    good_case = false;
                    break;
                }
            }

            good_case = true;

        }

        if(!good_case){
            cout<<"  -> Bad format. Try again: ";
            getline(cin, temp_add);
        }
    }
    strcpy(new_person.address, temp_add.c_str());

    cout<<"-> Enter city: ";
    string temp_city;
    getline(cin, temp_city);
    strncpy(new_person.city, temp_city.c_str(), 20); //truncate if too long
    new_person.city[19] = '\0';

    //strcpy(new_person.city, temp_city.c_str());

    cout<<"-> Enter postal code (NO SPACES, NO FORMATTING, NOTHING): ";
    string temp_pc;
    getline(cin, temp_pc);
   
    while(temp_pc.length() > 6){
        cout<<"  -> Postal code is in wrong format. Try again: ";
        getline(cin, temp_pc);
    }
    while(!(isalpha(temp_pc.at(0)) && isdigit(temp_pc.at(1)) && isalpha(temp_pc.at(2)) && isdigit(temp_pc.at(3)) && isalpha(temp_pc.at(4)) && isdigit(temp_pc.at(5)))){
        cout<<"  -> Has to be letter, number, letter, etc. Try again: ";
        getline(cin, temp_pc);
    }
    strcpy(new_person.pc, temp_pc.c_str());

    new_person.exists = 1;

    people[existing_people] = new_person;
    
    cout<<"SUCCESSFULLY ADDED\n";
}

void remove_contact(){

    int removal_index; //will store who to remove

    int existing_people = 0; //will store total amount of existing people

    //when contact removed, slide all the ones to the right of it over

    //display all contacts
    for(int i = 0; i<5; ++i){
        if(people[i].exists){
            cout<<"["<<i<<"] - "<<people[i].name<<"\n";
            ++existing_people;
        }
    }

    if(existing_people == 0){ //if no people, you cant remove anyone
        cout<<"There are no people. You can't remove anyone.\n";
        return; //get out 
    }
    //cout<<"\n";
    cout<<"Select the index of the person to remove: ";
    cin>>removal_index;
    while(removal_index < 0 || removal_index > 5 || !people[removal_index].exists){
        cout<<"Bad input. Try again: ";
        cin>>removal_index;
    }

    for(int i = removal_index; i<5; ++i){ //move the empty pos to the end and shift everything up
        if(i == 4){ //if the last make it empty
            people[4].clear(4);
        }else{ //otherwise shift everything up
            people[i] = people[i+1];
        }
    }

    cout<<"SUCCESSFULLY REMOVED\n";
}

void edit_contact(){
    int edit_index;          //will store who to remove
    int edit_choice;         //what will they edit, name address, etc. 
    int existing_people = 0; //will store total amount of existing people

    for(int i = 0; i<5; ++i){ //display all contacts
        if(people[i].exists){ //if they exist
            cout<<"["<<i<<"] - "<<people[i].name<<"\n"; //print
            ++existing_people; //add
        }
    }

    if(existing_people == 0){ //if no people, you cant remove anyone
        cout<<"There are no people. You can't edit anything.\n"; //message
        return; //get out 
    }

    cout<<"Select the index of the person to edit: "; //ask
    cin>>edit_index; //get
    while(edit_index < 0 || edit_index > 5 || !people[edit_index].exists){ //err check
        cout<<"  -> Bad input. Try again: "; //err msg
        cin>>edit_index; //get
    }

    while(true){
        cout<<"What do you want to edit?\n";
        cout<<"[0] - Name\n[1] - Number\n[2] - Address\n[3] - City\n[4] - Postal Code\n";
        cout<<"(Enter -1 to exit edit mode)\n> ";
        cin>>edit_choice;
        while(edit_choice < -1 || edit_choice > 4){
            cout<<"  -> Bad input. Try again\n> ";
            cin>>edit_choice;
        }

        if(edit_choice == -1){ //QUIT
            break;
        }

        if(edit_choice == 0){ //NAME
            cout<<"-> Enter name: ";
            string temp_name;
            cin.ignore();
            getline(cin, temp_name);
            while(temp_name.length() > 20){
                cout<<"  -> Name is way too long. Try again: ";
                getline(cin, temp_name);
            }
            //strcpy(people[edit_index].name, temp_name.c_str());

            for(int i=0;i<strlen(people[edit_index].name);i++){
                people[edit_index].name[i]=temp_name.at(i);
            }
            people[edit_index].name[19] = '\0';

        }else if(edit_choice == 1){ //NUMBER

            cout<<"-> Enter phone number (NO SPACES, NO FORMATTING, NOTHING - JUST THE NUMBERS): ";
            string temp_num;
            cin.ignore();
            getline(cin, temp_num);
            while(temp_num.length() != 10){ //check for correct size
                cout<<"  -> Bad input. Try again: ";
                getline(cin, temp_num);
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
            
            }

            for(int i=0;i<strlen(people[edit_index].number);i++){
                people[edit_index].number[i]=temp_num.at(i);
                if(i  == strlen(people[edit_index].number - 1)){
                    people[edit_index].number[i] = '\0';
                }
            }

           // strcpy(people[edit_index].number, temp_num.c_str());

        }else if(edit_choice == 2){ //ADDRESS

            cout<<"-> Enter address: ";
            string temp_add;
            cin.ignore();
            getline(cin, temp_add);
    
            while(temp_add.length() > 30){
                cout<<"  -> Adress is way too long. Try again: ";
                getline(cin, temp_add);
            
            }
            bool good_case = false; //for this error check
            while(!good_case){
                bool found_space = false; //between numbers and streetname
                for(int i = 0; i<temp_add.length(); ++i){

                    if(temp_add.at(i) == ' '){
                        found_space = true;
                    }
                    if(!found_space){ //has to be digit
                        if(!isdigit(temp_add.at(i))){
                            good_case = false;
                            break;
                        }
                    }else{ //has to be alpha or a space
                        if(!(isalpha(temp_add.at(i)) || temp_add.at(i) == ' ')){
                            good_case = false;
                            break;
                        }
                    }

                    good_case = true;

                }

                if(!good_case){
                    cout<<"  -> Bad format. Try again: ";
                    getline(cin, temp_add);
                
                }
            }
            strcpy(people[edit_index].address, temp_add.c_str());     

            for(int i=0;i<strlen(people[edit_index].address);i++){
                people[edit_index].address[i]=temp_add.at(i);
                if(i  == strlen(people[edit_index].address - 1)){
                    people[edit_index].address[i] = '\0';
                }
            }


        }else if(edit_choice == 3){ //CITY

            cout<<"-> Enter city: ";
            string temp_city;
            cin.ignore();
            getline(cin, temp_city);
            while(temp_city.length() > 20){
                cout<<"  -> City name is way too long. Try again: ";
                getline(cin, temp_city);
            }
            //strcpy(people[edit_index].city, temp_city.c_str());

            for(int i=0;i<strlen(people[edit_index].city);i++){
                people[edit_index].city[i]=temp_city.at(i);
                if(i  == strlen(people[edit_index].city - 1)){
                    people[edit_index].city[i] = '\0';
                }
            }

        }else if(edit_choice == 4){ //POSTAL CODE 

            cout<<people[edit_index].exists<<"<- exists.\n";

            cout<<"-> Enter postal code (NO SPACES, NO FORMATTING, NOTHING): ";
            string temp_pc;
            cin.ignore();
            getline(cin, temp_pc);
            
            cout<<people[edit_index].exists<<"<- exists.\n";

            while(temp_pc.length() > 6){
                cout<<"  -> Postal code is in wrong format. Try again: ";
                getline(cin, temp_pc);
                
            }

            cout<<people[edit_index].exists<<"<- exists.\n";

            while(!(isalpha(temp_pc.at(0)) && isdigit(temp_pc.at(1)) && isalpha(temp_pc.at(2)) && isdigit(temp_pc.at(3)) && isalpha(temp_pc.at(4)) && isdigit(temp_pc.at(5)))){
                cout<<"  -> Has to be letter, number, letter, etc. Try again: ";
                getline(cin, temp_pc);
            }

            cout<<people[edit_index].exists<<"<- exists.\n";

            for(int i=0;i<strlen(people[edit_index].pc);i++){
                people[edit_index].pc[i]=temp_pc.at(i);
            }
            people[edit_index].pc[6]='\0';
            //strcpy(people[edit_index].pc, temp_pc.c_str());

            cout<<people[edit_index].exists<<"<- exists.\n";

        }

        cout<<"SUCCESSFULLY EDITED\n";

    }
}



void search_contact(){
    string search_name;             //name 2 search 4
    bool found = false;             //if name found 
    bool at_least_1_person = false; //if one person exists in array

    cout << "-> Enter name to search for: "; //ask
    cin.ignore();                            //ignore whitespace
    getline(cin, search_name);               //get name 

    for (int i = 0; i < 5; i++){ //for each person
        found = true; //for now 
        for(int j = 0; j<strlen(people[i].name); ++j){ //for each character
            at_least_1_person = true; //self explanatory
            if(j >= search_name.length()){ //so as to not go out of bounds
                found = false; //if it was found by now we wouldnt be here 
                break; //get out of character check loop
            }
            if(tolower(people[i].name[j]) != tolower(search_name.at(j))){ //make case not matter
              found = false; //if its not the same then not found
              break;         //get out of this loop
            }
        }
        if(found && at_least_1_person){ //if found
            cout<<"Person found:\n"; //show
            people[i].display(); //show
            break; //get out of people loop since found 
        }
    }
    if (!found || !at_least_1_person) { //if person never found
        cout<<"  -> PERSON NOT FOUND!\n"; //output
    }
}

void display_all(){
    bool people_exist = false; //whether there are people
    for (int i = 0; i < 5; i++){ //for each person
        if(people[i].exists){ //if people exist
            people_exist = true; //set to yes
            people[i].display(); //display info
            cout<<"++++++++++++++++++++++++++++++++++\n"; //border
        }
    }
    if(!people_exist){ //you cant display anything if people don't exist
        cout<<"Well...Nothing to display here.\n"; //output
    }
}


void name_sort() {

    person temp;
    bool swapped;
    
    for (int i = 0; i < 4; i++) {
        swapped = false;
        for (int j = 0; j < 4 - i; j++) {
            if ((strcmp(people[j].name, people[j + 1].name) > 0) && people[j].exists && people[j+1].exists) {
                temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

