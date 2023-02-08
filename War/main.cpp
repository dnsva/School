
#include <iostream>
#include "info.h"
#include "display.h"
#include "ascii_stuff.h"

#ifdef _WIN32
	bool ok = init_term();
#endif

using namespace std;

void play(){

    cout<<"in play()\n";
    //Create players

    player p1, p2;
    cout<<"Players created\n";

    //Deal cards

    deal_cards(&p1, &p2);
    cout<<"Cards dealt\n";
    //Play 

    //which hand (EXTRA FINISH LATER)

    char dominant_hand;
    cout<<"are you left handed or right handed (r/l)?";
    cin>>dominant_hand;
    while(dominant_hand != 'r' && dominant_hand != 'l'){
        cout<<"bad input, try again: ";
        cin>>dominant_hand;
    }
    bool right_handed = (dominant_hand == 'r') ? 1:0;
 

    while(p1.num_cards() != 0 && p2.num_cards() != 0){
  
        cout<<"p1 has "<<p1.num_cards()<<", p2 has "<<p2.num_cards()<<"\n";
        //while there are still cards 

        card player_card, ai_card;

        player_card = p1.play_card();
        cout<<"\tp1 played "<<player_card.suit<<", "<<player_card.value<<"\n";
        ai_card = p2.play_card();
        cout<<"\tp2 played "<<ai_card.suit<<", "<<ai_card.value<<"\n";
        
        //DISPLAY
    	update_screen("test", p1.num_cards(), p2.num_cards(), false, player_card, ai_card, false);
    	//-----------------

        if(player_card.value > ai_card.value){
            p1.add_card(player_card);
            p1.add_card(ai_card);
            cout<<"\tp1 took cards\n";
        }else if(player_card.value < ai_card.value){
            p2.add_card(player_card);
            p2.add_card(ai_card);
            cout<<"\tp2 took cards\n";
        }else{
            cout<<"WAR\n";
            //WAR
            vector<card>extra_war_cards;

            while(player_card.value == ai_card.value){

                //2 cards down each unless someone doesnt have enough cards
                //if they dont have enough cards they just put out whatever they have

                for(int i = 0; i<2 && i<p1.num_cards()-1; ++i){ //minus 1 because we need to still draw cards that count
                    extra_war_cards.push_back(p1.play_card());
                }
                for(int i = 0; i<2 && i<p2.num_cards()-1; ++i){
                    extra_war_cards.push_back(p2.play_card());
                }

                //Draw new cards that count 

                player_card = p1.play_card();
                ai_card = p2.play_card();
                
            }

            //Now since we've dealt with the war, we act like norm
            if(player_card.value > ai_card.value){
                p1.add_card(player_card);
                p1.add_card(ai_card);
                cout<<"\tp1 takes cards\n";
            }else if(player_card.value < ai_card.value){
                p2.add_card(player_card);
                p2.add_card(ai_card);
                cout<<"\tp2 takes cards\n";
            }

        }

    }


}

int main(){
    //cout<<"Hello world";
    string test = "test";
    //play();
    //update_screen("test", 3, 14, false, {4, 'D'}, {5, 'H'}, true);
    update_screen("test", 3, 14, false, {4, 'D'}, {5, 'H'}, false);
    cout<<"returned\n";
    return 0;
}
