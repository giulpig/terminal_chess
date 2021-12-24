#ifndef ENUMS_CPP
#define ENUMS_CPP

enum class side: bool{
    black = false,
    white = true
};

enum class role: char{
    king   = 'R',
    queen  = 'D',
    bishop = 'A',
    tower  = 'T',
    knight = 'C',
    pawn   = 'P',
    dummy  = ' '
};

enum class move{
    NaM,
    movement,
    castling,
    promotion,
    enpassant
};

#endif