/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef DIRECTIONALPIECES_H
#define DIRECTIONALPIECES_H

#include "ChessPiece.h"

class DirectionalPieces : public ChessPiece{
    protected:

        /**
         * Add to legalMoves set all the possible movement in a specified direction
         *
         * Use the @board to check the new position 
         */
        void addLegalMoves(std::pair<int, int> dir, std::set<std::pair<int, int>>& legalMoves, const std::shared_ptr<ChessPiece>[8][8]) const;

    public:

        /**
         * Constructor will call the base class, ChessPiece constructor
         * and set the role of the piece
         */
        DirectionalPieces(int row, int column, Side sidePiece, Role _role);

        /**
         * Change the current position of this piece on the board
         */
        void setPosition(int _row, int _col) override;

        /**
         * Get a movement from specified the end position 
         * and simply return true if the piece can do this movement
         * otherwise if the piece is not allow to move in the specified position return false
         */
        Move moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const override;
};

#endif