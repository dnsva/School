
//Stuff to add

#include <iostream>
#include <windows.h>

#include "ascii_stuff.h"

using namespace std;

#ifdef _WIN32
	bool ok = init_term();
#endif

void show_rules(){
	cout<<"Look at your browser...\n";
	ShellExecute(NULL, "open", "https://bicyclecards.com/how-to-play/war",NULL, NULL, SW_SHOWNORMAL);
	
}

bool quit(){ //true - yes, quit, false - no, continue 
	char confirm_quit;
	cout<<"Are you sure (y/n)? ";
	cin>>confirm_quit;
	while(confirm_quit != 'y' && confirm_quit != 'n'){
		cout<<"Bad input, try again (y/n): ";
		cin>>confirm_quit;
	}
	if(confirm_quit == 'y'){
		return true;
	}else{
		return false;
	}
	
}

void play(){
	//already implemented
}

int main(){
	
	bool done = false;
	int choice = -1;
	while(!done){
		cout<<"\x1b[5m";
		cout<<"(0) - Play\n";
		cout<<"(1) - See rules\n";
		cout<<"(2) - Quit\n";
		cout<<"Enter choice: ";
		cin>>choice;
		while(choice < 0 || choice > 2){
			cout<<"Bad input. Try again: ";
			cin>>choice;
		}
		if(choice == 0){
			play();
		}else if(choice == 1){
			show_rules();
		}else{
			done = quit();
		}
	}
}



vector<vector<string>> FLIPPED_RIGHT_nocard = { //[6][9]
    //0   1   2   3   4   5   6   7   8
    {" ","/"," "," "," "," "," "," ","\\"}, //0
    {"|"," ","|"," ","|"," ","|"," ","|"},  //1
    {" ",upperscore,"|"," ","|"," ","|"," ","|"},  //2
    {" "," "," ",upperscore," ",upperscore," ",upperscore," "},  //3
    {" "," "," "," "," "," "," "," "," "},  //4
    {" "," "," "," "," "," "," "," "," "}   //5
};
vector<vector<string>> FLIPPED_RIGHT_card  = {
    //0   1   2   3   4   5   6   7   8
    {" ","/"," "," "," "," "," "," ","\\"}, //0
    {"|"," ","|"," ","|"," ","|"," ","|"},  //1
    {" ",upperscore,"|"," ","|"," ","|"," ","|"},  //2
    {" "," "," ",upperscore,"|",upperscore," ",upperscore,"|"},  //3
    {" "," "," "," ","|","_","_","_","|"},  //4
    {" "," "," "," "," "," "," "," "," "}   //5
};
vector<vector<string>> FLIPPED_LEFT_nocard  = {
    //0   1   2   3   4   5   6   7   8
    {"/"," "," "," "," "," "," ","\\"," "}, //0
    {"|"," ","|"," ","|"," ","|"," ","|"},  //1
    {"|"," ","|"," ","|"," ","|",upperscore," "},  //2
    {" ",upperscore," ",upperscore," ",upperscore," "," "," "},  //3
    {" "," "," "," "," "," "," "," "," "},  //4
    {" "," "," "," "," "," "," "," "," "}   //5
};
vector<vector<string>> FLIPPED_LEFT_card   = {
    //0   1   2   3   4   5   6   7   8
    {"/"," "," "," "," "," "," ","\\"," "}, //0
    {"|"," ","|"," ","|"," ","|"," ","|"},  //1
    {"|"," ","|"," ","|"," ","|",upperscore," "},  //2
    {" ",upperscore,"|",upperscore," ",upperscore,"|"," "," "},  //3
    {" "," ","|","_","_","_","|"," "," "},  //4
    {" "," "," "," "," "," "," "," "," "}   //5
};
vector<vector<string>>RIGHT_nocard = {
    //0   1   2   3   4   5   6   7   8
    {" "," "," "," "," "," "," "," "," "},  //4
    {" "," "," "," "," "," "," "," "," "},   //5
    {" "," "," ","_"," ","_"," ","_"," "},  //0
    {" ","_","|"," ","|"," ","|"," ","|"},  //1
    {"|"," ","|"," ","|"," ","|"," ","|"},  //2
    {" ","\\"," "," "," "," "," "," ","/"} //3
    
};
vector<vector<string>> RIGHT_card  = {
    //0   1   2   3   4   5   6   7   8
    {" "," "," "," "," ","_","_","_"," "},  //0
    {" "," "," "," ","|"," "," "," ","|"},  //1
    {" "," "," ","_","|","_"," ","_","|"},  //2
    {" ","_","|"," ","|"," ","|"," ","|"},  //3
    {"|"," ","|"," ","|"," ","|"," ","|"},  //4
    {" ","\\"," "," "," "," "," "," ","/"}  //5
};
vector<vector<string>> LEFT_nocard   = {
    //0   1   2   3   4   5   6   7   8
    {" "," "," "," "," "," "," "," "," "},  //4
    {" "," "," "," "," "," "," "," "," "},   //5
    {" ","_"," ","_"," ","_"," "," "," "},  //0
    {"|"," ","|"," ","|"," ","|","_"," "},  //1
    {"|"," ","|"," ","|"," ","|"," ","|"},  //2
    {"\\"," "," "," "," "," "," ","/"," "} //3
    
};
vector<vector<string>> LEFT_card  = {
    //0   1   2   3   4   5   6   7   8
    {" ","_","_","_"," "," "," "," "," "},  //0
    {"|","_"," ","_","|"," "," "," "," "},  //1
    {"|","_"," ","_","|","_"," "," "," "},  //2
    {"|"," ","|"," ","|"," ","|","_"," "},  //3
    {"|"," ","|"," ","|"," ","|"," ","|"},  //4
    {"\\"," "," "," "," "," "," ","/"," "}  //5
};