#ifndef PLAYER_H
#define PLAYER_H

#include<utility>
#include<vector>
#include<string>

class Player {

    protected:

        std::pair<int, int> convertPos(std::string) const;
        
    public:

        Player();  
        virtual std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const = 0;
        //virtual set<pair<int, int>>getLegalMoves(const shared_ptr<ChessPiece>[8][8]) const = 0;

};
#endif 
