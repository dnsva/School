

#include <iostream>
#include "info.h"
#include <vector>
#include "ascii_art.h"
#include <thread>
#include <chrono>
#include <string>
#include <windows.h>

using std::vector;
using std::cout;
using std::string;

bool right_handed = true; //by default, changeable in main code
vector<vector<string>> make_blank_card();
vector<vector<string>> make_card(card c);

string upperscore = "\xE2\x80\xBE";
string block = "\xE2\x96\x89";

//2d arrays for hands
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
    //{" "," "," ",upperscore,"|\033[48;5;124m",upperscore," ",upperscore,"\033[48;5;153m|"},  //3
    //{" "," "," "," ","|","\033[48;5;124m_","_","_","\033[48;5;153m|"},  //4
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
    //{" ",upperscore,"|\033[48;5;124m",upperscore," ",upperscore,"\033[48;5;153m|"," "," "},  //3
    //{" "," ","|\033[48;5;124m","_","_","_","\033[48;5;153m|"," "," "},  //4
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
    //{" "," "," "," ","|\033[48;5;124m"," "," "," ","\033[48;5;153m|"},  //1
    {" "," "," "," ","|"," "," "," ","|"},  //1
    {" "," "," ","_","|","_"," ","_","|"},
    //{" "," "," ","_","|\033[48;5;124m","_"," ","_","\033[48;5;153m|"},  //2
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
    //{"|\033[48;5;124m","_"," ","_","\033[48;5;153m|"," "," "," "," "},  //1
    {"|","_"," ","_","|","_"," "," "," "},  //2
    //{"|\033[48;5;124m","_"," ","_","\033[48;5;153m|","_"," "," "," "},  //2
    {"|"," ","|"," ","|"," ","|","_"," "},  //3
    {"|"," ","|"," ","|"," ","|"," ","|"},  //4
    {"\\"," "," "," "," "," "," ","/"," "}  //5
};

