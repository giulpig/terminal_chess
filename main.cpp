#include<iostream>
//#include"src/header/ChessBoard.h"
//#include"ChessBoard.h"

#include"Game.h"

using namespace std;

int main(void) {
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

    Game game (GameType::PcVsPc);

    game.play();
}
