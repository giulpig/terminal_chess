#ifndef GAME_CPP
#define GAME_CPP

#include"Game.h"
#include<stdlib.h>

#include <chrono>
#include <ctime>
#include <sys/time.h>

using namespace std::chrono;
using std::pair;
using std::unique_ptr;
using std::vector;
using namespace mPos;

Game::Game(GameType _gType) : gType{_gType} {

    //maybe this could go in a separate function

    std::string inputs;
    std::cout << "Inserisci il nome del log (lascia vuoto per nome standard = 'logGame.txt')" <<std::endl;
    std::getline(std::cin, inputs);

    log = inputs.empty() ? Log("gameLog") : Log(inputs);

    // random
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    
    srand(msecs_time);

    int randomColor = rand() % 2;
    Side side1 = randomColor == 0 ? Side::white : Side::black;
    Side side2 = randomColor != 0 ? Side::white : Side::black;
    
    switch(gType) {
        case GameType::HumanVsPc:
            players[0] = unique_ptr<HumanPlayer>{new HumanPlayer(side1)};
            break;
        case GameType::PcVsPc:
            players[0] = unique_ptr<PcPlayer>{new PcPlayer(board, side1)};

            std::cout << "Imposta il numero massimo di mosse (lascia vuoto per 50 mosse)" <<std::endl;
            bool validInput; 
            do {
                std::getline(std::cin, inputs);

                try {
                    maxMovesPc = inputs.empty() ? 50 : stoi(inputs);
                    validInput = true;
                } catch(std::invalid_argument e) {
                    validInput = false;
                }

            } while(!validInput);

            break;
        //To be removed
        case GameType::HumanVsHuman:
            players[0] = unique_ptr<HumanPlayer>{new HumanPlayer(side1)};
            players[1] = unique_ptr<HumanPlayer>{new HumanPlayer(side2)};
            break;
    }

    //to be removede this if
    if(gType != GameType::HumanVsHuman)
        players[1] = unique_ptr<PcPlayer>{new PcPlayer(board, side2)};
}

/*
Game& Game::operator=(const Game& g) {
    gType = g.gType;
    // do not need to copy stuff, the vector will do everyting
    players = g.players;
    board = g.board;
    log = g.log();
    return *this;
}
*/

void Game::play() {

    bool endGame = false;
    pair<pair<int, int>, pair<int, int>> movement;
    pair<pair<int, int>, pair<int, int>> printPair = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
    pair<pair<int, int>, pair<int, int>> quitGame = std::make_pair(std::make_pair(-2, -2), std::make_pair(-2, -2));
    //pair<pair<int, int>, pair<int, int>> endGamePair = std::make_pair(std::make_pair(-2, -2), std::make_pair(-2, -2));
    Moves moveType;
    int playerTurn = 0;
    int countMoves = 0;
    char promotioChar;

    printChessBoard();
    while(!endGame && countMoves <= maxMovesPc) {

        do {

            if(players[playerTurn] -> getType() == PlayerType::human)
                std::cout << "Type a movement player " << players[playerTurn] -> getSideStr() <<std::endl;

            //maybe the PcPlayer could print the movement so seems like
            //the human player (when it write the move remain on the screen)

            // ADD TODO keyword to give up

            movement = players[playerTurn] -> getMove();

            if( movement == printPair) {
                printChessBoard();
                moveType = Moves::NaM;
                continue;
            } else if(movement == quitGame) {
                moveType = Moves::NaM;
                endGame = true; 
                break;
            }

            moveType = board.move(movement.first, movement.second, players[playerTurn] -> getSide());

            if(moveType == Moves::NaM && players[playerTurn] -> getType() == PlayerType::human)
                std::cout << "Illegal Movement! \n\n";
            else if(moveType != Moves::NaM  && players[playerTurn] -> getType() == PlayerType::pc)
                std::cout << reConvertPos(movement) << "\n\n";

        } while(moveType == Moves::NaM);

        bool promotionMovement = false;
        while(!promotionMovement) {
            switch(moveType) {
                case Moves::promotion: 

                    promotioChar = players[playerTurn] -> getPromotion();

                    moveType = board.promotion(static_cast<Role>(promotioChar));

                    if(moveType != Moves::movement)
                        promotionMovement = false;
                    else
                        promotionMovement = true;

                    break;
                case Moves::staleMate:
                    std::cout << "patta" <<std::endl;
                    endGame = true; 
                    promotionMovement = true;
                    break;
                case Moves::checkMate:
                    std::cout << "Player " << players[playerTurn] -> getSideStr() << "you win" <<std::endl;
                    endGame = true; 
                    promotionMovement = true;
                    break;
                default:
                    promotionMovement = true;
                    break;
            }
        }
        
        playerTurn++;
        if(playerTurn >= 2)
            playerTurn = 0;

        if(gType == GameType::PcVsPc){
            countMoves++;        
            //To be removed
            //printChessBoard();
        }

        //something for the log
        log.logMove(moveType, movement, {1, promotioChar});
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

