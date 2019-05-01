#include <iostream>
#include <iomanip>
#include <string>
#include "battleship.h"
#include "console_game.h"
#include "human_player.h"
#include "slick_player.h"

using namespace bship;
using namespace std;

#define SLIDER_LEN 20


int main(){
    srand(time(NULL));

    string user_name;
    float diff = 0.2;
    char read = 't';
    
    cout << "Enter your name: ";
    getline(cin, user_name);
    cout << endl;

    // [=====| 0.9 |================]
    cout << "Welcome, " << user_name << ", you will be playing against a bot." << endl;
    cout << "Choose the difficulty with - and + keys and press SPACE:" << endl;
    cout << "(q to quit)" << endl;
    system("stty raw");
    while(read != ' ' && read != 'q'){
        cout << "\r[";
        int before = diff * SLIDER_LEN;
        for(int i=0; i<before; ++i) cout << "=";
        cout << "| " << fixed << setprecision(2) << diff << " |";
        for(int i=0; i<SLIDER_LEN-before; ++i) cout << "=";
        cout << "]    (0.00: random bot, 1.00: perfect player)  ";
        read = getchar();
        if(read == '-' && diff >= 0.05) diff -= 0.05;
        else if(read == '+' && diff <= 0.96) diff += 0.05;
        else if(read == 'q') { system("stty cooked"); cout << endl; return 1; }
        else cout << "     ";
    }

    system("stty cooked");

    slick_player *opp = new slick_player("Bot", diff);

    console_game game(
        10, 10,
        new human_player(user_name),
        opp,
        OM_PA
    );

    game.start();
    
    return 0;
}
