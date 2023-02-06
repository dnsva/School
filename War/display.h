
#include <iostream>
#include "card_info.h"

using std::cout;

bool right_handed = true; //by default, changeable in main code
wchar_t make_blank_card();
wchar_t make_card(card c);

//2d arrays for hands

wchar_t FLIPPED_RIGHT_nocard [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {' ','/',' ',' ',' ',' ',' ',' ','\\'}, //0
    {'|',' ','|',' ','|',' ','|',' ','|'},  //1
    {' ','‾','|',' ','|',' ','|',' ','|'},  //2
    {' ',' ',' ','‾',' ','‾',' ','‾',' '},  //3
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},  //4
    {' ',' ',' ',' ',' ',' ',' ',' ',' '}   //5
};
wchar_t FLIPPED_RIGHT_card   [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {' ','/',' ',' ',' ',' ',' ',' ','\\'}, //0
    {'|',' ','|',' ','|',' ','|',' ','|'},  //1
    {' ','‾','|',' ','|',' ','|',' ','|'},  //2
    {' ',' ',' ','‾','|','‾',' ','‾','|'},  //3
    {' ',' ',' ',' ','|','_','_','_','|'},  //4
    {' ',' ',' ',' ',' ',' ',' ',' ',' '}   //5
};
wchar_t FLIPPED_LEFT_nocard  [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {'/',' ',' ',' ',' ',' ',' ','\\',' '}, //0
    {'|',' ','|',' ','|',' ','|',' ','|'},  //1
    {'|',' ','|',' ','|',' ','|','‾',' '},  //2
    {' ','‾',' ','‾',' ','‾',' ',' ',' '},  //3
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},  //4
    {' ',' ',' ',' ',' ',' ',' ',' ',' '}   //5
};
wchar_t FLIPPED_LEFT_card    [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {'/',' ',' ',' ',' ',' ',' ','\\',' '}, //0
    {'|',' ','|',' ','|',' ','|',' ','|'},  //1
    {'|',' ','|',' ','|',' ','|','‾',' '},  //2
    {' ','‾','|','‾',' ','‾','|',' ',' '},  //3
    {' ',' ',' ',' ','|','_','_','_','|'},  //4
    {' ',' ',' ',' ',' ',' ',' ',' ',' '}   //5
};
wchar_t RIGHT_nocard         [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {' ',' ',' ','_',' ','_',' ','_',' '},  //0
    {' ','_','|',' ','|',' ','|',' ','|'},  //1
    {'|',' ','|',' ','|',' ','|',' ','|'},  //2
    {' ','\\',' ',' ',' ',' ',' ',' ','/'}, //3
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},  //4
    {' ',' ',' ',' ',' ',' ',' ',' ',' '}   //5
};
wchar_t RIGHT_card           [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {' ',' ',' ',' ',' ','_','_','_',' '},  //0
    {' ',' ',' ',' ','|',' ',' ',' ','|'},  //1
    {' ',' ',' ','_','|','_',' ','_','|'},  //2
    {' ','_','|',' ','|',' ','|',' ','|'},  //3
    {'|',' ','|',' ','|',' ','|',' ','|'},  //4
    {' ','\\',' ',' ',' ',' ',' ',' ','/'}  //5
};
wchar_t LEFT_nocard          [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {' ','_',' ','_',' ','_',' ',' ',' '},  //0
    {'|',' ','|',' ','|',' ','|','_',' '},  //1
    {'|',' ','|',' ','|',' ','|',' ','|'},  //2
    {'\\',' ',' ',' ',' ',' ',' ','/',' '}, //3
    {' ',' ',' ',' ',' ',' ',' ',' ',' '},  //4
    {' ',' ',' ',' ',' ',' ',' ',' ',' '}   //5
};
wchar_t LEFT_card            [6][9] = {
    //0   1   2   3   4   5   6   7   8
    {' ','_','_','_',' ',' ',' ',' ',' '},  //0
    {'|','_',' ','_','|',' ',' ',' ',' '},  //1
    {'|','_',' ','_','|','_',' ',' ',' '},  //2
    {'|',' ','|',' ','|',' ','|','_',' '},  //3
    {'|',' ','|',' ','|',' ','|',' ','|'},  //4
    {'\\',' ',' ',' ',' ',' ',' ','/',' '}  //5
};

