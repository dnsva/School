

#include <iostream>
//#include <string>
#include "info.h"
#include <vector>

using std::vector;
using std::cout;
using std::string;

bool right_handed = true; //by default, changeable in main code
vector<vector<string>> make_blank_card();
vector<vector<string>> make_card(card c);

string upperscore = "\xE2\x80\xBE";

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

	//cout<<"IN UPDATE SCREEN\n\n";
	
    int window_width = 50; //terminal width minus some edge stuff MAKE SURE THIS IS EVEN 
    int needed_width = 9*2+4+6; //hands and cards (28)
   // int leftover_width = (window_width-(needed_width))/2; //add err check for 0; // = (get terminal width-needed width)/ 2, sides
	int leftover_width = window_width/2 - needed_width/2;
   //AI

	//cout<<"\nABOUT TO PRINT 1\n";
    //top border
    cout<<"   ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" \n";

	//cout<<"\nABOUT TO PRINT LABEL\n";
    //label ------ [|] + ["THEM:"] + [terminal_width - 7] + [|]
    cout<<" | THEM: ";
    for(int i = 0; i<window_width-6; ++i) cout<<" ";
    cout<<" |\n";

	//cout<<"\nABOUT TO PRINT CARDS \n";
    //curr cards ------ [|] + ["CARDS ("] + [ (num_cards_P1 < 10) ? cout<<"0"; cout<<num_cards_P1 ] + [")"] + [terminal_width -] + [|]
    cout<<" | CARDS(";
    if (num_cards_P1<10) cout<<"0";
    cout<<num_cards_P1<<")";
    for(int i = 0; i<window_width-9; ++i) cout<<" ";
    cout<<" |\n";
    
    //cout<<"\nABOUT TO PRINT HAND\n";
    //hands and cards 
    
    
    if(face_up || (!face_up && !hand_covering)){
    	
    	//cout<<"\nABOUT TO PRINT EITHER - FACE UP OR NOT HAND COVERING\n";
        vector<vector<string>> showing_card; //either face up or face down
        
        if(face_up){
            showing_card = make_card(card_played_P1);
        }else{
            showing_card = make_blank_card();
        }
        //cout<<"filled showing_card\n";
        
        for(int i = 0; i<5; ++i){
        	cout<<" | ";
            for(int space = 0; space<leftover_width; ++space) cout<<" ";
            for(int j = 0; j<9; ++j) cout<<FLIPPED_LEFT_nocard[i][j];
            cout<<"  ";
            for(int j = 0; j<6; ++j)cout<<showing_card[i][j];
            cout<<"  ";
            for(int j = 0; j<9; ++j) cout<<FLIPPED_RIGHT_nocard[i][j];
            for(int space = 0; space<leftover_width; ++space) cout<<" ";
            cout<<" |\n";
        }
        
        	cout<<" | ";
        	for(int space = 0; space<leftover_width; ++space) cout<<" ";
            //cout<<leftover_width;
            for(int j = 0; j<9; ++j) cout<<FLIPPED_LEFT_nocard[5][j];
            cout<<"          ";
            for(int j = 0; j<9; ++j) cout<<FLIPPED_RIGHT_nocard[5][j];
            for(int space = 0; space<leftover_width; ++space) cout<<" ";
            cout<<" |\n";
            

    }else if(hand_covering){
    	//cout<<"\nABOUT TO PRINT HAND COVERING \n";
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){
            	cout<<" | ";
                for(int space = 0; space<leftover_width; ++space) cout<<" ";
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_LEFT_nocard[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_RIGHT_card[i][j];
                }
                //cout<<7+leftover_width;
                for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
                cout<<" |\n";
            }
            
            
        }else{ //left handed
            for(int i = 0; i<6; ++i){
            	cout<<" | ";
            	for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
                //cout<<leftover_width+7;
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_LEFT_card[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<FLIPPED_RIGHT_nocard[i][j];
                }
                for(int space = 0; space<leftover_width; ++space) cout<<" ";
				cout<<" |\n";
            }
            
        }
    }

	//cout<<"\nABOUT TO PRINT SPACE\n";
    //space
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<" |\n";

	//cout<<"\nABOUT TO PRINT MID BORDER\n";
    //mid border
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" |\n";

	//cout<<"\nABOUT TO PRINT NOTE\n";
    //note ------- [|] + ["Note: "] + [note itself] + [terminal_width - 7 - note.length()] + [|]
    cout<<" | Note: "<<note;
    for(int i = 0; i<window_width - 6 - note.size(); ++i) cout<<" ";
    cout<<" |\n";

	//cout<<"\nABOUT TO PRINT MID BORDER 2\n";
    //mid border
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" |\n";

   //PLAYER

   // [|] + ["YOU:"] + [terminal_width - 6] + [|]
   // [|] + ["CARDS ("] + [ (num_cards_P1 < 10) ? cout<<"0"; cout<<num_cards_P1 ] + [")"] + [terminal_width -] + [|]

	//cout<<"\nABOUT TO PRINT 2\n";
    //label ------ [|] + ["YOU:"] + [terminal_width - 6] + [|]
    cout<<" | YOU: ";
    for(int i = 0; i<window_width-5; ++i) cout<<" ";
    cout<<" |\n";

	//cout<<"\nABOUT TO PRINT CARDS\n";
    //curr cards ------ [|] + ["CARDS ("] + [ (num_cards_P2 < 10) ? cout<<"0"; cout<<num_cards_P2 ] + [")"] + [terminal_width -] + [|]
    cout<<" | CARDS(";
    if (num_cards_P2<10) cout<<"0";
    cout<<num_cards_P2<<")";
    for(int i = 0; i<window_width-9; ++i) cout<<" ";
    cout<<" |\n";
    
   // cout<<"\nABOUT TO PRINT SPACE\n";
    //space
    cout<<" | ";
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<" |\n";

	//cout<<"\nABOUT TO PRINT CARDS AND HANDS\n";
    //cards and hands
    if(face_up || (!face_up && !hand_covering)){
    	
    //	cout<<"\nABOUT TO PRINT EITHER - FACE UP OR NOT HAND COVERING\n";
        vector<vector<string>> showing_card; //either face up or face down
        
        if(face_up){
            showing_card = make_card(card_played_P2);
        }else{
            showing_card = make_blank_card();
        }
        //cout<<"filled showing_card\n";
      
        for(int i = 0; i<5; ++i){
        	cout<<" | ";
            for(int space = 0; space<leftover_width; ++space) cout<<" ";
            for(int j = 0; j<9; ++j) cout<<LEFT_nocard[i][j];
            cout<<"  ";
            for(int j = 0; j<6; ++j)cout<<showing_card[i][j];
            cout<<"  ";
            for(int j = 0; j<9; ++j) cout<<RIGHT_nocard[i][j];
            for(int space = 0; space<leftover_width; ++space) cout<<" ";
            cout<<" |\n";
        }
        
    	cout<<" | ";
    	for(int space = 0; space<leftover_width; ++space) cout<<" ";
        //cout<<leftover_width;
        for(int j = 0; j<9; ++j) cout<<LEFT_nocard[5][j];
        cout<<"          ";
        for(int j = 0; j<9; ++j) cout<<RIGHT_nocard[5][j];
        for(int space = 0; space<leftover_width; ++space) cout<<" ";
        cout<<" |\n";
      

    }else if(hand_covering){
    	//cout<<"\nABOUT TO PRINT HAND COVERING \n";
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){
            	cout<<" | ";
                for(int space = 0; space<leftover_width; ++space) cout<<" ";
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_nocard[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_card[i][j];
                }
                //cout<<7+leftover_width;
                for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
                cout<<" |\n";
            }
            
            
        }else{ //left handed
            for(int i = 0; i<6; ++i){
            	cout<<" | ";
            	for(int space = 0; space<leftover_width+8; ++space) cout<<" ";
                //cout<<leftover_width+7;
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_card[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_nocard[i][j];
                }
                for(int space = 0; space<leftover_width; ++space) cout<<" ";
				cout<<" |\n";
            }
            
        }
    }

//	cout<<"hello?\n";
	//bottom border
    cout<<"   ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<" \n";
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
            ascii_card[1][4] = c.value;
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
            ascii_card[3][1] = c.value;
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
