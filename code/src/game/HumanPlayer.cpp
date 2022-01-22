/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef HUMANPLAYER_CPP
#define HUMANPLAYER_CPP

#include"HumanPlayer.h"

using std::pair;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;

using namespace mPos;

HumanPlayer::HumanPlayer(Side side) : Player{side, PlayerType::human} {};

pair<pair<int, int>, pair<int, int>> HumanPlayer::getMove() {

  pair<pair<int, int>, pair<int, int>> movement;
  string line;
  // Use three strings to obtain also all the text that could
  // be after a proper input, if there is something than invalidate the input
  vector<string> pos {3};
  bool rightInput = true;
  
  do {
    pos = vector<string>{3};

    if(!rightInput)
      std::cout << "\nInput Invalido!\n" <<std::endl;

    // Get all the line of the input
    getline(std::cin, line);

    // Check some prefix line, one is to print the board and one is to quit the game
    // Return a specific pair so the Game class can understand what the player wants to do
    if(line == "XX XX")
      return {{-1, -1}, {-1, -1}};
    else if(line == "QQ QQ")
      return {{-2, -2}, {-2, -2}};

    // Scan all the input, divide into blocks anc make it uppercase
    // Doing this conversion will allow to accept uppercase 
    // or lowercase input and at the same time simplify the conversion
    stringstream inStream (line);
    for(int i = 0; i < 2; i++) {
      inStream >> pos[i];

      for(char& c : pos[i])
        c = std::toupper(c);

      // Validate an input position
      if(!isValidInput(pos[i])) {
        rightInput = false;
        break;
      }
      else
        rightInput = true;
    }

    // Test if there other text on the line
    inStream >> pos[2];
    if(pos[2].size() != 0)
      rightInput = false;

  } while(!rightInput);

  // Convert from string to pair for the ChessBoard class
  movement.first = convertPos(pos[0]);
  movement.second = convertPos(pos[1]);

  std::cout <<std::endl;

  return movement;
}



char HumanPlayer::getPromotion() const {  
  string line;

  // Check input
  do {

      std::cout << "Seleziona il pezzo: \n T - Torre \n D - Regina\n C - Cavallo\n A - Alfiere\n";
      getline(std::cin, line);

      if(line.size() != 1)
        continue;
        
      line[0] = std::toupper(line[0]);

      if(line[0] == 'P')
        std::cout << "Veramente??\n";

  } while(line[0] != 'T' && line[0] != 'D' && line[0] != 'C' && line[0] != 'B');

  return line[0];
}
#endif 