void update_screen(
    std::string note,
    int num_cards_P1,
    int num_cards_P2,
    bool face_up,
        //y?
        card card_played_P1,
        card card_played_P2,
        //n?
        bool hand_covering
){

    int window_width = 100; //terminal width minus some edge stuff
    int needed_width = 9*2+8; //hands and cards
    int leftover_width = window_width/2; // = (get terminal width-needed width)/ 2, sides

   //AI

    //top border
    cout<<"  ";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<"\n";

    //label ------ [|] + ["THEM:"] + [terminal_width - 7] + [|]
    cout<<" | THEM: ";
    for(int i = 0; i<window_width-7; ++i) cout<<" ";
    cout<<"|\n";

    //curr cards ------ [|] + ["CARDS ("] + [ (num_cards_P1 < 10) ? cout<<"0"; cout<<num_cards_P1 ] + [")"] + [terminal_width -] + [|]
    cout<<" | CARDS(";
    if (num_cards_P1<10) cout<<"0";
    cout<<num_cards_P1<<")";
    for(int i = 0; i<window_width-10; ++i) cout<<" ";
    cout<<"|\n";
    
    //hands and cards 
    if(face_up || (!face_up && !hand_covering)){
        char showing_card [4][5]; //either face up or face down
        if(face_up){
            showing_card = make_card(card_played_P1);
        }else{
            showing_card = make_blank_card();
        }

        for(int i = 0; i<2; ++i){
            cout<<leftover_width;
            for(int j = 0; j<9; ++j) cout<<FLIPPED_LEFT_nocard[i][j];
            cout<<"         ";
            for(int j = 0; j<9; ++j) cout<<FLIPPED_RIGHT_nocard[i][j];
            cout<<leftover_width;
        }

        for(int i = 0; i<5; ++i){
            cout<<leftover_width;
            for(int j = 0; j<9; ++j) cout<<FLIPPED_LEFT_nocard[i+2][j];
            cout<<"  ";
            for(int j = 0; j<5; ++j) cout<<showing_card[i][j]
            cout<<"  ";
            for(int j = 0; j<9; ++j) cout<<FLIPPED_RIGHT_nocard[i+2][j];
            cout<<leftover_width;
        }

    }else if(hand_covering){
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){
                cout<<leftover_width;
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_nocard[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_card[i][j];
                }
                cout<<7+leftover_width;

            }
        }else{ //left handed
            for(int i = 0; i<6; ++i){
                cout<<leftover_width+7;
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_card[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_nocard[i][j];
                }
                cout<<leftover_width;

            }
        }
    }

    //space
    cout<<" |";
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<"|\n";

    //mid border
    cout<<" |";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<"|\n";

    //note ------- [|] + ["Note: "] + [note itself] + [terminal_width - 7 - note.length()] + [|]
    cout<<" | Note: "<<note;
    for(int i = 0; i<window_width - 7 - note.size(); ++i) cout<<" ";
    cout<<"|\n";

    //mid border
    cout<<" |";
    for(int i = 0; i<window_width; ++i) cout<<"-";
    cout<<"|\n";

   //PLAYER

   // [|] + ["YOU:"] + [terminal_width - 6] + [|]
   // [|] + ["CARDS ("] + [ (num_cards_P1 < 10) ? cout<<"0"; cout<<num_cards_P1 ] + [")"] + [terminal_width -] + [|]

    //label ------ [|] + ["YOU:"] + [terminal_width - 6] + [|]
    cout<<" | YOU: ";
    for(int i = 0; i<window_width-6; ++i) cout<<" ";
    cout<<"|\n";

    //curr cards ------ [|] + ["CARDS ("] + [ (num_cards_P2 < 10) ? cout<<"0"; cout<<num_cards_P2 ] + [")"] + [terminal_width -] + [|]
    cout<<" | CARDS(";
    (num_cards_P2<10) ? cout<<"0";
    cout<<num_cards_P2<<")";
    for(int i = 0; i<window_width-10; ++i) cout<<" ";
    cout<<"|\n";
    
    //space
    cout<<" |";
    for(int i = 0; i<window_width; ++i) cout<<" ";
    cout<<"|\n";

    //cards and hands
    if(face_up || (!face_up && !hand_covering)){
        char showing_card [4][5]; //either face up or face down
        if(face_up){
            showing_card = make_card(card_played_P2);
        }else{
            showing_card = make_blank_card();
        }

        for(int i = 0; i<2; ++i){
            cout<<leftover_width;
            for(int j = 0; j<9; ++j) cout<<LEFT_nocard[i][j];
            cout<<"         ";
            for(int j = 0; j<9; ++j) cout<<RIGHT_nocard[i][j];
            cout<<leftover_width;
        }

        for(int i = 0; i<5; ++i){
            cout<<leftover_width;
            for(int j = 0; j<9; ++j) cout<<LEFT_nocard[i+2][j];
            cout<<"  ";
            for(int j = 0; j<5; ++j) cout<<showing_card[i][j]
            cout<<"  ";
            for(int j = 0; j<9; ++j) cout<<RIGHT_nocard[i+2][j];
            cout<<leftover_width;
        }

    }else if(hand_covering){
        if(right_handed){ //right handed
            for(int i = 0; i<6; ++i){
                cout<<leftover_width;
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_nocard[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_card[i][j];
                }
                cout<<7+leftover_width;

            }
        }else{ //left handed
            for(int i = 0; i<6; ++i){
                cout<<leftover_width+7;
                for(int j = 0; j<9; ++j){
                    cout<<LEFT_card[i][j];
                }
                cout<<"  ";
                for(int j = 0; j<9; ++j){
                    cout<<RIGHT_nocard[i][j];
                }
                cout<<leftover_width;

            }
        }
    }

}

