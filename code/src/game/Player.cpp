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
            return "bianco";
            break;
        case Side::black:
            return "nero";
            break;
        default:
            return "";
            break;
    }

}



#endif 
