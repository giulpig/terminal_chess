#ifndef HUMANPLAYER_CPP
#define HUMANPLAYER_CPP

#include"HumanPlayer.h"

using std::pair;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;

HumanPlayer::HumanPlayer() : Player{} {};

pair<pair<int, int>, pair<int, int>> HumanPlayer::getMove() const {

  pair<pair<int, int>, pair<int, int>> movement;
  string line;
  vector<string> pos {3};
  bool rightInput = true; 
  
  do {
    getline(std::cin, line);
    stringstream inStream (line);
    int i = 0;   
    while(getline(inStream, pos[i], ' ')) {

      if(!isValidInput(pos[i++])) {
        rightInput = false;
        break;
      }

    } 
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
