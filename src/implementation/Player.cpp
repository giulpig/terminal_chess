#ifndef PLAYER_CPP
#define PLAYER_CPP

#include"Player.h"

using std::pair;

Player::Player() {}

pair<int, int> Player::convertPos(pair<char, int> toConvert) const {

    pair<int, int> convertedPos;
    convertedPos.first = (int)toConvert.first - 65;
    convertedPos.second = 8 - toConvert.second;

}


#endif 
