#ifndef PLAYER_H
#define PLAYER_H

#include<utility>
#include<vector>
#include<string>
#include"Enums.h"
#include"ManagePosition.h"

class Player {

    protected:
        Side side;
        PlayerType plType;
        
    public:

        Player(Side, PlayerType);  
        virtual std::pair<std::pair<int, int>, std::pair<int, int>> getMove() = 0;
        Side getSide() const;
        std::string getSideStr() const;
        PlayerType getType() const;
        //virtual set<pair<int, int>>getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const = 0;
        virtual char getPromotion() const = 0;

};


#endif 