void update_screen(
    string note,
    int num_cards_P1,
    int num_cards_P2,
    bool face_up,
        //y?
        card card_played_P1,
        card card_played_P2,
        //n?
        bool hand_covering
){
	
	printf(newpage); //clear screen
	cout<<reset; //reset all colors and everything
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    //int window_width = 100; //terminal width minus some edge stuff MAKE SURE THIS IS EVEN 
    int window_width = (columns%2 == 0) ? columns-10 : columns - 11;
    int needed_width = 9*2+4+6; //hands and cards (28)
	int leftover_width = window_width/2 - needed_width/2; //for sides 
	if(leftover_width < 0) leftover_width = 0;

    //top border
    cout<<"   ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" \n";

	//top label
    cout<<" | "<<background<<deep_blue<<"THEM: ";
    for(int i = 0; i<window_width-6; ++i) cout<<" ";
    cout<<reset<<" |\n";

	//card count
    cout<<" | "<<background<<deep_blue<<"CARDS(";
    if (num_cards_P1<10) cout<<"0";
    cout<<num_cards_P1<<")";
    for(int i = 0; i<window_width-9; ++i) cout<<" ";
    cout<<reset<<" |\n";
    
    //hands and cards
    if(face_up || (!face_up && !hand_covering)){ //face up or not hand covering 
    	
        vector<vector<string>> showing_card = (face_up) ? make_card(card_played_P1) : make_blank_card(); //either face up or face down, stores ascii 
        
        for(int i = 0; i<5; ++i){
        	//-------------------------------------------------------------------
        	cout<<" | "<<background;
            for(int space = 0; space<leftover_width; ++space) cout<<" ";
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<FLIPPED_LEFT_nocard[i][j];
			}
            cout<<reset;
            //-------------------------------------------------------------------
            cout<<background<<"  ";
            //-------------------------------------------------------------------
            for(int j = 0; j<6; ++j){
            	if(i == 0 || i == 4 || j == 0 || j == 5){
            		cout<<background;
				}else{
					if(face_up){
						cout<<card_front;
					}else{
						cout<<card_back;
					}
				}
            	cout<<deep_blue<<showing_card[i][j];
			}
            cout<<reset;
            //-------------------------------------------------------------------
            cout<<background<<"  ";
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<FLIPPED_RIGHT_nocard[i][j];
			}
            cout<<reset;
            //-------------------------------------------------------------------
            cout<<background;
			for(int space = 0; space<leftover_width; ++space) cout<<" ";
            cout<<reset<<" |\n";
            //-------------------------------------------------------------------
        }
        cout<<" | "<<background;
    	for(int space = 0; space<leftover_width; ++space) cout<<" ";
        for(int j = 0; j<9; ++j) cout<<deep_blue<<FLIPPED_LEFT_nocard[5][j];
        cout<<"          ";
        for(int j = 0; j<9; ++j) cout<<deep_blue<<FLIPPED_RIGHT_nocard[5][j];
        for(int space = 0; space<leftover_width; ++space) cout<<" ";
        cout<<reset<<" |\n";
      
            

    }else if(hand_covering){ //Since this is the AI, make their dominant hand such that it is NOT mirrored to you (this looks better) 
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){
            	cout<<" | "<<background<<deep_blue;
                for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_LEFT_card[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_RIGHT_nocard[i][j];
                }
                for(int space = 0; space<leftover_width; ++space) cout<<" ";
                cout<<reset<<" |\n";
            }
        }else{ //left handed
            for(int i = 0; i<6; ++i){
            	cout<<" | "<<background<<deep_blue;
            	for(int space = 0; space<leftover_width; ++space) cout<<" ";
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_LEFT_nocard[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_RIGHT_card[i][j];
                }
                for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
				cout<<reset<<" |\n";
            }
            
        }
    }

    //space
    cout<<" | "<<background;
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<reset<<" |\n";

    //mid border
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" |\n";

	//note
    cout<<" | STATUS: ";
	
	if(note == "..."){
		cout<<note; //no bkgd
	}else{
		cout<<background2<<magenta<<note<<reset;
	}
    for(int i = 0; i<window_width - 8 - note.size(); ++i) cout<<" ";
    cout<<" |\n";

    //mid border
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" |\n";

	//label
    cout<<" | "<<background<<deep_blue<<"YOU: ";
    for(int i = 0; i<window_width-5; ++i) cout<<" ";
    cout<<reset<<" |\n";

	//card count
    cout<<" | "<<background<<deep_blue<<"CARDS(";
    if (num_cards_P2<10) cout<<"0";
    cout<<num_cards_P2<<")";
    for(int i = 0; i<window_width-9; ++i) cout<<" ";
    cout<<reset<<" |\n";
    
    //space
    cout<<" | "<<background;
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<reset<<" |\n";

    //cards and hands
    if(face_up || (!face_up && !hand_covering)){ //face up or not hand covering 
        vector<vector<string>> showing_card = (face_up) ? make_card(card_played_P2) : make_blank_card(); //either face up or face down, stores ascii 
        for(int i = 0; i<5; ++i){
        	//-------------------------------------------------------------------
        	cout<<" | "<<background;
            for(int space = 0; space<leftover_width; ++space) cout<<" ";
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<LEFT_nocard[i][j];
			}
            cout<<reset;
            //-------------------------------------------------------------------
            cout<<background<<"  ";
            //-------------------------------------------------------------------
            for(int j = 0; j<6; ++j){
            	if(i == 0 || i == 4 || j == 0 || j == 5){
            		cout<<background;
				}else{
					if(face_up){
						cout<<card_front;
					}else{
						cout<<card_back;
					}
				}
            	cout<<deep_blue<<showing_card[i][j];
			}
            cout<<reset;
            //-------------------------------------------------------------------
            cout<<background<<"  ";
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<RIGHT_nocard[i][j];
			}
            cout<<reset;
            //-------------------------------------------------------------------
            cout<<background;
			for(int space = 0; space<leftover_width; ++space) cout<<" ";
            cout<<reset<<" |\n";
            //-------------------------------------------------------------------
    	}
        
    	cout<<" | "<<background;
    	for(int space = 0; space<leftover_width; ++space) cout<<" ";
        for(int j = 0; j<9; ++j) cout<<deep_blue<<LEFT_nocard[5][j];
        cout<<"          ";
        for(int j = 0; j<9; ++j) cout<<deep_blue<<RIGHT_nocard[5][j];
        for(int space = 0; space<leftover_width; ++space) cout<<" ";
        cout<<reset<<" |\n";
      

    }else if(hand_covering){
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){
            	cout<<" | "<<background<<deep_blue;
                for(int space = 0; space<leftover_width; ++space) cout<<" ";
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_nocard[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_card[i][j];
                }
                for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
                cout<<reset<<" |\n";
            }
        }else{ //left handed
            for(int i = 0; i<6; ++i){
            	cout<<" | "<<background<<deep_blue;
            	for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_card[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_nocard[i][j];
                }
                for(int space = 0; space<leftover_width; ++space) cout<<" ";
				cout<<reset<<" |\n";
            }
            
        }
    }

	//bottom border
    cout<<"   ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" \n";
    
    //SLEEP
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
}

