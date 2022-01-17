#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

using std::unique_ptr;

class Queen : public ChessPiece{
    private:

        /*
        ** Add to @legalMoves set all the possible movement in a specified direction
        **
        ** Dir:
        **  1 - up
        **  2 - up - right
        **  3 - right
        **  4 - down - right
        **  5 - down
        **  6 - down - left
        **  7 - left
        **  8 - up - left
        ** Use the @board to check the new position 
        */
        void addLegalMoves(int dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece>[8][8]) const;

    public:

        /*
        ** Constructor will call the base class, ChessPiece constructor
        ** and set the role of the piece
        */
        Queen(int row, int column, Side sidePiece);

        /*
        ** Change the current position of this piece on the board
        */
        void setPosition(int _row, int _col) override;

        /* 
        ** Return all the possible movements of the piece
        ** following his rules
        */
        std::set<std::pair<int, int>> getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const override;

        /*
        ** Get a movement from specified the end position 
        ** and simply return true if the piece can do this movement
        ** otherwise if the piece is not allow to move in the specified position return false
        */
        Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
};

#endif
