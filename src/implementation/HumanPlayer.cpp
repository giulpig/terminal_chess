#ifndef HUMANPLAYER_CPP
#define HUMANPLAYER_CPP

#include"HumanPlayer.h"

using std::pair;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;

HumanPlayer::HumanPlayer(Side side) : Player{side, PlayerType::human} {};


pair<pair<int, int>, pair<int, int>> HumanPlayer::getMove() const {

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

#endif 
