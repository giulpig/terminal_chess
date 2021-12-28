#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "ChessBoard.h"
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
            ~ copyPiece()   [static]
            ~ newPiece()    [static]

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
    //TODO: Arrocco?
    //TODO: Modifica variabile del pedone
    //TODO: should we have a "eaten" container?

    if(chessBoard[from.first][from.second]->getRole() == Role::pawn){
        chessBoard[from.first][from.second]->isMoved();
    }
    
    chessBoard[from.first][from.second] -> setPosition(to.first, to.second);

    chessBoard[to.first][to.second] = chessBoard[from.first][from.second];
    chessBoard[from.first][from.second] = oneDummyToRuleThemAll;
    

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
        //OKKIO: not possible remove pair from ret, maybe create a new set
        //TODO: you can't put yourself in a check position
        if(false){
            ret.erase(i);
        }
    }

    return ret;
}


//returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side,
//the returned set is empty if there isn't any piece or if there are no possible moves
set<std::pair<int, int>> ChessBoard::getPossiblemovementsByIndex(int index, Side side) const{
    switch(side){
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
        case Role::king:
            return shared_ptr<ChessPiece>(new King(dynamic_cast<King&>(*toCopy)));

        case Role::queen:
            return shared_ptr<ChessPiece>(new Queen(dynamic_cast<Queen&>(*toCopy)));

        case Role::bishop:
            return shared_ptr<ChessPiece>(new Bishop(dynamic_cast<Bishop&>(*toCopy)));

        case Role::knight:
            return shared_ptr<ChessPiece>(new Knight(dynamic_cast<Knight&>(*toCopy)));

        case Role::tower:
            return shared_ptr<ChessPiece>(new Tower(dynamic_cast<Tower&>(*toCopy)));

        case Role::pawn:
            return shared_ptr<ChessPiece>(new Pawn(dynamic_cast<Pawn&>(*toCopy)));

        case Role::dummy:
            return shared_ptr<ChessPiece>(new Dummy());

        default:
            ;       //Exception?

    }

    return shared_ptr<ChessPiece>(nullptr);
}


//static method to get shared pointer of new ChessPiece
shared_ptr<ChessPiece> ChessBoard::newPiece(int row, int col, Side side, Role role){
    switch(role){
        case Role::king:
            return shared_ptr<ChessPiece>(new King(row, col, side));

        case Role::queen:
            return shared_ptr<ChessPiece>(new Queen(row, col, side));

        case Role::bishop:
            return shared_ptr<ChessPiece>(new Bishop(row, col, side));

        case Role::knight:
            return shared_ptr<ChessPiece>(new Knight(row, col, side));

        case Role::tower:
            return shared_ptr<ChessPiece>(new Tower(row, col, side));

        case Role::pawn:
            return shared_ptr<ChessPiece>(new Pawn(row, col, side));

        case Role::dummy:
            return shared_ptr<ChessPiece>(new Dummy());

        default:
            ;       //Exception?

    }

    return shared_ptr<ChessPiece>(nullptr);
}





/*--------------------------- Section 2 - Constructors & operators --------------------------------------*/


//constructor
ChessBoard::ChessBoard(){

    oneDummyToRuleThemAll = std::make_shared<Dummy>();

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            Side side = static_cast<Side>(initial_colors[i][j]);
            Role role = static_cast<Role>(initial_roles[i][j]);
            shared_ptr<ChessPiece> toAdd = newPiece(i, j, side, role);
            chessBoard[i][j] = toAdd;
            addToPieceList(toAdd, side);
        }
    }
}


//copy constructor
ChessBoard::ChessBoard(const ChessBoard& o){
    
    oneDummyToRuleThemAll = std::make_shared<Dummy>();

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


/*
TODO
bool ChessBoard::isCheck() const{

}

bool ChessBoard::isCheckMate() const{

}

bool ChessBoard::isStaleMate() const{

}
*/

//does a promotion
void ChessBoard::promotion(Role role){         //sould I get the position also?
    for(int i=0; i<SIZE; i++){
        if(chessBoard[0][i]->getRole() == Role::pawn){  
            //should I delete old object explicitly?
            chessBoard[0][i] = newPiece(0, i, chessBoard[0][i]->getSide(), role);
            break;
        }
        if(chessBoard[SIZE-1][i]->getRole() == Role::pawn){
            chessBoard[SIZE-1][i] = newPiece(0, i, chessBoard[SIZE-1][i]->getSide(), role);
            break;
        }
    }
}








#endif