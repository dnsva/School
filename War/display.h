
//----------------------------------------------------------------------------
#include <iostream>    //input output
#include <vector>      //instead of arrays
#include <thread>      //for sleep (osx & win)
#include <chrono>      //for sleep (osx & win)
#include <string>      //for strings
#include <windows.h>   //for getting terminal width 

#include "info.h"      //for classes
#include "ascii_art.h" //for colors and art
//----------------------------------------------------------------------------
using std::vector;     //less typing
using std::cout;       //lt
using std::string;     //lt
//----------------------------------------------------------------------------

//The following declares global variables that will be used 

bool right_handed = true; //dominant hand, set to right by default
vector<vector<string>> make_blank_card(); // function to make blank card
vector<vector<string>> make_card(card c); // fucntion to make face-up card

string upperscore = "\xE2\x80\xBE"; //symbol
string background = "\033[48;5;153m"; //background COLOR (ANSI)

//----------------------------------------------------------------------------
/*
THE FOLLOWING HUGE BLOCKS OF CODE CONTAIN THE ASCI ART OF HANDS. COLLAPSE THE
CODE FROM THE SIDES OF EDITOR. SIZES OF ALL VECTORS ARE [6][9]
*/
vector<vector<string>> FLIPPED_RIGHT_nocard = {
    {" ","/"," "," "," "," "," "," ","\\"},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {" ",upperscore,"|"," ","|"," ","|"," ","|"},
    {" "," "," ",upperscore," ",upperscore," ",upperscore," "},
    {" "," "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "," "}
};
vector<vector<string>> FLIPPED_RIGHT_card  = {
    {" ","/"," "," "," "," "," "," ","\\"},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {" ",upperscore,"|"," ","|"," ","|"," ","|"},
    {" "," "," ",upperscore,"|",upperscore," ",upperscore,"|"},
    {" "," "," "," ","|","_","_","_","|"},
    {" "," "," "," "," "," "," "," "," "}
};
vector<vector<string>> FLIPPED_LEFT_nocard  = {
    {"/"," "," "," "," "," "," ","\\"," "},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {"|"," ","|"," ","|"," ","|",upperscore," "},
    {" ",upperscore," ",upperscore," ",upperscore," "," "," "},
    {" "," "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "," "}
};
vector<vector<string>> FLIPPED_LEFT_card   = {
    {"/"," "," "," "," "," "," ","\\"," "},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {"|"," ","|"," ","|"," ","|",upperscore," "},
    {" ",upperscore,"|",upperscore," ",upperscore,"|"," "," "},
    {" "," ","|","_","_","_","|"," "," "},
    {" "," "," "," "," "," "," "," "," "}
};
vector<vector<string>>RIGHT_nocard = {
    {" "," "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "," "},
    {" "," "," ","_"," ","_"," ","_"," "},
    {" ","_","|"," ","|"," ","|"," ","|"},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {" ","\\"," "," "," "," "," "," ","/"}
};
vector<vector<string>> RIGHT_card  = {
    {" "," "," "," "," ","_","_","_"," "},
    {" "," "," "," ","|"," "," "," ","|"},
    {" "," "," ","_","|","_"," ","_","|"},
    {" ","_","|"," ","|"," ","|"," ","|"},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {" ","\\"," "," "," "," "," "," ","/"}
};
vector<vector<string>> LEFT_nocard   = {
    {" "," "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "," "},
    {" ","_"," ","_"," ","_"," "," "," "},
    {"|"," ","|"," ","|"," ","|","_"," "},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {"\\"," "," "," "," "," "," ","/"," "}
};
vector<vector<string>> LEFT_card  = {
    {" ","_","_","_"," "," "," "," "," "},
    {"|","_"," ","_","|"," "," "," "," "},
    {"|","_"," ","_","|","_"," "," "," "},
    {"|"," ","|"," ","|"," ","|","_"," "},
    {"|"," ","|"," ","|"," ","|"," ","|"},
    {"\\"," "," "," "," "," "," ","/"," "}
};

//----------------------------------------------------------------------------

void update_screen( //MAIN FUNCTION TO UPDATE SCREEN AND DRAW ASCII
    string note,             //THE MESSAGE TO DISPLAY
    int num_cards_P1,        //HOW MANY CARDS P1 HAS CURRENTLY
    int num_cards_P2,        //SAME FOR P2
    bool face_up,            //ARE THE CARDS FACE UP?
        card card_played_P1, //CARD OF P1 (ONLY IF FACE UP)
        card card_played_P2, //CARD OF P2 (ONLY IF FACE UP)
        bool hand_covering   //IS A HAND COVERING THE CARD? (IF NOT UP)
){
	
	//----------------------------------------------------------------------------
	
	//VARIABLE DECLARATIONS
	vector<vector<string>> showing_card; //the card to output if needed
	int columns; //needed for getting ter width 
	int window_width; //full width of terminal
	int needed_width; //width that will need to be used
	int leftover_width; //remaining width for sides
	
	//----------------------------------------------------------------------------
	
	/* The following code gets the length of the terminal */
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    
    //----------------------------------------------------------------------------
    
    window_width = (columns%2 == 0) ? columns-10 : columns - 11; //Make sure it is even (makes life easier) 
    needed_width = 9*2+4+6; //this is the sum of hands and cards (28)
	leftover_width = window_width/2 - needed_width/2; //for sides 
	if(leftover_width < 0) leftover_width = 0; //make sure leftover width isnt negative 
	
	//----------------------------------------------------------------------------
	
	printf(newpage); //clear screen
	cout<<reset;     //reset all colors and everything
	
	//----------------------------------------------------------------------------
	
	if(note == "AI TAKES CARDS"){ //if cards won
		background = "\033[48;5;39m"; //change bkg to a deeper blue
	}
	
	//............................................................................
	
    //top border
    cout<<"   ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" \n";

	//............................................................................
	
	//top label
    cout<<" | "<<background<<deep_blue<<"THEM: ";
    for(int i = 0; i<window_width-6; ++i) cout<<" ";
    cout<<reset<<" |\n";
	
	//............................................................................
	
	//card count
    cout<<" | "<<background<<deep_blue<<"CARDS(";
    if (num_cards_P1<10) cout<<"0";
    cout<<num_cards_P1<<")";
    for(int i = 0; i<window_width-9; ++i) cout<<" ";
    cout<<reset<<" |\n";
    
    //............................................................................
    
    //hands and cards
    if(face_up || (!face_up && !hand_covering)){ //face up or not hand covering 
    	
        showing_card = (face_up) ? make_card(card_played_P1) : make_blank_card(); //either face up or face down, stores ascii 
        
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

	//............................................................................
	
    //space
    cout<<" | "<<background;
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<reset<<" |\n";

	//............................................................................
	
	background = "\033[48;5;153m"; //change back to blue 
	
	//............................................................................
	
    //mid border
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" |\n";
    
    //............................................................................
    
	//note
    cout<<" | STATUS: ";
	if(note == "..."){
		cout<<note; //no bkgd
	}else{
		cout<<background2<<magenta<<note<<reset;
	}
    for(int i = 0; i<window_width - 8 - note.size(); ++i) cout<<" ";
    cout<<" |\n";
    
    //............................................................................
    
    //mid border
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" |\n";
	
	//............................................................................
	
	if(note == "PLAYER TAKES CARDS"){ //if cards won
		background = "\033[48;5;39m"; //change bkgrd to deeper blue
	}
	
	//............................................................................
	
	//label
    cout<<" | "<<background<<deep_blue<<"YOU: ";
    for(int i = 0; i<window_width-5; ++i) cout<<" ";
    cout<<reset<<" |\n";

	//............................................................................
	
	//card count
    cout<<" | "<<background<<deep_blue<<"CARDS(";
    if (num_cards_P2<10) cout<<"0";
    cout<<num_cards_P2<<")";
    for(int i = 0; i<window_width-9; ++i) cout<<" ";
    cout<<reset<<" |\n";
    
    //............................................................................
    
    //space
    cout<<" | "<<background;
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<reset<<" |\n";
    
    //............................................................................

    //cards and hands
    if(face_up || (!face_up && !hand_covering)){ //face up or not hand covering 
        showing_card = (face_up) ? make_card(card_played_P2) : make_blank_card(); //either face up or face down, stores ascii 
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

	//............................................................................
	
	//bottom border
    cout<<"   ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" \n";
    
    //............................................................................
    
	background = "\033[48;5;153m"; //change back to blue 
	
	//----------------------------------------------------------------------------
	
    //SLEEP
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    
    //----------------------------------------------------------------------------
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
