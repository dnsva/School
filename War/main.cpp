
#include <iostream>  //i/o
#include <thread>    //sleep 
#include <chrono>    //sleep
#include "info.h"    //classes
#include "display.h" //displays

#include "enable_ansi.h" //allows ansi codes 
#ifdef _WIN32
	bool ok = init_term(); //if were on windows
#endif

using namespace std; //less typing 

//FUNCTIONS -------------------------
void show_rules(); //shows the rules|
bool quit();       //exits game     |
void play();       //plays game     |
//----------------------------------

//-----------------------------------------------------------------------------------

int main(){ //main - calls other funcs 

 	cout<<light_purple; //SET THE FOREGROUND COLOR TO BE LIGHT PURPLE
 	
	bool done = false; //tells us whether to run or not 
	int choice = -1;   //tells us what function to call

	while(!done){ //while not done 

		cout<<newpage; //clear screen 
		display_title(); //show "WAR"
		cout<<"(0) - Play\n";      //output
		cout<<"(1) - See rules\n"; //output
		cout<<"(2) - Quit\n";      //output
		cout<<"Enter choice: ";    //prompt
		cin>>choice;               //get

		while(choice < 0 || choice > 2){ //error check 
			cout<<"Bad input. Try again: "; //error msg
			cin>>choice; //get again
		}

		if(choice == 0){ //if 0 entered
			play(); //call func 
		}else if(choice == 1){ //if 1 entered
			show_rules(); //call func
		}else{ //if 2 entered
			done = quit(); //leave
		}
	}
}

//-----------------------------------------------------------------------------------

void show_rules(){ //pulls up the rules 
	cout<<"Look at your browser...\n"; //output
	ShellExecute(NULL, "open", "https://bicyclecards.com/how-to-play/war",NULL, NULL, SW_SHOWNORMAL); //open link
	cout<<"You will go back to the main screen in 5 seconds\n"; //clarification
	std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //sleep	
}

//-----------------------------------------------------------------------------------

bool quit(){ //true - yes, quit, false - no, continue 
	char confirm_quit; //holds confirmation
	cout<<"Are you sure (y/n)? "; //ask
	cin>>confirm_quit; //get
	while(confirm_quit != 'y' && confirm_quit != 'n'){ //error check
		cout<<"Bad input, try again (y/n): "; //err message
		cin>>confirm_quit; //get input 
	}
	if(confirm_quit == 'y'){ //if yes quit 
		return true; //return yes 
	}else{ //if no quit 
		return false; //return no 
	}	
}

//-----------------------------------------------------------------------------------

