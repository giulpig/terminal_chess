/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

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

        /**
         * Return the side of the player
         */
        Side getSide() const;

        /**
         * Return a Stirng with the side of the player
         */
        std::string getSideStr() const;

        /**
         * Return the type, if human or pc
         */
        PlayerType getType() const;

        /**
         * Funcion that have to be override, 
         * return the character that represents the piece with 
         * which the player wants to make the promotion
         */
        virtual char getPromotion() const = 0;

};


#endif 
