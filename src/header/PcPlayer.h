#ifndef PCPLAYER_H
#define PCPLAYER_H

#include"Player.h"
#include"ChessBoard.h"

constexpr char possPromotion[] = {'T','D','C','A'};

class PcPlayer : public Player {
    private:
      const ChessBoard& board;

    public:

      PcPlayer(const ChessBoard&, Side);
      std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const override;
      char getPromotion();

};

#endif 
