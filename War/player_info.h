
#include <iostream>
#include <vector>
#include <queue>

#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H
#include "card_info.h"

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

#endif