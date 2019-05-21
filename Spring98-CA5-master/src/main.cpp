#include "Game.h"
#include<iostream>

using namespace std;

int main(int argc, char* argv[]) {
    string map_name;
    if (argc < 2)
        map_name = "../assets/maps/1.txt";
    else
        map_name = argv[1];
    Game game;
    game.run_level(map_name);
}
