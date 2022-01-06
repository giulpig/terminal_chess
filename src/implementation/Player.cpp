#ifndef PLAYER_CPP
#define PLAYER_CPP

#include"Player.h"

using std::pair;
using std::string;

Player::Player(Side _side, PlayerType _plType) : side{_side}, plType{_plType} {}

pair<int, int> Player::convertPos(std::string toConvert) const {

    pair<int, int> convertedPos;
    convertedPos.second = toConvert[0] - 65;
    convertedPos.first = 8 - (toConvert[1] - 48);

    return convertedPos;

}

Side Player::getSide() const {
    return side;
}

PlayerType Player::getType() const {
    return plType;
}

string Player::getSideStr() const {
    if(side == Side::noSide) return "";
    return side == Side::white ? "white " : "black";
}

std::string reConvertPos(pair<pair<int, int>, pair<int, int>> mov) {

    string st;
    st += (char) mov.first.second + 65;
    st += (char) mov.first.first + 48;
    st += ' ';
    st += (char) mov.second.second + 65;
    st += (char) mov.second.first + 48;

    return st;

}

#endif 
