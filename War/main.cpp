
#include <iostream>

#include "card_info.h"
#include "player_info.h"

using namespace std;

void play(){

    //Create players

    player p1, p2;

    //Deal cards

    deal_cards(&p1, &p2);

    //Play 

    while(p1.card_num != 0 && p2.card_num != 0){

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
}