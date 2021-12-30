#ifndef PLAYER_H
#define PLAYER_H

class Player {
    protected:

        std::pair<int, int> convertPos(std::pair<char, int>) const;
        
    public:

        Player();  
        virtual std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const = 0;

};
#endif 
