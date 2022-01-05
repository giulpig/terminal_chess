#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include<iostream>
#include<sstream>
#include<algorithm>
#include"Player.h"
#include"Enums.h"

class HumanPlayer : public Player {

    private:
        bool isValidInput(std::string) const;
        
    public:
      HumanPlayer(Side);
      std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const override;

};

#endif 