void play(){ //main function that plays the game 

    player p1, p2; //Create players
	char dominant_hand; //To store dominant hand
	char in_game_options; //stores whether we want to keep playing or quit mid game
	//VARS USED IN MAIN LOOP:
	card player_card, ai_card; //will store the current cards of ai and player 
		//Used for WAR
		vector<card>WAR_cards_from_p1; //all the cards played by p1 (ai)
		vector<card>WAR_cards_from_p2; //all the cards played by p2 (player)
		bool enough_cards = true; //boolean to store whether or not there are enough cards to play 
	

	//------------------------------------------------------------------------------
	
	cout<<reset<<light_purple; //set text to light purple 
	
	/* THE FOLLOWING PRINTS (DEALING CARDS...)
	   VERTICALLY WITH SLEEPS IN BETWEEN      */
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
	cout<<newpage; //clear screen 
	

    deal_cards(&p1, &p2); //Deal cards
	cout<<"CARDS DEALT...\n"; //Output
	cout<<reset; //Reset any colors
	
    //-----------------------------------PLAY---------------------------------

    //ask for dominant hand (used in display.h)
    cout<<"are you left handed or right handed (r/l)?\n> "; //ask
    cin>>dominant_hand; //get
    while(dominant_hand != 'r' && dominant_hand != 'l'){ //err check
        cout<<"bad input, try again: "; //err message
        cin>>dominant_hand; //get again 
    }
    right_handed = (dominant_hand == 'r') ? 1:0; //change global var from display.h
 
    //WHILE NO ONE HAS WON YET -------------------------------------------------
    while(p1.num_cards() != 0 && p2.num_cards() != 0){ //while neither person has 0 cards
  		
  		update_screen("...", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display 
  		
		cout<<"What do you want to do? Enter the char 'p' to play a card, 'q' to quit the match\n> "; //ask
		cin>>in_game_options; //get
		while(in_game_options != 'p' && in_game_options != 'q'){ //err check 
			cout<<"Bad input... Try again\n> "; //err msg
			cin>>in_game_options; //get again 
		}
		if(in_game_options == 'q'){ //if quit
			break; //get out of loop
		} //else just continue 
  		
  		update_screen("About to play card...", p1.num_cards(), p2.num_cards(), false, {}, {}, true); //display 
  		
        player_card = p1.play_card(); //play a card
        ai_card = p2.play_card();     //play a card 
        
        update_screen("Cards played", p1.num_cards(), p2.num_cards(), true, ai_card, player_card, false); //display
        std::this_thread::sleep_for(std::chrono::milliseconds(1500)); //add extra sleep 

        if(player_card.value > ai_card.value){ //IF PLAYER HAS A GREATER CARD VALUE 
            p2.add_card(player_card); //add own card back 
            p2.add_card(ai_card);     //take ai card
            update_screen("PLAYER TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false); //display
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //add extra sleep
          
        }else if(player_card.value < ai_card.value){ //IF AI HAS A GREATER CARD VALUE 
            p1.add_card(player_card); //take player card
            p1.add_card(ai_card);     //add own card back 
            update_screen("AI TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false); //display
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //add extra sleep

        }else{ //IF THE CARDS ARE THE SAME VALUE!!!!!!!!!!!!!!!!!!!!!!!!
            
            //WAR

            while(player_card.value == ai_card.value){ //While there is a war (accounts for double war)
       
	   			/* The following outputs text and sleeps------------------------------------------------*/
	            cout<<"P1 - ...\n"; //output                                                             |
	            std::this_thread::sleep_for(std::chrono::milliseconds(900)); //sleep                     |
	            cout<<"P2 - What's this?\n"; //o                                                         | 
	            std::this_thread::sleep_for(std::chrono::milliseconds(900)); //s                         |
	            cout<<"P1 - I think...\n";  //o                                                          |
	            std::this_thread::sleep_for(std::chrono::milliseconds(900)); //s                         |
	            if(WAR_cards_from_p1.size() > 0){ //WE CHECK IF THIS IS A DOUBLE/TRIBLE/ETC. WAR         |
	            	cout<<"P2 - Not again?!?!\n"; //extra output                                         |
	            	std::this_thread::sleep_for(std::chrono::milliseconds(900)); //s                     | 
				}                                                                                      //|
	            cout<<"WAR!!!!!!!!\n"; //o                                                               |
	            std::this_thread::sleep_for(std::chrono::milliseconds(2500)); //s                        |
	            cout<<newpage; //clear screen                                                            |
				//---------------------------------------------------------------------------------------


				update_screen("WAR", p1.num_cards(), p2.num_cards(), true, ai_card, player_card, false); //display "WAR"
				cout<<"What do you want to do? Enter the char 'p' to play cards, 'q' to quit the match\n> "; //ask
				cin>>in_game_options; //get
				while(in_game_options != 'p' && in_game_options != 'q'){ //err check 
					cout<<"Bad input... Try again\n> "; //err msg
					cin>>in_game_options; //get again
				}
				
				update_screen("About to play cards (2 face down, 1 up) ...", p1.num_cards(), p2.num_cards(), false, {}, {}, true); //display
       			std::this_thread::sleep_for(std::chrono::milliseconds(900)); //add extra sleep 

                //IF YOU DO NOT HAVE ENOUGH CARDS (under 3), YOU LOSE ---------------------------------------------------------------
                if(p1.num_cards() < 3){ //if ai not enough                                                                           |
                	update_screen("AI DOES NOT HAVE ENOUGH CARDS", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display  |
                	std::this_thread::sleep_for(std::chrono::milliseconds(900)); //sleep                                             |
                	update_screen("YOU AUTOMATICALLY WIN", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display          |
                	std::this_thread::sleep_for(std::chrono::milliseconds(900)); //sleep                                             |
                	for(int left_over = 0; left_over < p1.num_cards(); ++left_over){  //go through anything remaining                |
                		p1.cards.pop(); //remove from queue                                                                          |
					}                                                                                                              //|
                	enough_cards = false; //change boolean                                                                           |
                	break; //get out of loop                                                                                         |
				}                                                                                                                  //|
				if(p2.num_cards() < 3){ //if you not enough                                                                          |
					update_screen("YOU DO NOT HAVE ENOUGH CARDS", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display   |
					std::this_thread::sleep_for(std::chrono::milliseconds(900)); //sleep                                             |
                	update_screen("AI AUTOMATICALLY WINS", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display          |
                	std::this_thread::sleep_for(std::chrono::milliseconds(900)); //sleep                                             |
                	for(int left_over = 0; left_over < p2.num_cards(); ++left_over){ //go through anything remaining                 |
                		p2.cards.pop(); //remove from queue                                                                          |
					}                                                                                                              //|
                	enough_cards = false; //change bool                                                                              |
                	break; //get out of loop                                                                                         |
				}                                                                                                                  //|
				//------------------------------------------------------------------------------------------------------------------
				
				WAR_cards_from_p1.push_back(p1.play_card()); //play face down card & save
				WAR_cards_from_p1.push_back(p1.play_card()); //play face down card & save
				WAR_cards_from_p2.push_back(p2.play_card()); //play face down card & save
				WAR_cards_from_p2.push_back(p2.play_card()); //play face down card & save 

                player_card = p2.play_card(); //play face up card
                ai_card = p1.play_card();     //play face up card

                WAR_cards_from_p1.push_back(ai_card);     //save face up card
                WAR_cards_from_p2.push_back(player_card); //save face up card
                
				//Pretend to play two cards, then play third (display) -------------------------------------------------------
				update_screen("...", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display                        |
				update_screen("...", p1.num_cards(), p2.num_cards(), false, {}, {}, true);  //display                        |
				update_screen("...", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display                        |
				update_screen("...", p1.num_cards(), p2.num_cards(), false, {}, {}, false); //display                        |
                update_screen("Cards played", p1.num_cards(), p2.num_cards(), true, ai_card, player_card, false); //display  |
        		std::this_thread::sleep_for(std::chrono::milliseconds(1500)); //add extra sleep                              |
				//------------------------------------------------------------------------------------------------------------
            }
            
            if(enough_cards){ //If war was successful reveal all the cards
            	cout<<background2<<deep_blue<<"THE REVEAL"<<reset<<"\n"; //output
            	cout<<background2<<deep_blue<<"ALL THE CARDS PLAYED BY THE AI WERE..."<<reset<<"\n"; //output
                for(card c: WAR_cards_from_p1){ //for each ai card
                	cout<<"\t"<<c.suit<<" "; //output suit
                	if(c.value < 11){ //if 2-10
                		cout<<c.value; //output 
					}else if(c.value = 11){ //if jack
						cout<<"J"; //output 
					}else if(c.value == 12){ //if queen
						cout<<"Q"; //output 
					}else if(c.value == 13){ //if king 
						cout<<"K"; //output 
					}else if(c.value == 14){ //if ace 
						cout<<"A"; //output 
					}else{ //if joker 
						cout<<"JOKER";
					}
					cout<<"\n"; //newline 
				}
				cout<<background2<<deep_blue<<"ALL THE CARDS PLAYED BY YOU WERE..."<<reset<<"\n"; //output
				for(card c: WAR_cards_from_p2){ //for each player card
                	cout<<"\t"<<c.suit<<" ";
                	if(c.value < 11){ //if 2-10
                		cout<<c.value; //output 
					}else if(c.value = 11){ //if jack
						cout<<"J"; //output 
					}else if(c.value == 12){ //if queen
						cout<<"Q"; //output 
					}else if(c.value == 13){ //if king 
						cout<<"K"; //output 
					}else if(c.value == 14){ //if ace 
						cout<<"A"; //output 
					}else{ //if joker 
						cout<<"JOKER";
					}
					cout<<"\n"; //new line 
				}
				cout<<light_purple<<"(wait 8.7 seconds for this to close...)"<<reset<<"\n"; //output
				std::this_thread::sleep_for(std::chrono::milliseconds(8700)); //sleep
			}

            //NOW THAT WE HAVE DEALT WITH THE WAR WE ACT LIKE NORMAL
            if(player_card.value > ai_card.value && enough_cards){ //if player value is > 
                for(card c : WAR_cards_from_p1){ //for each ai card played
                	p2.add_card(c); //add them 
				}
				for(card c : WAR_cards_from_p2){ //for each player card played
                	p2.add_card(c); //add them 
				}
                update_screen("AI TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false); //display
            	std::this_thread::sleep_for(std::chrono::milliseconds(1000));//add extra sleep 

            }else if(player_card.value < ai_card.value && enough_cards){ //if player value is < 
                for(card c : WAR_cards_from_p1){ //for each card ai played
                	p1.add_card(c); //add them
				}
				for(card c : WAR_cards_from_p2){ //for each player card played 
                	p1.add_card(c); //add them 
				}
                update_screen("PLAYER TAKES CARDS", p1.num_cards(), p2.num_cards(), false, ai_card, player_card, false); //display
            	std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //add extra sleep 
            }
           

        }

    }

	cout<<newpage; //clear screen
	
	if(p1.num_cards() == 0 && in_game_options != 'q'){ //you win 
		display_win(); //ascii 
		cout<<"Please wait 5 seconds while the game resets...\n"; //output 
		std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //sleep
	}else if(in_game_options != 'q'){ //ai wins 
		display_lost(); //ascii
		cout<<"Please wait 5 seconds while the game resets...\n"; //output 
		std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //sleep	
	}

}

//-----------------------------------------------------------------------------------