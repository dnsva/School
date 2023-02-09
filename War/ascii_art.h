
#include <iostream>
#include <string>

using std::cout;

//misc ascii art
#define reset "\033[0m"


#define newpage "\033[2J"
#define setblinking "\033[25m"

//COLOURS

//FOREGROUND
#define light_purple "\033[38;5;189m"
#define deep_blue "\033[38;5;21m"
#define orange "\033[38;5;167m"
#define magenta "\033[38;5;52m"

//BACKGROUND
#define skin_tone "\033[48;5;223m"
#define background "\033[48;5;153m"
#define background2 "\033[48;5;214m"
#define card_back "\033[48;5;124m"
#define card_front "\033[48;5;218m"
#define border "\033[48;5;195m"

void display_title(){
    cout<<orange;
    cout<<" █     █░ ▄▄▄       ██▀███   \n";
    cout<<"▓█░ █ ░█░▒████▄    ▓██ ▒ ██▒ \n";
    cout<<"▒█░ █ ░█ ▒██  ▀█▄  ▓██ ░▄█ ▒ \n";
    cout<<"░█░ █ ░█ ░██▄▄▄▄██ ▒██▀▀█▄   \n";
    cout<<"░░██▒██▓  ▓█   ▓██▒░██▓ ▒██▒ \n";
    cout<<"░ ▓░▒ ▒   ▒▒   ▓▒█░░ ▒▓ ░▒▓░ \n";
    cout<<"  ▒ ░ ░    ▒   ▒▒ ░  ░▒ ░ ▒░ \n";
    cout<<"  ░   ░    ░   ▒     ░░   ░  \n";
    cout<<"    ░          ░  ░   ░      \n";
}
