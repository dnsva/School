
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
    cout<<"   "; //output
    for(int i = 0; i<window_width; ++i) cout<<"-"; //border itself
    cout<<" \n"; //end 

	//............................................................................
	
	//top label
    cout<<" | "<<background<<deep_blue<<"THEM: "; //label itself
    for(int i = 0; i<window_width-6; ++i) cout<<" "; //remaining space
    cout<<reset<<" |\n"; //end 
	
	//............................................................................
	
	//card count
    cout<<" | "<<background<<deep_blue<<"CARDS("; //label
    if (num_cards_P1<10) cout<<"0"; //if less than 10 add a 0 first
    cout<<num_cards_P1<<")"; //print number
    for(int i = 0; i<window_width-9; ++i) cout<<" "; //leftover space
    cout<<reset<<" |\n"; //end 
    
    //............................................................................
    
    //hands and cards
    if(face_up || (!face_up && !hand_covering)){ //face up or not hand covering 
    	
        showing_card = (face_up) ? make_card(card_played_P1) : make_blank_card(); //either face up or face down, stores ascii 
        
        for(int i = 0; i<5; ++i){ //for each row 
        	//-------------------------------------------------------------------
        	cout<<" | "<<background; //start
            for(int space = 0; space<leftover_width; ++space) cout<<" "; //space left
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<FLIPPED_LEFT_nocard[i][j]; //hand
			}
            cout<<reset; //no color 
            //-------------------------------------------------------------------
            cout<<background<<"  "; //space between card
            //-------------------------------------------------------------------
            for(int j = 0; j<6; ++j){ //for each column 
            	if(i == 0 || i == 4 || j == 0 || j == 5){ //if not the card
            		cout<<background; //keep normal color
				}else{ //if card, change color
					if(face_up){ //if card is face up
						cout<<card_front; //make color the face up one 
					}else{ //if face down 
						cout<<card_back; //make color the face down one 
					}
				}
            	cout<<deep_blue<<showing_card[i][j]; //output ascii
			}
            cout<<reset; //no more color 
            //-------------------------------------------------------------------
            cout<<background<<"  "; //space
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<FLIPPED_RIGHT_nocard[i][j]; //output ascii 
			}
            cout<<reset; //reset color 
            //-------------------------------------------------------------------
            cout<<background; //set background color 
			for(int space = 0; space<leftover_width; ++space) cout<<" "; //space output
            cout<<reset<<" |\n"; //end output 
            //-------------------------------------------------------------------
        }
        cout<<" | "<<background; //start output 
    	for(int space = 0; space<leftover_width; ++space) cout<<" "; //space
        for(int j = 0; j<9; ++j) cout<<deep_blue<<FLIPPED_LEFT_nocard[5][j]; //finish hand ascii
        cout<<"          "; //space between hands 
        for(int j = 0; j<9; ++j) cout<<deep_blue<<FLIPPED_RIGHT_nocard[5][j]; //finish hand ascii
        for(int space = 0; space<leftover_width; ++space) cout<<" "; //space
        cout<<reset<<" |\n"; //end output     

    }else if(hand_covering){ //Since this is the AI, make their dominant hand such that it is NOT mirrored to you (this looks better) 
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){ //loop through rows
            	cout<<" | "<<background<<deep_blue; //start output 
                for(int space = 0; space<leftover_width+8; ++space) cout<<" "; //add spaces left
                for(int j = 0; j<9; ++j){ //for each column
                    cout<<FLIPPED_LEFT_card[i][j]; //output ascii
                }
                cout<<"  "; //add space in between
                for(int j = 0; j<9; ++j){ //for each column
                    cout<<FLIPPED_RIGHT_nocard[i][j]; //output column
                }
                for(int space = 0; space<leftover_width; ++space) cout<<" "; //output left over space right 
                cout<<reset<<" |\n"; //output end 
            }
        }else{ //left handed
            for(int i = 0; i<6; ++i){ //loop through rows 
            	cout<<" | "<<background<<deep_blue; //start output
            	for(int space = 0; space<leftover_width; ++space) cout<<" "; //add spaces left
                for(int j = 0; j<9; ++j){ //for each col
                    cout<<FLIPPED_LEFT_nocard[i][j]; //output hand 
                }
                cout<<"  "; //output space
                for(int j = 0; j<9; ++j){ //for each col
                    cout<<FLIPPED_RIGHT_card[i][j]; //output hand ascii
                }
                for(int space = 0; space<leftover_width+8; ++space) cout<<" "; //add spaces right 
				cout<<reset<<" |\n"; //end output 
            }
            
        }
    }

	//............................................................................
	
    //space
    cout<<" | "<<background; //start output 
    for(int i = 0; i<window_width; ++i) cout<<" "; //space 
    cout<<reset<<" |\n"; //enbd output 

	//............................................................................
	
	background = "\033[48;5;153m"; //change back to blue bkg
	
	//............................................................................
	
    //mid border
    cout<<" | "; //output start
    for(int i = 0; i<window_width; ++i) cout<<"-"; //space
    cout<<" |\n"; //output end
    
    //............................................................................
    
	//note
    cout<<" | STATUS: "; //output label
	if(note == "..."){ //if the message is ...
		cout<<note; //no bkgd color 
	}else{ //otherwise 
		cout<<background2<<magenta<<note<<reset; //add color
	}
    for(int i = 0; i<window_width - 8 - note.size(); ++i) cout<<" "; //add left over space 
    cout<<" |\n"; //end output 
    
    //............................................................................
    
    //mid border
    cout<<" | "; //start output
    for(int i = 0; i<window_width; ++i) cout<<"-"; //border
    cout<<" |\n"; //end output 
	
	//............................................................................
	
	if(note == "PLAYER TAKES CARDS"){ //if cards won
		background = "\033[48;5;39m"; //change bkgrd to deeper blue
	}
	
	//............................................................................
	
	//label
    cout<<" | "<<background<<deep_blue<<"YOU: "; //label
    for(int i = 0; i<window_width-5; ++i) cout<<" "; //fill left over space
    cout<<reset<<" |\n"; //end output 

	//............................................................................
	
	//card count
    cout<<" | "<<background<<deep_blue<<"CARDS("; //label
    if (num_cards_P2<10) cout<<"0"; //add 0 if num is 2-9
    cout<<num_cards_P2<<")"; //add number
    for(int i = 0; i<window_width-9; ++i) cout<<" "; //add leftover space
    cout<<reset<<" |\n"; //output end 
    
    //............................................................................
    
    //space
    cout<<" | "<<background; //output start
    for(int i = 0; i<window_width; ++i) cout<<" "; //output space
    cout<<reset<<" |\n"; //output end 
    
    //............................................................................

    //cards and hands
    if(face_up || (!face_up && !hand_covering)){ //face up or not hand covering 
        showing_card = (face_up) ? make_card(card_played_P2) : make_blank_card(); //either face up or face down, stores ascii 
        for(int i = 0; i<5; ++i){ //for each row
        	//-------------------------------------------------------------------
        	cout<<" | "<<background; //output start 
            for(int space = 0; space<leftover_width; ++space) cout<<" "; //output left 
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<LEFT_nocard[i][j]; //output ascii
			}
            cout<<reset; //reset colors
            //-------------------------- -----------------------------------------
            cout<<background<<"  "; //output space between card
            //-------------------------------------------------------------------
            for(int j = 0; j<6; ++j){ //for each col
            	if(i == 0 || i == 4 || j == 0 || j == 5){ //if not a card 
            		cout<<background; //keep blue bkg
				}else{
					if(face_up){ //if the card is up
						cout<<card_front; //set to color 
					}else{ //if down
						cout<<card_back; //set to other color
					}
				}
            	cout<<deep_blue<<showing_card[i][j]; //output card ascii
			}
            cout<<reset; //reset colors
            //-------------------------------------------------------------------
            cout<<background<<"  "; //add space 
            //-------------------------------------------------------------------
            for(int j = 0; j<9; ++j){ //loop through current row of LEFT HAND 
				cout<<deep_blue<<RIGHT_nocard[i][j]; //output ascii
			}
            cout<<reset; //reset colors
            //-------------------------------------------------------------------
            cout<<background; //set background color
			for(int space = 0; space<leftover_width; ++space) cout<<" "; //add space
            cout<<reset<<" |\n"; //output end 
            //-------------------------------------------------------------------
    	}
        
    	cout<<" | "<<background; //start output 
    	for(int space = 0; space<leftover_width; ++space) cout<<" "; //add left spaces
        for(int j = 0; j<9; ++j) cout<<deep_blue<<LEFT_nocard[5][j]; //do leftover hand ascii
        cout<<"          "; //add space in between
        for(int j = 0; j<9; ++j) cout<<deep_blue<<RIGHT_nocard[5][j]; //do leftover hand ascii
        for(int space = 0; space<leftover_width; ++space) cout<<" "; //add right space
        cout<<reset<<" |\n"; //end output 
      

    }else if(hand_covering){ //if the hand is covering the card 
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){ //for each col
            	cout<<" | "<<background<<deep_blue; //output start 
                for(int space = 0; space<leftover_width; ++space) cout<<" "; //left space
                for(int j = 0; j<9; ++j){ //for each col
                    cout<<LEFT_nocard[i][j]; //output ascii
                }
                cout<<"  "; //space inbetween hands
                for(int j = 0; j<9; ++j){ //for each col
                    cout<<RIGHT_card[i][j]; //output ascii 
                }
                for(int space = 0; space<leftover_width+8; ++space) cout<<" "; //right space
                cout<<reset<<" |\n"; //output end 
            }
        }else{ //left handed
            for(int i = 0; i<6; ++i){ //for each col
            	cout<<" | "<<background<<deep_blue; //output start
            	for(int space = 0; space<leftover_width+8; ++space) cout<<" "; //left space
                for(int j = 0; j<9; ++j){ //for each col
                    cout<<LEFT_card[i][j]; //output ascii
                }
                cout<<"  "; //output space in between 
                for(int j = 0; j<9; ++j){ //for each col
                    cout<<RIGHT_nocard[i][j]; //output ascii
                }
                for(int space = 0; space<leftover_width; ++space) cout<<" "; //right space 
				cout<<reset<<" |\n"; //output end 
            }
            
        }
    }

	//............................................................................
	
	//bottom border
    cout<<"   "; //space 
    for(int i = 0; i<window_width; ++i) cout<<"-"; //border
    cout<<" \n"; //newline 
    
    //............................................................................
    
	background = "\033[48;5;153m"; //change back to blue 
	
	//----------------------------------------------------------------------------
	
    //SLEEP
    std::this_thread::sleep_for(std::chrono::milliseconds(800)); //sleep
    
    //----------------------------------------------------------------------------
}

