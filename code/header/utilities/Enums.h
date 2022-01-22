//Artico Giovanni n.matr.200178
#ifndef ENUMS_CPP
#define ENUMS_CPP

enum class Side: char{
    black   =  0,
    white   =  1,
    noSide  = -1
};

enum class Role: char{
    king   = 'R',
    queen  = 'D',
    bishop = 'A',
    rook   = 'T',
    knight = 'C',
    pawn   = 'P',
    dummy  = ' '
};

enum class Move{
    NaM,
    movement,
    castling,
    promotion,
    doublePawn,
    enpassant,
    staleMate,
    checkMate
};

//for now add an enum for the type of play
enum class GameType {
    HumanVsPc,
    PcVsPc,
    HumanVsHuman
};


enum class PlayerType {
    pc,
    human
};


#endif
