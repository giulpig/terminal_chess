/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef GAME_CPP
#define GAME_CPP

#include"Game.h"

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
        case GameType::HumanVsHuman:
            players[0] = unique_ptr<HumanPlayer>{new HumanPlayer(side1)};
            players[1] = unique_ptr<HumanPlayer>{new HumanPlayer(side2)};
            break;
    }

    //to be removede this if
    if(gType != GameType::HumanVsHuman)
        players[1] = unique_ptr<PcPlayer>{new PcPlayer(board, side2)};
}

std::string Game::getFileLogName() {
    std::string input;
    std::cout << "Inserisci il nome del log (lascia vuoto per nome standard = 'logGame')" <<std::endl;
    std::getline(std::cin, input);
    return  input.empty() ? "gameLog" : input;
}

void Game::setMaxMoves() {
    std::string input;
    std::cout << "Imposta il numero massimo di mosse (lascia vuoto per 50 mosse)" <<std::endl;
    bool validInput; 
    do {
        std::getline(std::cin, input);

        // If the user write something I have to check thath it is
        // a real number to use in the maxMoves variable
        try {
            maxMovesPc = input.empty() ? 50 : stoi(input);
            validInput = true;
        } catch(std::invalid_argument e) {
            validInput = false;
        }
    } while(!validInput);
}

void Game::play() {

    bool endGame = false;
    bool quitted = false;
    pair<pair<int, int>, pair<int, int>> movement;
    // Pair used to understand if the human player want to seen the board or quit the game
    pair<pair<int, int>, pair<int, int>> printPair = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
    pair<pair<int, int>, pair<int, int>> quitGame = std::make_pair(std::make_pair(-2, -2), std::make_pair(-2, -2));

    Moves moveType;

    int playerTurn = 0;
    // Check who is the white player
    playerTurn = players[0] -> getSide() == Side::white ? 0 : 1;

    int countMoves = 0;
    char promotioChar;

    // Print the initial chessBoard
    printChessBoard();

    std::cout << "Inizia a giocare!" << std::endl;
    std::cout << "Scrivi 'XX XX' per stampare la tavola da gioco \n";
    std::cout << "Scrivi 'QQ QQ' per abbandonare la partita \n\n";

    // Loop until there is a 'flap', someone win or the pc players have reached up the max moves
    while(!endGame && countMoves <= maxMovesPc) {

        // Loop until a right movement is selected
        do {

            // Print that it's the turn of a player only if it is human
            if(players[playerTurn] -> getType() == PlayerType::human)
                std::cout << "Seleziona una mossa giocatore: " << players[playerTurn] -> getSideStr() <<std::endl;

            // Get the movement from the player, the pointer of the player will manage id human or pc
            movement = players[playerTurn] -> getMove();

            if(movement == printPair) {
                printChessBoard();
                moveType = Moves::NaM;
                continue;
            } else if(movement == quitGame) {
                moveType = Moves::NaM;
                endGame = true; 
                quitted = true;
                break;
            }

            // Try to do the selected movement of the player and the the response of the type of movement
            moveType = board.move(movement.first, movement.second, players[playerTurn] -> getSide());

            // If NotAMovement and the player is human
            if(moveType == Moves::NaM && players[playerTurn] -> getType() == PlayerType::human)
                std::cout << "Mossa Illegale! \n\n";
            // If the movement is ok and it is done by a computer than print the movement
            else if(moveType != Moves::NaM  && players[playerTurn] -> getType() == PlayerType::pc) {
                std::cout << players[playerTurn] -> getSideStr() << " ha mosso: \n";
                std::cout << reConvertPos(movement) << "\n\n";
            }

        } while(moveType == Moves::NaM);

        // Promotion could make a check so I have to redo the switch
        bool promotionMovement = false;
        bool isPromotion = false;
        while(!promotionMovement) {
            // Manage the type of movement
            switch(moveType) {
                case Moves::promotion: 

                    isPromotion = true;

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
                    std::cout << "Patta" <<std::endl;
                    endGame = true; 
                    promotionMovement = true;
                    break;
                case Moves::checkMate:
                    std::cout << "Giocatore " << players[playerTurn] -> getSideStr() << " Hai Vinto!!" <<std::endl;
                    endGame = true; 
                    promotionMovement = true;
                    break;
                default:
                    promotionMovement = true;
                    break;
            }
        }
        
        // Log the movement
        promotioChar = players[playerTurn] -> getSide() == Side::white ? std::tolower(promotioChar) : promotioChar;

        moveType = isPromotion ? Moves::promotion : moveType;

        if(!quitted) {
            char p[] = {promotioChar};
            //log.logMove(moveType, movement, {1, promotioChar});
            log.logMove(moveType, movement, p);
        }

        // Advance to the other player
        playerTurn = playerTurn + 1 >= 2 ? 0 : playerTurn + 1;

        if(gType == GameType::PcVsPc)
            countMoves++;        
    }

    if(gType == GameType::PcVsPc && countMoves >= maxMovesPc)
        std::cout << "Numero massimo di mosse raggiunta" <<std::endl;
}

void Game::printChessBoard() {
    std::cout << std::endl;
    std::cout << board.notToString() << std::endl;
    std::cout << std::endl;
}

#endif

