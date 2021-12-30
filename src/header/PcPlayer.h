#ifndef PCPLAYER_H
#define PCPLAYER_H

#include"Player.h"

class PcPlayer : public Player {
        
    public:

      PcPlayer();
      std::pair<std::pair<int, int>, std::pair<int, int>> getMove() const override;

};

#endif 