vector<vector<string>> make_card(card c){ //MAKES ASCII ART OF A CARD 

    /* THE FOLLOWING CODE CREATES THE ASCII ART OF A CARD WITH A VALUE.
        WE TAKE THE VALUES AND SUITS AND ASSIGN THEM TO CERTAIN POSITIONS.
        VALUES LIKE 11 ARE TRANSLATED TO THEIR NAMES LIKE, JACK. */

    vector<vector<string>> ascii_card (5, vector<string>(6)); //[5][6], stores card 
    //------------------------------------------
    ascii_card[0] = {" ","_","_","_","_"," "}; //top
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
    ascii_card[2] = {"|","-","-","-","-","|"}; //border 
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
    ascii_card[4] = {" ",upperscore,upperscore,upperscore,upperscore," "}; //end 
    //------------------------------------------
    return ascii_card; //return datastruct 
}

vector<vector<string>> make_blank_card(){ //RETURN BLANK CARD ASCII

    /*THIS FUNCTION INITIALIZES AND ASSIGNS A VECTOR WITH THE ASCII ART OF A BLANK CARD*/
    vector<vector<string>> ascii_card = { //stores blank card
        {" ","_","_","_","_"," "},
        {"|"," "," "," "," ","|"},
        {"|","-","-","-","-","|"},
        {"|"," "," "," "," ","|"},
        {" ",upperscore,upperscore,upperscore,upperscore," "}
    };
    return ascii_card; //return datastruct 
}
