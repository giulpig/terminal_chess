#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include<iostream>
#include<sstream>
#include"Player.h"

class HumanPlayer : public Player {
    public:
        
      HumanPlayer();
      std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const override;

};

#endif 
