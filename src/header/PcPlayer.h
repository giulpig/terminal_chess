#ifndef PCPLAYER_H
#define PCPLAYER_H

#include"Player.h"
#include"ChessBoard.h"

class PcPlayer : public Player {
    private:
      ChessBoard board;
      Side side;

    public:

      PcPlayer(const ChessBoard&, Side);
      std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const override;

};

#endif 
