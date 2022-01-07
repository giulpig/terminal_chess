#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include<iostream>
#include<sstream>
#include<algorithm>
#include"Player.h"
#include"Enums.h"

class HumanPlayer : public Player {

    private:
        
    public:
      HumanPlayer(Side);
      std::pair<std::pair<int, int>, std::pair<int, int>> getMove() override;
      char getPromotion() const;

};

#endif 
