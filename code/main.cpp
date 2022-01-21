#include<iostream>
//#include"src/header/ChessBoard.h"
//#include"ChessBoard.h"

#include"Game.h"

using namespace std;


int main(int argc, char** argv) {
    
    
    if(argc < 2) {
        std::cout << "Missing arguments\n";
        return 0;
    }
    else if(argc > 2) {
        std::cout << "Too many arguments\n";
        return 0;
    }

    string argument = argv[1];
    
    GameType type;
    if(argument.compare("pc") == 0)
       type = GameType::HumanVsPc;
    else if(argument.compare("cc") == 0)
       type = GameType::PcVsPc;
    else {
        std::cout << "Wrong argument\n";
        return 0;
    }
    Game game{type};

    game.play();
}