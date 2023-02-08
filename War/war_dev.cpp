
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
