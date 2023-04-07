
/*
    name: Anna
    date: April 23
    title: Phone Book
    desc: Phone book program with add, remove, edit, search, display functions PLUS
    + class usage
    + alphabetical sorting
*/

#include <iostream> //i/o
#include <string.h> //cstrings
#include <string>   //strings

using namespace std; //less typing

struct person{
    char name[20];    //-> name
    char number[11];  //-> phone number
    char address[30]; //-> address
    char city[20];    //-> city
    char pc[7];       //-> postal code
    bool exists;      //-> whether person exists or not 
    void display(){   //print own contact
        /*The following lines print each field with formatting */
        cout<<"Name: "<<name<<"\n";
        cout<<"#: ("<<number[0]<<number[1]<<number[2]<<")"<<number[3]<<number[4]<<number[5]<<"-"<<number[6]<<number[7]<<number[8]<<number[9]<<"\n";
        cout<<"Address: "<<address<<"\n";
        cout<<"City: "<<city<<"\n";
        cout<<"Postal Code: "<<char(toupper(pc[0]))<<pc[1]<<char(toupper(pc[2]))<<" "<<pc[3]<<char(toupper(pc[4]))<<pc[5]<<"\n";
    }
    void clear(int pos); //function to clear contents (declare)
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

    /* THE FOLLOWING LINES PRINT ASCII ART */
    cout<<" __   __             __   __               ___                   \n";
    cout<<" \\ \\ / /__ _  _ _ _  \\ \\ / /__ _ _ _  _   / _ \\__ __ ___ _       \n";
    cout<<"  \\ V / _ \\ || | '_|  \\ V / -_) '_| || | | (_) \\ V  V / ' \\ \n";
    cout<<"   |_|\\___/\\_,_|_|     \\_/\\___|_|  \\_, |  \\___/ \\_/\\_/|_||_|     \n";
    cout<<"           ___ _                 _ |__/         _                \n";
    cout<<"          | _ \\ |_  ___ _ _  ___| |__  ___  ___| |__             \n";
    cout<<"          |  _/ ' \\/ _ \\ ' \\/ -_) '  \\/ _ \\/ _ \\ / /          \n";
    cout<<"          |_| |_||_\\___/_||_\\___|_.__/\\___/\\___/_\\_\\             \n";
                                                            
