#ifndef GAME_CPP
#define GAME_CPP

#include"Game.h"
#include<stdlib.h>


Game::Game(GameType _gType) : gType{_gType}{

    //bard = ChessBoard{};

    // random 
    srand(0);            //For debug, it's best to set a seed
    
    int randomColor = rand() % 2;
    Side side1 = randomColor == 0 ? Side::white : Side::black;
    Side side2 = randomColor != 0 ? Side::white : Side::black;
    
    switch(gType) {
        case GameType::HumanVsPc:
            players[0] = std::unique_ptr<HumanPlayer>{new HumanPlayer(side1)};
            break;
        case GameType::PcVsPc:
            players[0] = std::unique_ptr<PcPlayer>{new PcPlayer(board, side1)};

            std::cout << "Imposta il numero massimo di mosse" <<std::endl;
            //TODO CHECK IF IS A NUMBER
            std::cin >> maxMovesPc;
            break;
    }

    players[1] = std::unique_ptr<PcPlayer>{new PcPlayer(board, side2)};
}

void Game::play() {

    bool endGame = false;
    pair<pair<int, int>, pair<int, int>> movement;
    pair<pair<int, int>, pair<int, int>> printPair = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
    Moves moveType;
    int playerTurn = 0;
    int countMoves = 0;

    printChessBoard();
    while(!endGame && countMoves <= maxMovesPc) {

        do {
            std::cout << "Type a movement player " << players[playerTurn] -> getSideStr() <<std::endl;
            //maybe the PcPlayer could print the movement so seems like
            //the human player (when it write the move remain on the screen)

            // ADD TODO keyword to give up

            movement = players[playerTurn] -> getMove();

            if( movement == printPair) {
                printChessBoard();
                moveType = Moves::NaM;
                continue;
            }

            moveType = board.move(movement.first, movement.second, players[playerTurn] -> getSide());

            if(moveType == Moves::NaM && players[playerTurn] -> getType() == PlayerType::human)
                std::cout << "Illegal Movement!" << std::endl;
            else if(moveType != Moves::NaM  && players[playerTurn] -> getType() == PlayerType::pc)
                std::cout << reConvertPos(movement) << std::endl;

        } while(moveType == Moves::NaM);
    
        switch(moveType) {
            //case Moves::promotion:

                //char promot = players[playerTurn] -> getPromotion();

                // maybe this not work
                //board.setPromotion(promot);

                //break;
            // TODO add this to the enums so we can finish the game
            case Moves::staleMate:
                std::cout << "patta" <<std::endl;
                break;
            case Moves::checkMate:
                std::cout << "Player " << players[playerTurn] -> getSideStr() << "you win" <<std::endl;
                endGame = true; 
                break;
        }
        

        //that function is totally usefull 
        //system("clear");
        //printChessBoard();
        
        playerTurn++;
        if(playerTurn >= 2)
            playerTurn = 0;

        if(gType == GameType::PcVsPc){
            countMoves++;        
            //To be removed
            printChessBoard();
        }

        //TODO something for the log
    }

    if(gType == GameType::PcVsPc && countMoves >= maxMovesPc)
        std::cout << "Numero massimo di mosse raggiunta" <<std::endl;

    std::cout << "Finito IL GAME" <<std::endl;
}

void Game::printChessBoard() {
    //space maybe usefull
    //but to make it clear they could be beautiful
    std::cout << std::endl;
    std::cout << board.notToString() << std::endl;
    std::cout << std::endl;
}

#endif

