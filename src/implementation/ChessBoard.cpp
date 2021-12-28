#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "../header/ChessBoard.h"
//temp
#include <iostream>

/*
    Index of contents:
        > Section 1 - Utility methods---------------
            ~ move()
            ~ addToPieceList()
            ~ swapPointers()
            ~ nOfPieces()
            ~ notToString()
            ~ getPossiblemovements()
            ~ getPossiblemovementsByIndex()
            ~ copyPiece()    [static]
../header/
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


//changes pointers and returns the type of move that was done
Moves ChessBoard::doMove(pair<int, int> from, pair<int, int> to){
    //TODO verifica della mossa piu' successivo scambio
    chessBoard[from.first][from.second] -> setPosition(to.first, to.second);
    //TODO: Arrocco?
    //TODO: Modifica variabile del pedone
    //TODO: should we have a "eaten" container?

    //TODO: dummy is always the same
    //sould I delete the shared pointer??
    chessBoard[to.first][to.second] = chessBoard[from.first][from.second];
    shared_ptr<ChessPiece> newDummy(new Dummy());
    chessBoard[from.first][from.second] = newDummy;
    

}


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::addToPieceList(const shared_ptr<ChessPiece> piece, const Side sid){
    if(sid == Side::black)
        black.push_back(piece);
    else
        white.push_back(piece);
}


//returns the number of piece on the chessboard
int ChessBoard::nOfPieces(Side c) const{
    return white.size() + black.size();
}


//returns a string containing the board disposition
std::string ChessBoard::notToString() const{
    std::string res;

    for(int i=0; i<SIZE; i++){
        res += std::to_string(SIZE-i) + " ";
        for(int j=0; j<SIZE; j++){
            if(chessBoard[i][j]->getSide() == Side::black)
                res += static_cast<char>(chessBoard[i][j]->getRole());
            else
                res += std::tolower(static_cast<char>(chessBoard[i][j]->getRole()));
        }
        res += "\n";
    }
    res += "  ";
    for(int i=0; i<SIZE; i++){
        res += 'A'+i;
    }
    res += "\n";
    return res;
}


//returns possible movements from a specific chesspiece,
//the returned set is empty if there isn't any piece or if there are no possible moves
set<std::pair<int, int>> ChessBoard::getPossiblemovements(int row, int col) const{

    std::set<std::pair<int, int>> ret = chessBoard[row][col]->getLegalMoves(chessBoard);

    for(auto &i: ret){
        //TODO not possible remove pair from ret
        //maybe create a new set with the effectivly legal moves
        //TODO: you can't put yourself in a check position
        if(false){
            ret.erase(i);
        }
    }

    return ret;
}


//returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side,
//the returned set is empty if there isn't any piece or if there are no possible moves
set<std::pair<int, int>> ChessBoard::getPossiblemovementsByIndex(int index, Side thisSide) const{
    switch(thisSide){
        case Side::black:
            return getPossiblemovements(black[index]->getRow(), black[index]->getCol());
        break;
        case Side::white:
            return getPossiblemovements(white[index]->getRow(), white[index]->getCol());
        break;
    }
}



//static method to get copy of a piece
shared_ptr<ChessPiece> ChessBoard::copyPiece(const shared_ptr<ChessPiece> toCopy){
    switch(toCopy->getRole()){
        case Role::king: {
            return shared_ptr<ChessPiece>(new King(dynamic_cast<King&>(*toCopy)));
        }
        case Role::queen: {
            return shared_ptr<ChessPiece>(new Queen(dynamic_cast<Queen&>(*toCopy)));
        }
        case Role::bishop: {
            return shared_ptr<ChessPiece>(new Bishop(dynamic_cast<Bishop&>(*toCopy)));
        }
        case Role::knight:{
            return shared_ptr<ChessPiece>(new Knight(dynamic_cast<Knight&>(*toCopy)));
        }
        case Role::tower:{
            return shared_ptr<ChessPiece>(new Tower(dynamic_cast<Tower&>(*toCopy)));
        }
        case Role::pawn:{
            return shared_ptr<ChessPiece>(new Pawn(dynamic_cast<Pawn&>(*toCopy)));
        }
        case Role::dummy:{
            return shared_ptr<ChessPiece>(new Dummy());
        }

    }
}





/*--------------------------- Section 2 - Constructors & operators --------------------------------------*/


//constructor
ChessBoard::ChessBoard(){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            Side thisSide = static_cast<Side>(initial_colors[i][j]);
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
                    shared_ptr<ChessPiece> toAdd(new Dummy());
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
void ChessBoard::promotion(Role r){

}








#endif