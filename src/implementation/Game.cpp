#ifndef GAME_CPP
#define GAME_CPP

#include"Game.h"
#include<stdlib.h>

#include <chrono>
#include <ctime>
#include <sys/time.h>

//have to change this
using namespace std::chrono;

using std::pair;
using std::unique_ptr;
using std::vector;
using namespace mPos;



Game::Game(GameType _gType) : gType{_gType} {

    // Set the log
    std::string logName = getFileLogName();
    log = Log{logName};

    // Get a random seed for the srand fuction
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    
    srand(msecs_time);

    // Set to the players randomly the colors
    int randomColor = rand() % 2;
    Side side1 = randomColor == 0 ? Side::white : Side::black;
    Side side2 = randomColor != 0 ? Side::white : Side::black;

    std::string inputs;
    
    // Set the players in function of the gameType
    switch(gType) {
        case GameType::HumanVsPc:
            players[0] = unique_ptr<HumanPlayer>{new HumanPlayer(side1)};
            break;
        case GameType::PcVsPc:
            players[0] = unique_ptr<PcPlayer>{new PcPlayer(board, side1)};
            setMaxMoves();
            break;

        //To be removed
        //case GameType::HumanVsHuman:
            //players[0] = unique_ptr<HumanPlayer>{new HumanPlayer(side1)};
            //players[1] = unique_ptr<HumanPlayer>{new HumanPlayer(side2)};
            //break;
    }

    //to be removede this if
    //if(gType != GameType::HumanVsHuman)
    players[1] = unique_ptr<PcPlayer>{new PcPlayer(board, side2)};
}

std::string Game::getFileLogName() {
    std::string input;
    std::cout << "Inserisci il nome del log (lascia vuoto per nome standard = 'logGame.txt')" <<std::endl;
    std::getline(std::cin, input);
    return  input.empty() ? "gameLog" : input;
}

void Game::setMaxMoves() {
    std::string input;
    std::cout << "Imposta il numero massimo di mosse (lascia vuoto per 50 mosse)" <<std::endl;
    bool validInput; 
    do {
        std::getline(std::cin, input);

        try {
            maxMovesPc = input.empty() ? 50 : stoi(input);
            validInput = true;
        } catch(std::invalid_argument e) {
            validInput = false;
        }
    } while(!validInput);
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
    // Pair used to understand if the human player want to seen the board or quit the game
    pair<pair<int, int>, pair<int, int>> printPair = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
    pair<pair<int, int>, pair<int, int>> quitGame = std::make_pair(std::make_pair(-2, -2), std::make_pair(-2, -2));

    Moves moveType;
    int playerTurn = 0;
    int countMoves = 0;
    char promotioChar;

    // Print the initial chessBoard
    printChessBoard();

    // Loop until there is a 'flap', someone win or the pc players have reached up the max moves
    while(!endGame && countMoves <= maxMovesPc) {

        // Loop until a right movement is selected
        do {

            // Print that it's the turn of a player only if it is human
            if(players[playerTurn] -> getType() == PlayerType::human)
                std::cout << "Type a movement player " << players[playerTurn] -> getSideStr() <<std::endl;

            // Get the movement from the player, the pointer of the player will manage id human or pc
            movement = players[playerTurn] -> getMove();

            if(movement == printPair) {
                printChessBoard();
                moveType = Moves::NaM;
                continue;
            } else if(movement == quitGame) {
                moveType = Moves::NaM;
                endGame = true; 
                break;
            }

            // Try to do the selected movement of the player and the the response of the type of movement
            moveType = board.move(movement.first, movement.second, players[playerTurn] -> getSide());

            // If NotAMovement and the player is human
            if(moveType == Moves::NaM && players[playerTurn] -> getType() == PlayerType::human)
                std::cout << "Illegal Movement! \n\n";
            // If the movement is ok and it is done by a computer than print the movement
            else if(moveType != Moves::NaM  && players[playerTurn] -> getType() == PlayerType::pc)
                std::cout << reConvertPos(movement) << "\n\n";

        } while(moveType == Moves::NaM);

        // Promotion could make a check so I have to redo the switch
        bool promotionMovement = false;
        while(!promotionMovement) {
            // Manage the type of movement
            switch(moveType) {
                case Moves::promotion: 

                    // If promotion then I have to get the piece
                    promotioChar = players[playerTurn] -> getPromotion();

                    // Make the promotion and then receive what the promotion did
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
        
        // Advance to the other player
        playerTurn = playerTurn + 1 >= 2 ? 0 : playerTurn + 1;
        //playerTurn++;
        //if(playerTurn >= 2)
            //playerTurn = 0;

        if(gType == GameType::PcVsPc)
            countMoves++;        

        // Log the movement
        log.logMove(moveType, movement, {1, promotioChar});
    }

    if(gType == GameType::PcVsPc && countMoves >= maxMovesPc)
        std::cout << "Numero massimo di mosse raggiunta" <<std::endl;

    std::cout << "Finito IL GAME" <<std::endl;
}

void Game::printChessBoard() {
    std::cout << std::endl;
    std::cout << board.notToString() << std::endl;
    std::cout << std::endl;
}

#endif

