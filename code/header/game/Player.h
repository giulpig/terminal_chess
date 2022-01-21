#ifndef PLAYER_H
#define PLAYER_H

#include<utility>
#include<vector>
#include<string>
#include"Enums.h"
#include"ManagePosition.h"

class Player {

    protected:
        // Store the side of the player
        Side side;

        // Store his type, it could be Pc or Human
        PlayerType plType;
        
    public:

        /**
         * The constructor initially will only set the side and the type
         */
        Player(Side, PlayerType);  

        /**
         * This funtion will return the movement selected from the player,
         * it will be override 
         */
        virtual std::pair<std::pair<int, int>, std::pair<int, int>> getMove() = 0;
        Side getSide() const;
        std::string getSideStr() const;
        PlayerType getType() const;
        //virtual set<pair<int, int>>getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const = 0;
        virtual char getPromotion() const = 0;

};


#endif 
