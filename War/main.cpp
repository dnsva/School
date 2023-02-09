

#include "ascii_stuff.h"

#ifdef _WIN32
	bool ok = init_term();
#endif

#include <iostream>
#include <thread>
#include <chrono>
#include "info.h"
#include "display.h"

using namespace std;

void show_rules(){
	cout<<"Look at your browser...\n";
	ShellExecute(NULL, "open", "https://bicyclecards.com/how-to-play/war",NULL, NULL, SW_SHOWNORMAL);
	
}

bool quit(){ //true - yes, quit, false - no, continue 
	char confirm_quit;
	cout<<"Are you sure (y/n)? ";
	cin>>confirm_quit;
	while(confirm_quit != 'y' && confirm_quit != 'n'){
		cout<<"Bad input, try again (y/n): ";
		cin>>confirm_quit;
	}
	if(confirm_quit == 'y'){
		return true;
	}else{
		return false;
	}
	
}

void play(){

    player p1, p2; //Create players
	
	cout<<reset<<light_purple;
	
	cout<<newpage; //clear screen
	cout<<"D\n";
	cout<<"E\n";
	cout<<"A\n";
	cout<<"L\n";
	cout<<"I\n";
	cout<<"N\n";
	cout<<"G\n\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //sleep
	cout<<"C\n";
	cout<<"A\n";
	cout<<"R\n";
	cout<<"D\n";
	cout<<"S\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //sleep
	cout<<".\n";
	cout<<".\n";
	cout<<".\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //sleep
	cout<<newpage;
	//std::this_thread::sleep_for(std::chrono::milliseconds(500)); //sleep
    deal_cards(&p1, &p2); //Deal cards
	cout<<"CARDS DEALT...\n";
	cout<<reset;
	
    //PLAY

    //which hand (EXTRA) 
    char dominant_hand;
    cout<<"are you left handed or right handed (r/l)?\n> ";
    cin>>dominant_hand;
    while(dominant_hand != 'r' && dominant_hand != 'l'){
        cout<<"bad input, try again: ";
        cin>>dominant_hand;
    }
    right_handed = (dominant_hand == 'r') ? 1:0; //change global var from display.h
 
    while(p1.num_cards() != 0 && p2.num_cards() != 0){
  		
  		update_screen("...", p1.num_cards(), p2.num_cards(), false, {}, {}, false);
  		
		char in_game_options;
		cout<<"What do you want to do? Enter the char 'p' to play a card, 'q' to quit the match\n> ";
		cin>>in_game_options;
		while(in_game_options != 'p' && in_game_options != 'q'){
			cout<<"Bad input... Try again\n> ";
			cin>>in_game_options;
		}
		if(in_game_options == 'q'){
			break;
		} //else just continue 
  		
  		update_screen("About to play card...", p1.num_cards(), p2.num_cards(), false, {}, {}, true);
  		
        card player_card, ai_card;
        player_card = p1.play_card();
        ai_card = p2.play_card();
       // cout<<"\tp1 played "<<player_card.suit<<", "<<player_card.value<<"\n";
        //cout<<"\tp2 played "<<ai_card.suit<<", "<<ai_card.value<<"\n";
        
        update_screen("Cards played", p1.num_cards(), p2.num_cards(), true, ai_card, player_card, false);
        //add extra sleep 
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            
        //DISPLAY
    	//update_screen("test", p1.num_cards(), p2.num_cards(), false, player_card, ai_card, false);
    	//-----------------

        if(player_card.value > ai_card.value){
            p2.add_card(player_card);
            p2.add_card(ai_card);
            update_screen("PLAYER TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false);
            //add extra sleep 
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            //cout<<"\tp1 took cards\n";
        }else if(player_card.value < ai_card.value){
            p1.add_card(player_card);
            p1.add_card(ai_card);
            update_screen("AI TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false);
            //add extra sleep 
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            //cout<<"\tp2 took cards\n";
        }else{
        	
        	//cout<<"Would be a war but we end the prog here for now \n";
        	//return;
        	
            cout<<"WAR\n";
            //WAR
            vector<card>extra_war_cards;

            while(player_card.value == ai_card.value){
				
				cout<<"What do you want to do? Enter the char 'p' to play cards, 'q' to quit the match\n> ";
				cin>>in_game_options;
				while(in_game_options != 'p' && in_game_options != 'q'){
					cout<<"Bad input... Try again\n> ";
					cin>>in_game_options;
				}
				
				update_screen("About to play cards (2 face down, 1 up) ...", p1.num_cards(), p2.num_cards(), false, {}, {}, true);
				//add extra sleep 
       			std::this_thread::sleep_for(std::chrono::milliseconds(900));
                //2 cards down each unless someone doesnt have enough cards
                //if they dont have enough cards they just put out whatever they have

                for(int i = 0; i<2 && i<p1.num_cards()-1; ++i){ //minus 1 because we need to still draw cards that count
                    extra_war_cards.push_back(p1.play_card());
                }
                for(int i = 0; i<2 && i<p2.num_cards()-1; ++i){
                    extra_war_cards.push_back(p2.play_card());
                }
				
				extra_war_cards.push_back(player_card); //old main ones (if double war)
				extra_war_cards.push_back(ai_card); //old main ones (if double war)
                //Draw new cards that count 

                player_card = p2.play_card();
                ai_card = p1.play_card();
                
                update_screen("Cards played", p1.num_cards(), p2.num_cards(), true, ai_card, player_card, false);
                //add extra sleep 
        		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }

            //Now since we've dealt with the war, we act like norm
            if(player_card.value > ai_card.value){
                p2.add_card(player_card);
                p2.add_card(ai_card);
                for(card c : extra_war_cards){
                	p2.add_card(c);
				}
                update_screen("AI TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false);
           		//add extra sleep 
            	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }else if(player_card.value < ai_card.value){
                p1.add_card(player_card);
                p1.add_card(ai_card);
                for(card c : extra_war_cards){
                	p1.add_card(c);
				}
                update_screen("PLAYER TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false);
           		//add extra sleep 
            	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

        }

    }


}

int main(){
    //cout<<"Hello world";
    //string test = "test";
    //play();
    //              note  cards p1, cards p2, 
    //update_screen("test", 3, 14, false, {4, 'D'}, {5, 'H'}, true);
    //update_screen("test", 3, 14, false, {4, 'D'}, {5, 'H'}, false);
 
 	//SET THE FOREGROUND COLOR TO BE LIGHT PURPLE
 	cout<<light_purple;
 	
 	
 	
	bool done = false;
	int choice = -1;
	while(!done){
		cout<<newpage; //get new page 
		//cout<<deep_blue<<"\x1b[5m";
		display_title();
		cout<<"(0) - Play\n";
		cout<<"(1) - See rules\n";
		cout<<"(2) - Quit\n";
		cout<<"Enter choice: ";
		cin>>choice;
		while(choice < 0 || choice > 2){
			cout<<"Bad input. Try again: ";
			cin>>choice;
		}
		if(choice == 0){
			play();
		}else if(choice == 1){
			show_rules();
		}else{
			done = quit();
		}
	}
}

//update_screen( note, num_cards_P1, num_cards_P2, face_up?(bool), card_played_P1, card_played_P2, hand_covering? )
