//Artico Giovanni n. matr. 2000178
#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <utility>
#include <set>

#include "Enums.h"
#include "Exceptions.h"
#include <memory>

class ChessPiece{

private:
    std::pair<int, int> location;
    Side color;
    //used for special moves
    bool moved = false;

protected:
    Role rol;
    ChessPiece(int _row, int _col, Side s);
    //utility functions
    /*
    ** Check if the movement is inside of the board
    ** return true if it is, otherwise false
    */
    bool checkBoundaries(std::pair<int, int> pos) const;
    //Returns true if the space in [row_][col_] is free

    bool isDummy(const std::shared_ptr<ChessPiece>[8][8], int row_, int col_) const;

    //Returns true if the piece in [row_][col_] is of the opposite side;
    bool isOppositeSide(const std::shared_ptr<ChessPiece>[8][8], int row_, int col_) const;
public:

    ChessPiece(const ChessPiece&) = default;

    int getRow() const;
    int getCol() const;
    Role getRole() const;
    bool isMoved() const;
    Side getSide() const;
    std::pair<int, int> getPosition() const;

    //moves without validating the move
    virtual void setPosition(int _row, int _col) = 0;

    //returns legal moves not counting the possible autocheck
    virtual std::set<std::pair<int, int>>getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const = 0;
    
    //returns the type of move that they did
    virtual Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const = 0;
};

#endif