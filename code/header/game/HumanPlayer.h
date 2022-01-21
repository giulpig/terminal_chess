/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include<iostream>
#include<sstream>
#include<algorithm>
#include<cctype>
#include"Player.h"
#include"Enums.h"

class HumanPlayer : public Player {
        
  public:

    HumanPlayer(Side);

    /**
     * Get the movement of the player from input stream
     * It will also validate the input and if the format is not ok
     * than reask the string
     */
    std::pair<std::pair<int, int>, std::pair<int, int>> getMove() override;

    /**
     * Ask to the player in witch piece want to do the promotion
     */
    char getPromotion() const;

};

#endif 
