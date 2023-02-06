
#include <iostream>

#include "card_info.h"
#include "player_info.h"
#include "display.h"

using namespace std;

void play(){

    //Create players

    player p1, p2;

    //Deal cards

    deal_cards(&p1, &p2);

    //Play 

    //which hand
    char dominant_hand;
    cout<<"are you left handed or right handed (r/l)?";
    cin>>dominant_hand;
    while(dominant_hand != 'r' && dominant_hand != 'l'){
        cout<<"bad input, try again: ";
        cin>>dominant_hand;
    }
    right_handed = (dominant_hand == 'r') ? 1:0;

    while(p1.num_cards() != 0 && p2.num_cards() != 0){

        //while there are still cards 

        card player_card, ai_card;

        player_card = p1.play_card();
        ai_card = p2.play_card();

        if(player_card.value > ai_card.value){
            p1.add_card(player_card);
            p1.add_card(ai_card);
        }else if(player_card.value < ai_card.value){
            p2.add_card(player_card);
            p2.add_card(ai_card);
        }else{
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
            }else if(player_card.value < ai_card.value){
                p2.add_card(player_card);
                p2.add_card(ai_card);
            }

        }

    }


}

int main(){
    cout<<"Hello world";
    string test = "test";
    update_screen(test, 3, 14, false, {4, 'D'}, {5, 'H'}, false);
}