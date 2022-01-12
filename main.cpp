#include<iostream>
//#include"src/header/ChessBoard.h"
//#include"ChessBoard.h"

#include"Game.h"

using namespace std;


int main(int argc, char** argv) {
    
    
    /*if(argc < 2) {
        std::cout << "Missing arguments\n";
        return 0;
    }
    else if(argc > 2) {
        std::cout << "Too many arguments\n";
        return 0;
    }

    string argument = argv[1];*/
    
    /*GameType type;
    if(argument.compare("pc") == 0)
       type = GameType::HumanVsPc;
    else if(argument.compare("cc") == 0)
       type = GameType::PcVsPc;
    else {
        std::cout << "Wrong argument\n";
        return 0;
    }*/
    Game game{GameType::PcVsPc};

    /*
    if(argument.compare("pc") == 0)
       game = Game(GameType::HumanVsPc);
    else if(argument.compare("cc") == 0)
       game = Game(GameType::PcVsPc);
    else {
        std::cout << "Wrong argument\n";
        return 0;
    }*/
    //game = Game(GameType::PcVsPc);

    game.play();
}

// TEST CODE, NOW USEFULL
    /*
    ChessBoard cb {};

    cout << cb.notToString() <<endl;
    //test pawn
    for (auto i : cb.getPossiblemovements(1,3))
        cout << i.first << " " << i.second <<endl;
    cout <<endl;

    cb.doMove({0, 4}, {4, 4});
    cout << cb.notToString() <<endl;
    //test King
    for (auto i : cb.getPossiblemovements(4,4))
        cout << i.first << " " << i.second <<endl;
    cout <<endl;

    cb.doMove({0, 0}, {4, 0});
    cout << cb.notToString() <<endl;
    //test King
    for (auto i : cb.getPossiblemovements(4,0))
        cout << i.first << " " << i.second <<endl;
    cout <<endl;


    cb.doMove({0, 2}, {4, 2});
    cout << cb.notToString() <<endl;
    //test bishop
    for (auto i : cb.getPossiblemovements(4,2))
        cout << i.first << " " << i.second <<endl;
    cout <<endl;


    cb.doMove({0, 3}, {3, 3});
    cout << cb.notToString() <<endl;
    //test Queen
    for (auto i : cb.getPossiblemovements(3,3))
        cout << i.first << " " << i.second <<endl;
    cout <<endl;


    cb.doMove({6, 2}, {5, 2});
    cout << cb.notToString() <<endl;
    //test Pawn Avversario
    for (auto i : cb.getPossiblemovements(5,2))
        cout << i.first << " " << i.second <<endl;
    cout <<endl;
    */

