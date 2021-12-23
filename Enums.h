#ifndef ENUMS_CPP
#define ENUMS_CPP

enum class side{
    black, white
};

enum class role{
    king, queen, bishop, tower, knight, pawn, dummy
};
enum class move{
    NaM/*Not a Move*/, movement, castling, promotion, enpassant
};
#endif