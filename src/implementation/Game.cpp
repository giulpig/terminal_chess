#ifndef GAME_CPP
#define GAME_CPP

#include"Game.h"

Game::Game(GameType gType) {

    switch(gType) {
        case GameType::HumanVsPc:
            players[0] = HumanPlayer();
            break;
        case GameType::PcVsPc:
            players[0] = PcPlayer();
            break;
    }
    players[1] = PcPlayer();

    board = ChessBoard();
}

void Game::play() {

    bool endGame = false;
    pair<pair<int, int>, pair<int, int>> movement;
    Moves moveType;

    while(!endGame) {

        for(int i = 0; i < 2; ++i) {

            do {
                std::cout << "Type a movement player " << i << ": " <<std::endl;
                //maybe the PcPlayer could print the movement so seems like
                //the human player (when it write the move remain on the screen)
                movement = players[i].getMove();
                moveType = board.doMove(movement.first, movement.second);
            } while(moveType == Moves::NaM);
    
            switch(moveType) {
                case Moves::promotion:
                    break;
                // TODO add this to the enums so we can finish the game
                /*
                case WIN:
                   endGame = true; 
                   break;
                */
            }
        }

        printChessBoard();

        //TODO something for the log
    }
}

void Game::printChessBoard() {
    //space maybe usefull
    //but to make it clear they could be beautiful
    std::cout << std::endl;
    std::cout << board.notToString() << std::endl;
    std::cout << std::endl;
}

#endif

