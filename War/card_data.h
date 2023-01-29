
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include "player_data.h"

struct card{

    int value; //number on card
    char suit; //suit of card

};

void deal_cards(player* p1, player* p2){

    //We will need random numbers so 
    srand(time(0));

    std::vector<card>deck;
    std::vector<card>suffled_deck {54, 0};

    //First we get the deck out of the package 

    //Creation of deck 

    for(int i = 2; i<=13; ++i){
        deck.push_back({i, 'h'}); //hearts
        deck.push_back({i, 'd'}); //diamonds
        deck.push_back({i, 's'}); //spades
        deck.push_back({i, 'c'}); //clubs
    }
    //and jokers
    deck.push_back({14, 'j'});
    deck.push_back({14, 'j'});

    //Now we have to shuffle it 

    for(int i = 0; i < deck.size(); ++i){ //we will randomly generate a pos for each card in deck to place into shuffled deck

        int new_pos = rand()%54 + 1;

        while(shuffled_deck[new_pos] == 0){ //if already taken
            new_pos = rand()%54 + 1; //roll new pos 
        }

        shuffled_deck[new_pos] = shuffled[i];

    }

    //Deck should be shuffled

    //New we add the cards to the queues of p1 and p2 

    //since 54/2 is 27, each player gets 27 cards

    for(int i = 0; i < 27; ++i){
        p1.cards.push(shuffled_deck[i]);
    }

    for(int i = 27; i < 54; ++i){
        p2.cards.push(shuffled_deck[i]);
    }

}.