    while(true){
        int menu_option;

        cout<<"----------------------------------------------------------------\n";
        cout<<"[0] - Add Contact\n";
        cout<<"[1] - Remove Contact\n";
        cout<<"[2] - Edit Contact\n";
        cout<<"[3] - Search Contact\n";
        cout<<"[4] - Display All Contacts\n";
        cout<<"[5] - CLOSE PHONEBOOK\n";
        cout<<"> ";

        cin>>menu_option;

        while(menu_option < 0 || menu_option > 5){
            cout<<"  -> Bad input try again: ";
            cin>>menu_option;
        }

        cout<<"----------------------------------------------------------------\n";

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

void add_contact(){ //adds a person 

    int existing_people = 0;   //will store total amount of existing people
    person new_person;         //makes instance of struct

    //TEMP PEOPLE USED AS STRING INPUTS:
    string temp_name; //name
    string temp_num;  //phone
    string temp_add;  //address
    bool found_space = false; //for address error check
    string temp_city; //city
    string temp_pc;   //postal code 
    bool good_input = true; //for error checks

    for(int i = 0; i<5; ++i){  //for each person
        if(people[i].exists)   //if they exist
            ++existing_people; //add to counter
    }

    if(existing_people == 5){ //you cant add anyone if full
        cout<<"No more space for another contact. 5 is max.\n"; //output
        return; //get out 
    }

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    cout<<"-> Enter name: "; //ask
    cin.ignore(); //ignore ws
    getline(cin, temp_name); //get
    while(1){
        good_input = true;
        for(int i = 0; i<temp_name.length(); ++i){
            if(!isalpha(temp_name.at(i)) && temp_name.at(i) != ' '){
                good_input = false;
                cout<<"  -> Bad input. Try again: "; 
                getline(cin, temp_name);
                break;
            }
        }
        if(good_input){
            break;
        }
    }
    strncpy(new_person.name, temp_name.c_str(), 20); //truncate if too long
    new_person.name[19] = '\0'; //null

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    cout<<"-> Enter phone number (NO SPACES, NO FORMATTING, NOTHING - JUST THE NUMBERS): "; //ask
    getline(cin, temp_num); //get
    while(1){
        good_input = true;
        if(temp_num.length() != 10){
            good_input = false;
        }else if(!(isdigit(temp_num.at(0)) && isdigit(temp_num.at(1)) && isdigit(temp_num.at(2)) && isdigit(temp_num.at(3)) && isdigit(temp_num.at(4)) && isdigit(temp_num.at(5)) && isdigit(temp_num.at(6)) && isdigit(temp_num.at(7)) && isdigit(temp_num.at(8)) && isdigit(temp_num.at(9)))){
            good_input = false;
        }
        if(!good_input){
            cout<<"  -> Bad input. Try again: ";
            getline(cin, temp_num);
        }else{
            break;
        }
    }
    strcpy(new_person.number, temp_num.c_str()); //make cstr
    new_person.number[10] = '\0'; //null

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    cout<<"-> Enter address: "; //ask
    getline(cin, temp_add); //get
    while(1){ //while bad input
        good_input = true; //assume for now 
        found_space = false; //between numbers and streetname
        for(int i = 0; i<temp_add.length(); ++i){ //for each char
            if(temp_add.at(i) == ' '){ //if space then letters should follow
                found_space = true; //ok
            }
            if(!found_space){ //has to be digit
                if(!isdigit(temp_add.at(i))){ //if bad
                    good_input = false; //not good
                    break; //get out of char check loop
                }
            }else{ //has to be alpha or a space
                if(!isalpha(temp_add.at(i)) && temp_add.at(i) != ' '){ //check
                    good_input = false; //not good
                    break; //get out of char check loop
                }
            }
            good_input = true; //ok
        }
        if(!good_input ||  !found_space){ //has to be good input AND not only just numbers
            cout<<"  -> Bad input. Try again: ";
            getline(cin, temp_add);
        }else{
            break;
        }
    }
    strncpy(new_person.address, temp_add.c_str(), 30); //trunc if too long
    new_person.address[29] = '\0'; //null char

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    cout<<"-> Enter city: "; //ask
    getline(cin, temp_city); //get
    while(1){
        good_input = true; //for now 
        for(int i = 0; i<temp_city.length(); ++i){
            if(!isalpha(temp_city.at(i)) && temp_city.at(i) != ' '){
                good_input = false;
                cout<<"  -> Bad input. Try again: ";
                getline(cin, temp_city);
                break;
            }
        }
        if(good_input){
            break;
        }
    }
    strncpy(new_person.city, temp_city.c_str(), 20); //truncate if too long
    new_person.city[19] = '\0'; //null

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    cout<<"-> Enter postal code (NO SPACES, NO FORMATTING, NOTHING): "; //ask
    getline(cin, temp_pc); //get
    while(1){
        good_input = true;
        if(temp_pc.length() != 6){ //check size
            good_input = false;
        }else if(!(isalpha(temp_pc.at(0)) && isdigit(temp_pc.at(1)) && isalpha(temp_pc.at(2)) && isdigit(temp_pc.at(3)) && isalpha(temp_pc.at(4)) && isdigit(temp_pc.at(5)))){ //check 
            good_input = false;
        }
        if(good_input){
            break;
        }else{
            cout<<"  -> Bad input. Try again: ";
            getline(cin, temp_pc);
        }
    }
    strcpy(new_person.pc, temp_pc.c_str()); //add
    new_person.pc[6] = '\0'; //null

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    new_person.exists = 1; //make person finally exist
    people[existing_people] = new_person; //put into golbal array
    
    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    cout<<"SUCCESSFULLY ADDED\n"; //yay
}

void remove_contact(){ //remove a person

    int removal_index; //will store who to remove
    int existing_people = 0; //will store total amount of existing people
    
    for(int i = 0; i<5; ++i){ //display all contacts
        if(people[i].exists){ //if they exist
            cout<<"["<<i<<"] - "<<people[i].name<<"\n"; //cout
            ++existing_people; //self explanatory
        }
    }

    if(existing_people == 0){ //if no people, you cant remove anyone
        cout<<"There are no people. You can't remove anyone.\n"; //cout
        return; //get out 
    }

    cout<<"Select the index of the person to remove: "; //ask
    cin>>removal_index; //get
    while(removal_index < 0 || removal_index > 5 || !people[removal_index].exists){ //err check
        cout<<"Bad input. Try again: "; //err msg
        cin>>removal_index; //tryr again
    }

    for(int i = removal_index; i<5; ++i){ //move the empty pos to the end and shift everything up
        if(i == 4){ //if the last make it empty
            people[4].clear(4); //call member func
        }else{ //otherwise shift everything up
            people[i] = people[i+1]; //self explanatory
        }
    }

    cout<<"SUCCESSFULLY REMOVED\n"; //output
}

void edit_contact(){

    int edit_index;          //will store who to remove
    int edit_choice;         //what will they edit, name address, etc. 
    int existing_people = 0; //will store total amount of existing people

    //TEMP PEOPLE USED AS STRING INPUTS:
    string temp_name; //name
    string temp_num;  //phone
    string temp_add;  //address
    bool found_space = false; //for address error check
    string temp_city; //city
    string temp_pc;   //postal code 
    bool good_input = true; //for error checks

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

        cout<<"What do you want to edit?\n"; //ask
        cout<<"[0] - Name\n[1] - Number\n[2] - Address\n[3] - City\n[4] - Postal Code\n"; //provide options
        cout<<"(Enter -1 to exit edit mode)\n> "; //extra
        cin>>edit_choice; //get
        while(edit_choice < -1 || edit_choice > 4){ //err check
            cout<<"  -> Bad input. Try again: "; //err msg
            cin>>edit_choice; //get again
        }
        if(edit_choice == -1){ //QUIT
            break; //ok
        }

        if(edit_choice == 0){ //NAME
            cout<<"-> Enter name: "; //ask
            cin.ignore(); //ignore ws
            getline(cin, temp_name);
            while(1){
                good_input = true;
                for(int i = 0; i<temp_name.length(); ++i){
                    if(!isalpha(temp_name.at(i)) && temp_name.at(i) != ' '){
                        good_input = false;
                        cout<<"  -> Bad input. Try again: "; 
                        getline(cin, temp_name);
                        break;
                    }
                }
                if(good_input){
                    break;
                }
            }
            strncpy(people[edit_index].name, temp_name.c_str(), 20); //truncate if too long
            people[edit_index].name[19] = '\0'; //null

        }else if(edit_choice == 1){ //NUMBER
            cout<<"-> Enter phone number (NO SPACES, NO FORMATTING, NOTHING - JUST THE NUMBERS): "; //ask
            cin.ignore(); //ignore ws
            getline(cin, temp_num); //get
            while(1){
                good_input = true;
                if(temp_num.length() != 10){
                    good_input = false;
                }else if(!(isdigit(temp_num.at(0)) && isdigit(temp_num.at(1)) && isdigit(temp_num.at(2)) && isdigit(temp_num.at(3)) && isdigit(temp_num.at(4)) && isdigit(temp_num.at(5)) && isdigit(temp_num.at(6)) && isdigit(temp_num.at(7)) && isdigit(temp_num.at(8)) && isdigit(temp_num.at(9)))){
                    good_input = false;
                }
                if(!good_input){
                    cout<<"  -> Bad input. Try again: ";
                    getline(cin, temp_num);
                }else{
                    break;
                }
            }
            strcpy(people[edit_index].number, temp_num.c_str()); //make cstr
            people[edit_index].number[10] = '\0';

        }else if(edit_choice == 2){ //ADDRESS
            cout<<"-> Enter address: "; //ask
            cin.ignore(); //ignore cin
            getline(cin, temp_add); //get
            while(1){ //while bad input
                good_input = true; //assume for now 
                found_space = false; //between numbers and streetname
                for(int i = 0; i<temp_add.length(); ++i){ //for each char
                    if(temp_add.at(i) == ' '){ //if space then letters should follow
                        found_space = true; //ok
                    }
                    if(!found_space){ //has to be digit
                        if(!isdigit(temp_add.at(i))){ //if bad
                            good_input = false; //not good
                            break; //get out of char check loop
                        }
                    }else{ //has to be alpha or a space
                        if(!isalpha(temp_add.at(i)) && temp_add.at(i) != ' '){ //check
                            good_input = false; //not good
                            break; //get out of char check loop
                        }
                    }
                    good_input = true; //ok
                }
                if(!good_input || !found_space){
                    cout<<"  -> Bad input. Try again: ";
                    getline(cin, temp_add);
                }else{
                    break;
                }
            }
            strncpy(people[edit_index].address, temp_add.c_str(), 30); //trunc if too long
            people[edit_index].address[29] = '\0'; //null 

        }else if(edit_choice == 3){ //CITY
            cout<<"-> Enter city: "; //ask
            cin.ignore(); //no ws
            getline(cin, temp_city); //get
            while(1){
                good_input = true; //for now 
                for(int i = 0; i<temp_city.length(); ++i){
                    if(!isalpha(temp_city.at(i)) && temp_city.at(i) != ' '){
                        good_input = false;
                        cout<<"  -> Bad input. Try again: ";
                        getline(cin, temp_city);
                        break;
                    }
                }
                if(good_input){
                    break;
                }
            }
            strncpy(people[edit_index].city, temp_city.c_str(), 20); //truncate if too long
            people[edit_index].city[19] = '\0'; //null

        }else if(edit_choice == 4){ //POSTAL CODE 
            cout<<"-> Enter postal code (NO SPACES, NO FORMATTING, NOTHING): "; //ask
            cin.ignore(); //ignore ws
            getline(cin, temp_pc); //get
            while(1){
                good_input = true;
                if(temp_pc.length() != 6){ //check size
                    good_input = false;
                }else if(!(isalpha(temp_pc.at(0)) && isdigit(temp_pc.at(1)) && isalpha(temp_pc.at(2)) && isdigit(temp_pc.at(3)) && isalpha(temp_pc.at(4)) && isdigit(temp_pc.at(5)))){ //check 
                    good_input = false;
                }
                if(good_input){
                    break;
                }else{
                    cout<<"  -> Bad input. Try again: ";
                    getline(cin, temp_pc);
                }
            }
            strcpy(people[edit_index].pc, temp_pc.c_str()); //add
            people[edit_index].pc[6] = '\0'; //null
        }

        cout<<"SUCCESSFULLY EDITED\n"; //yay

    }
}

void search_contact(){ //find people by name
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

void display_all(){ //display everyone
    bool people_exist = false; //whether there are people
    for (int i = 0; i < 5; i++){ //for each person
        if(people[i].exists){ //if people exist
            people_exist = true; //set to yes
            people[i].display(); //display info
            cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"; //border
        }
    }
    if(!people_exist){ //you cant display anything if people don't exist
        cout<<"Well...Nothing to display here.\n"; //output
    }
}

void name_sort(){ //sorts everyone by name
    person temp; //temporary person
    bool swapped; //for bubble sort
    for (int i = 0; i < 4; i++) { //loop through each element
        swapped = false; //for early break
        for (int j = 0; j < 4 - i; j++) { //loop through each element
            if ((strcmp(people[j].name, people[j + 1].name) > 0) && people[j].exists && people[j+1].exists){ //compare and check 
                temp = people[j]; //store person
                people[j] = people[j + 1]; //swap 1
                people[j + 1] = temp; //swap 2
                swapped = true; //set this to true
            }
        }
        if (!swapped){ //check if done
            break; //if yes stop looping
        }
    }
}