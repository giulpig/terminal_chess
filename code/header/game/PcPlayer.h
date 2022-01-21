/**
 * Gabriele Miotti
 * 
 * N. Matricola : 2000165
 */

#ifndef PCPLAYER_H
#define PCPLAYER_H

#include"Player.h"
#include"ChessBoard.h"

// Store the possible character for the promotion
constexpr char possPromotion[] = {'T','D','C','A'};

class PcPlayer : public Player {

  private:
    // Store a reference to the board
    ChessBoard& board;

  public:

    PcPlayer(ChessBoard&, Side);

    /**
     * The pc player ask to the board the possible moves of a random piece
     * and take a radom movement from the set
     */
    std::pair<std::pair<int, int>, std::pair<int, int>> getMove() override;

    /**
     * Randomly select a character for the promotion
     */
    char getPromotion() const;

};

#endif 
