
#include <iostream>
#include <vector>
#include <queue>

#include "card_data.h"

struct player{

    std::queue<card>cards;

    //Actions player can do (as methods)

    void add_card(card c){
        cards.push(c);
    }

    card play_card(){
        card top_card = cards.front();
        cards.pop();
        return top_card;
    }

    int num_cards(){
        return cards.size();
    }

};