#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "ChessBoard.h"


/*
    Index of contents:
        > Section 1 - Utility methods---------------
            ~ addToPieceList()
            ~ nOfPieces()
            ~ notToString()
            ~ getPossiblemovements()
            ~ copyPiece()    [static]

        > Section 2 - Constructors & operators------
            ~ ChessBoard() [constructor]
            ~ ChessBoard() [copy constructor]
            ~ ChessBoard() [move constructor]
            ~ operator=()

        > Section 3 - Special moves & situations----
            ~ isCheck()
            ~ isCheckMate()
            ~ isStaleMate()
            ~ promotion()

        

*/




/*--------------------------- Section 1 - Utility methods ----------------------------------------*/


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::addToPieceList(const shared_ptr<ChessPiece> piece, const side sid){
    if(sid == side::black)
        black.push_back(piece);
    else
        white.push_back(piece);
}


//returns the number of piece on the chessboard
int ChessBoard::nOfPieces(side c) const{
    return white.size() + black.size();
}


//returns a string containing the board disposition
std::string ChessBoard::notToString() const{
    std::string res;

    for(int i=0; i<SIZE; i++){
        res += std::to_string(SIZE-i) + " ";
        for(int j=0; j<SIZE; j++){
            if(chessBoard[i][j]->getSide() == side::black)
                res += static_cast<char>(chessBoard[i][j]->getRole());
            else
                res += std::tolower(static_cast<char>(chessBoard[i][j]->getRole()));
        }
        res += "\n";
    }
    for(int i=0; i<SIZE; i++){
        res += 'A'+i;
    }
    res += "\n";
}


//returns possible movements from a specific chesspiece,
//the returned set is empty if there isn't any piece or if there are no possible moves
set<std::pair<int, int>>& ChessBoard::getPossiblemovements(int _row, int _col) const{
     
}





//static method to get copy of a piece
shared_ptr<ChessPiece> ChessBoard::copyPiece(const shared_ptr<ChessPiece> toCopy){
    switch(toCopy->getRole()){
        case role::king: {
            return shared_ptr<ChessPiece>(new King(*toCopy));
        }
        case role::queen: {
            return shared_ptr<ChessPiece>(new Queen(dynamic_cast<Queen&>(*toCopy)));
        }
        case role::bishop: {
            return shared_ptr<ChessPiece>(new Bishop(*toCopy));
        }
        case role::knight:{
            return shared_ptr<ChessPiece>(new Knight(*toCopy));
        }
        case role::tower:{
            return shared_ptr<ChessPiece>(new Tower(*toCopy));
        }
        case role::pawn:{
            return shared_ptr<ChessPiece>(new Pawn(*toCopy));
        }
        case role::dummy:{
            return shared_ptr<ChessPiece>(new Dummy());
        }

    }
}





/*--------------------------- Section 2 - Constructors & operators --------------------------------------*/


//constructor
ChessBoard::ChessBoard(){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            side thisSide = static_cast<side>(initial_colors[i][j]);
            switch (initial_roles[i][j]){
                case 'R': {
                    shared_ptr<ChessPiece> toAdd(new King(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    addToPieceList(toAdd, thisSide);
                    break;
                }
                case 'D': {
                    shared_ptr<ChessPiece> toAdd(new Queen(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    addToPieceList(toAdd, thisSide);
                    break;
                }
                case 'A': {
                    shared_ptr<ChessPiece> toAdd(new Bishop(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    addToPieceList(toAdd, thisSide);
                    break;
                }
                case 'C':{
                    shared_ptr<ChessPiece> toAdd(new Knight(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    addToPieceList(toAdd, thisSide);
                    break;
                }
                case 'T':{
                    shared_ptr<ChessPiece> toAdd(new Tower(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    addToPieceList(toAdd, thisSide);
                    break;
                }
                case 'P':{
                    shared_ptr<ChessPiece> toAdd(new Pawn(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    addToPieceList(toAdd, thisSide);
                    break;
                }
                case ' ':{
                    shared_ptr<ChessPiece> toAdd(new Dummy(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    break;
                }

                default:
                    ; //should I implement an exception?
            }
        }
    }
}


//copy constructor
ChessBoard::ChessBoard(const ChessBoard& o){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            shared_ptr<ChessPiece> toAdd(copyPiece(o.chessBoard[i][j]));
            chessBoard[i][j] = toAdd;
        }
    }
    for(const auto &i: o.black){
        black.push_back(i);
    }
    for(const auto &i: o.white){
        white.push_back(i);
    }
}


//move constructor
ChessBoard::ChessBoard(ChessBoard&& o){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            //chessBoard[i][j] = std::move(o.chessBoard[i][j]);
            chessBoard[i][j] = o.chessBoard[i][j];
            o.chessBoard[i][j] = nullptr;
        }
    }

    for(auto &i: o.black){      //copy and clear
        black.push_back(i);
    }
    o.black.clear();

    for(auto &i: o.white){
        white.push_back(i);
    }
    o.white.clear();
}


//equals operator, does a copy of the chessPiece objects
ChessBoard& ChessBoard::operator=(const ChessBoard& o){
    
    if(this == &o)
        return *this;
    
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            shared_ptr<ChessPiece> toAdd(copyPiece(o.chessBoard[i][j]));
            chessBoard[i][j] = toAdd;
        }
    }
    for(const auto &i: o.black){
        black.push_back(i);
    }
    for(const auto &i: o.white){
        white.push_back(i);
    }

    return *this;
}


/*--------------------------- Section 3 - Special moves & situations --------------------------------------*/


bool ChessBoard::isCheck() const{

}

bool ChessBoard::isCheckMate() const{

}

bool ChessBoard::isStaleMate() const{

}


//does a promotion
void ChessBoard::promotion(role r){

}








#endif