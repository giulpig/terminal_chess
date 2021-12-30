#ifndef HUMANPLAYER_CPP
#define HUMANPLAYER_CPP

#include"HumanPlayer.h"

using std::pair;
using std::string;
using std::getline;
using std::stringstream;

HumanPlayer::HumanPlayer() : Player{} {};

pair<pair<int, int>, pair<int, int>> HumanPlayer::getMove() const {

  pair<pair<int, int>, pair<int, int>> movement;
  string line, pos;

  getline(std::cin, line);
  stringstream inStream (line);
    
  while(getline(inStream, pos, ' ')) {
       
      //TODO get the position and convert it to int int with the Player class
      //
      //so get, convert and return
  }

}

#endif 
