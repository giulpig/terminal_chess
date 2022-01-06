#ifndef HUMANPLAYER_CPP
#define HUMANPLAYER_CPP

#include"HumanPlayer.h"

using std::pair;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;

HumanPlayer::HumanPlayer(Side side) : Player{side, PlayerType::human} {};


pair<pair<int, int>, pair<int, int>> HumanPlayer::getMove() {

  pair<pair<int, int>, pair<int, int>> movement;
  string line;
  vector<string> pos {3};
  bool rightInput = true;
  
  do {
    pos = vector<string>{3};

    if(!rightInput)
      std::cout << "Invalid Input!" <<std::endl;

    getline(std::cin, line);

    //check XX XX
    if(line == "XX XX")
      return {{-1, -1}, {-1, -1}};

    stringstream inStream (line);
    for(int i = 0; i < 2; i++) {
      inStream >> pos[i];
      std::transform(pos[i].begin(), pos[i].end(), pos[i].begin(), ::toupper);


      if(!isValidInput(pos[i])) {
        rightInput = false;
        break;
      }
      else
        rightInput = true;
    }

    //remain of the line
    inStream >> pos[2];
    if(pos[2].size() != 0)
      rightInput = false;

  } while(!rightInput);

  movement.first = convertPos(pos[0]);
  movement.second = convertPos(pos[1]);

  return movement;
}

bool HumanPlayer::isValidInput(string pos) const {
  if(pos.size() != 2)
    return false;

  if(pos[0] < 65 || pos[0] > 73 || pos[1] < 48 || pos[1]> 56)
    return false;

  return true; 
}

char HumanPlayer::getPromotion() const {  
  string line;
  std::cout << "Select a new Piece: \n T - Rook \n D - Queen\n P - Pawn (but you can't do this)\n C - Knight\n A - Bishop\n";

  //check input
  do {
      getline(std::cin, line);
  } while(line.size() != 1 && (line[0] != 'T' && line[0] != 'D' && line[0] != 'C' && line[0] != 'B'));

  if(getSide() == Side::white)
      line[0] += 32;

  return side == Side::white ? line[0] + 32 : line[0];
}
#endif 
