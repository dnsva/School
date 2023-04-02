
#ifndef INFO_H //header guard
#define INFO_H ///guard

#include <iostream>  //input output
#include <queue>     //to store cards
#include <vector>    //for shuffling deck
#include <stdlib.h>  //for random
#include <stdio.h>   //for random
#include <time.h>    //for random

using std::vector; //less typing

struct card{ //card datastructure 

    int value; //number on card
    char suit; //suit of card
    
    card(int value_, char suit_)    //card constructor 
    : value(value_), suit(suit_) {} //assign everything as normal

    card() = default; //default values 

};

struct player{ //player datastructure 

    std::queue<card>cards; //stores the cards the player has

    //Actions player can do:

    void add_card(card c){ //add a card to players deck
        cards.push(c); //pushes to queue
    }

    card play_card(){ //plays a card
        card top_card = cards.front(); //get top card
        cards.pop(); //remove it from the queue
        return top_card; //return the top card
    }

    int num_cards(){ //gets the curr number of cards
        return cards.size(); //returns size of queue
    }

};

void deal_cards(player* p1, player* p2){ //deals cards to each player

    srand(time(0)); //for random numbers 

    vector<card>deck; //this will hold the unshuffled deck
    vector<card>shuffled_deck (54, card(0, '?')); //this will hold the shuffled deck
                                                  //we initialize each place to an empty card 

    //CREATE NORM DECK
    for(int i = 2; i<=14; ++i){ //for each type of card
        deck.push_back(card(i, 'H')); //add hearts
        deck.push_back(card(i, 'D')); //add diamonds
        deck.push_back(card(i, 'S')); //add spades
        deck.push_back(card(i, 'C')); //add clubs
    }
    deck.push_back(card(15, '-')); //add 2 jokers
    deck.push_back(card(15, '-')); //a2j
    
    //SUFFLE DECK
    for(int i = 0; i < 54; ++i){ //-> for each card in the ordered deck, 
        int new_pos = rand()%54; //-> randomly generate a pos for each card in deck to place into shuffled deck

        
        while(shuffled_deck[new_pos].value != 0){ //-> if the new pos is already used,
        	new_pos = rand()%54;                  //-> find another one 
		}
        
        shuffled_deck[new_pos] = deck[i]; //fill pos with card 
    }

    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //FOR MRS. MORIN FOR TESTING 
    //------THIS CAUSES ONE WAR:----
    //(*p1).add_card({5, 'D'});   //|
    //(*p2).add_card({5, 'H'});   //|
    //------------------------------

    //ADD THIS TO GET A DOUBLE WAR---
    //(*p1).add_card({2, 'D'});   //|
    //(*p2).add_card({3, 'H'});   //|
    //(*p1).add_card({4, 'D'});   //|
    //(*p2).add_card({5, 'H'});   //|
    /*                          *///|
    //(*p1).add_card({6, 'D'});   //|
    //(*p2).add_card({6, 'H'});   //|
    //------------------------------
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //DISTRIBUTE CARDS
    for(int i = 0; i < 27; ++i){ //first half 
        (*p1).add_card(shuffled_deck[i]); //add to AI
    }
    for(int i = 27; i < 54; ++i){ //second half
        (*p2).add_card(shuffled_deck[i]); //add to Player
    }
    
}

#endif //guard
