//ascii test

#include <iostream>
#include <vector>
#include "ascii_stuff.h"

#ifdef _WIN32
	bool ok = init_term();
#endif

using namespace std;

string upperscore = "\xE2\x80\xBE";
//string upperscore = {'\xE2', '\x80', '\xBE'};
//2d arrays for hands

//string test [1] = {upperscore};

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
    {" "," "," ","_"," ","_"," ","_"," "},  //0
    {" ","_","|"," ","|"," ","|"," ","|"},  //1
    {"|"," ","|"," ","|"," ","|"," ","|"},  //2
    {" ","\\"," "," "," "," "," "," ","/"}, //3
    {" "," "," "," "," "," "," "," "," "},  //4
    {" "," "," "," "," "," "," "," "," "}   //5
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
    {" ","_"," ","_"," ","_"," "," "," "},  //0
    {"|"," ","|"," ","|"," ","|","_"," "},  //1
    {"|"," ","|"," ","|"," ","|"," ","|"},  //2
    {"\\"," "," "," "," "," "," ","/"," "}, //3
    {" "," "," "," "," "," "," "," "," "},  //4
    {" "," "," "," "," "," "," "," "," "}   //5
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



int main(){
	
	cout<<upperscore<<"\n";
	for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<LEFT_nocard[i][j];
		}
		cout<<"\n";
	}
	for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<FLIPPED_LEFT_nocard[i][j];
		}
		cout<<"\n";
	}
	for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<LEFT_card[i][j];
		}
		cout<<"\n";
	}
	for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<FLIPPED_LEFT_card[i][j];
		}
		cout<<"\n";
	}for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<RIGHT_nocard[i][j];
		}
		cout<<"\n";
	}
	for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<FLIPPED_RIGHT_nocard[i][j];
		}
		cout<<"\n";
	}
	for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<RIGHT_card[i][j];
		}
		cout<<"\n";
	}
	for(int i = 0; i<6; ++i){
		for(int j = 0; j<9; ++j){
			cout<<FLIPPED_RIGHT_card[i][j];
		}
		cout<<"\n";
	}
	return 0;
}

