/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef PLAYER_CPP
#define PLAYER_CPP

#include"Player.h"

using std::pair;
using std::string;

Player::Player(Side _side, PlayerType _plType) : side{_side}, plType{_plType} {}

Side Player::getSide() const {
    return side;
}

PlayerType Player::getType() const {
    return plType;
}

string Player::getSideStr() const {

    switch (side) {
        case Side::white:
            return "white";
            break;
        case Side::black:
            return "black";
            break;
        default:
            return "";
            break;
    }

}



#endif 
