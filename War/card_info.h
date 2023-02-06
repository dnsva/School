
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef CARD_INFO_H
#define CARD_INFO_H
#include "player_info.h"

using std::vector;

struct card{

    int value; //number on card
    char suit; //suit of card
    
    card(int value_, char suit_)
    : value(value_), suit(suit_) {} //assign everything as normal

    card() = default; //default 

};

void deal_cards(player* p1, player* p2){ //deals cards to each player

    srand(time(0));
    vector<card>deck;
    vector<card>shuffled_deck (54, card(0, '?'));

    //CREATE DECK
    for(int i = 2; i<=14; ++i){
        deck.push_back(card(i, 'H')); //hearts
        deck.push_back(card(i, 'D')); //diamonds
        deck.push_back(card(i, 'S')); //spades
        deck.push_back(card(i, 'C')); //clubs
    }
    deck.push_back(card(15, 'J')); //jokers
    deck.push_back(card(15, 'J'));

    //SUFFLE DECK
    for(int i = 0; i < deck.size(); ++i){ //randomly generate a pos for each card in deck to place into shuffled deck
        int new_pos = rand()%54 + 1;
        while(shuffled_deck[new_pos].value == 0){ //if already taken
            new_pos = rand()%54 + 1; //roll new pos 
        }
        shuffled_deck[new_pos] = deck[i];
    }

    //DISTRIBUTE CARDS
    //Now we add the cards to the queues of p1 and p2 
    //since 54/2 is 27, each player gets 27 cards
    for(int i = 0; i < 27; ++i){
        (*p1).add_card(shuffled_deck[i]);
    }
    for(int i = 27; i < 54; ++i){
        (*p2).add_card(shuffled_deck[i]);
    }

}

#endif