vector<vector<string>> make_card(card c){
    vector<vector<string>> ascii_card (5, vector<string>(6)); //[5][6]
    //------------------------------------------
    ascii_card[0] = {" ","_","_","_","_"," "};
    //------------------------------------------
    //------------> [suit][value]
    
    /*edge*/ ascii_card[1][0] = "|";
    /*edge*/ ascii_card[1][5] = "|";
    /*suit*/ ascii_card[1][1] = c.suit;
    /*____________value___________*/
    ascii_card[1][2] = " ";
    if(c.value == 10){
        ascii_card[1][3] = "1";
        ascii_card[1][4] = "0";
    }else if(c.value == 15){
        ascii_card[1][3] = "J";
        ascii_card[1][4] = "K";
    }else{
        ascii_card[1][3] = " ";
        if(c.value < 11){
            ascii_card[1][4] = std::to_string(c.value);
        }else if(c.value == 11){
            ascii_card[1][4] = "J";
        }else if(c.value == 12){
            ascii_card[1][4] = "Q";
        }else if(c.value == 13){
            ascii_card[1][4] = "K";
        }else if(c.value == 14){
            ascii_card[1][4] = "A";
        }
    }
    //------------------------------------------
    ascii_card[2] = {"|","-","-","-","-","|"};
    //------------------------------------------
    //------------> [value][suit]
    /*edge*/ ascii_card[3][0] = "|";
    /*edge*/ ascii_card[3][5] = "|";
    /*____________value___________*/
    if(c.value == 10){
        ascii_card[3][1] = "1";
        ascii_card[3][2] = "0";
    }else if(c.value == 15){
        ascii_card[3][1] = "J";
        ascii_card[3][2] = "K";
    }else{
        ascii_card[3][2] = " ";
        if(c.value < 11){
            ascii_card[3][1] = std::to_string(c.value);
        }else if(c.value == 11){
            ascii_card[3][1] = "J";
        }else if(c.value == 12){
            ascii_card[3][1] = "Q";
        }else if(c.value == 13){
            ascii_card[3][1] = "K";
        }else if(c.value == 14){
            ascii_card[3][1] = "A";
        }
    }
    ascii_card[3][3] = " ";
    /*suit*/ ascii_card[3][4] = c.suit;
    //------------------------------------------
    ascii_card[4] = {" ",upperscore,upperscore,upperscore,upperscore," "};
    //------------------------------------------
    return ascii_card;
}

vector<vector<string>> make_blank_card(){
    vector<vector<string>> ascii_card = {
        {" ","_","_","_","_"," "},
        {"|"," "," "," "," ","|"},
        {"|","-","-","-","-","|"},
        {"|"," "," "," "," ","|"},
        {" ",upperscore,upperscore,upperscore,upperscore," "}
    };
    return ascii_card;
}
