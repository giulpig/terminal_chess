#ifndef PLAYER_CPP
#define PLAYER_CPP

#include"Player.h"

using std::pair;

Player::Player() {}

pair<int, int> Player::convertPos(std::string toConvert) const {

    pair<int, int> convertedPos;
    convertedPos.second = toConvert[0] - 65;
    convertedPos.first = 8 - (toConvert[1] - 48);

}


#endif 