wchar_t make_card(card c){
    wchar_t ascii_card[4][5];
    //------------------------------------------
    ascii_card[0] = {' ','_','_','_','_',' '};
    //------------------------------------------
    //------------> [suit][value]
    /*edge*/ ascii_card[1][0] = '|';
    /*edge*/ ascii_card[1][5] = '|';
    /*suit*/ ascii_card[1][1] = c.suit;
    /*____________value___________*/
    ascii_card[1][2] = ' ';
    if(c.value == 10){
        ascii_card[1][3] = '1';
        ascii_card[1][4] = '0';
    }else if(c.value == 15){
        ascii_card[1][3] = 'J';
        ascii_card[1][4] = 'K';
    }else{
        ascii_card[1][3] = ' ';
        if(c.value < 11){
            ascii_card[1][4] = c.value;
        }else if(c.value == 11){
            ascii_card[1][4] = 'J';
        }else if(c.value == 12){
            ascii_card[1][4] = 'Q';
        }else if(c.value == 13){
            ascii_card[1][4] = 'K';
        }else if(c.value == 14){
            ascii_card[1][4] = 'A';
        }
    }
    //------------------------------------------
    ascii_card[2] = {'|','-','-','-','-','|'};
    //------------------------------------------
    //------------> [value][suit]
    /*edge*/ ascii_card[3][0] = '|';
    /*edge*/ ascii_card[3][5] = '|';
    /*____________value___________*/
    if(c.value == 10){
        ascii_card[3][1] = '1';
        ascii_card[3][2] = '0';
    }else if(c.value == 15){
        ascii_card[3][1] = 'J';
        ascii_card[3][2] = 'K';
    }else{
        ascii_card[3][2] = ' ';
        if(c.value < 11){
            ascii_card[3][1] = c.value;
        }else if(c.value == 11){
            ascii_card[3][1] = 'J';
        }else if(c.value == 12){
            ascii_card[3][1] = 'Q';
        }else if(c.value == 13){
            ascii_card[3][1] = 'K';
        }else if(c.value == 14){
            ascii_card[3][1] = 'A';
        }
    }
    ascii_card[3][3] = ' ';
    /*suit*/ ascii_card[3][4] = c.suit;
    //------------------------------------------
    ascii_card[4] = {' ','‾','‾','‾','‾',' '};
    //------------------------------------------
    return ascii_card;
}

wchar_t make_blank_card(){
    char ascii_card[4][5] = {
        {' ','_','_','_','_',' '},
        {'|',' ',' ',' ',' ','|'},
        {'|','-','-','-','-','|'},
        {'|',' ',' ',' ',' ','|'},
        {' ','‾','‾','‾','‾',' '}
    };
    return ascii_card;
}