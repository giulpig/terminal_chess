#ifndef ENUMS_CPP
#define ENUMS_CPP

enum class Side: bool{
    black = false,
    white = true
};

enum class Role: char{
    king   = 'R',
    queen  = 'D',
    bishop = 'A',
    tower  = 'T',
    knight = 'C',
    pawn   = 'P',
    dummy  = ' '
};

enum class Moves{
    NaM,
    movement,
    castling,
    promotion,
    enpassant
};

//for now add an enum for the type of play
enum class GameType {
    HumanVsPc,
    PcVsPc
};


#endif
