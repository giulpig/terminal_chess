#ifndef PLAYER_H
#define PLAYER_H

#include<utility>
#include<vector>
#include<string>
#include"Enums.h"

class Player {

    protected:
        Side side;
        PlayerType plType;
        std::pair<int, int> convertPos(std::string) const;
        
    public:

        Player(Side, PlayerType);  
        virtual std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const = 0;
        Side getSide() const;
        std::string getSideStr() const;
        PlayerType getType() const;
        //virtual set<pair<int, int>>getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const = 0;
        virtual char getPromotion();

};

std::string reConvertPos(std::pair<std::pair<int, int>, std::pair<int, int>>);

#endif 
