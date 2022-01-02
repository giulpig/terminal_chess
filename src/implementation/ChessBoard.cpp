#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "ChessBoard.h"
//temp
#include <iostream>

//TODO: modificare tutti i new a make_shared

/*
    Index of contents:
        > Section 1 - Utility methods---------------
            ~ move()
            ~ addToPieceList()
            ~ removeFromPieceList()
            ~ swapPointers()
            ~ nOfPieces()
            ~ notToString()
            ~ getPossiblemovements()
            ~ getPossiblemovementsByIndex()
            ~ getPosition()
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

Moves ChessBoard::move(pair<int, int> from, pair<int, int> to, Side side){

}


//changes pointers and returns the type of move that was done
void ChessBoard::doMove(pair<int, int> from, pair<int, int> to){
    //TODO: Arrocco?
    //TODO: should we have a "eaten" container?

    if((from.first==0 || from.first==SIZE-1) && chessBoard[from.first][from.second]->getRole() == Role::pawn){
        toPromote = chessBoard[from.first][from.second];
    }
    
    //update piece information
    chessBoard[from.first][from.second] -> setPosition(to.first, to.second);

    if(chessBoard[to.first][to.second]->getRole() != Role::dummy)
        removeFromPieceList(chessBoard[to.first][to.second]);

    //actually swap pointers
    chessBoard[to.first][to.second] = chessBoard[from.first][from.second];
    chessBoard[from.first][from.second] = oneDummyToRuleThemAll;

}


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::addToPieceList(const shared_ptr<ChessPiece> piece){
    if(piece->getSide() == Side::black){
        black.push_back(piece);
        return;
    }

    if(piece->getSide() == Side::white)
        white.push_back(piece);
    
    return;
}


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::removeFromPieceList(const shared_ptr<ChessPiece> piece){

    if(chessBoard[piece->getRow()][piece->getCol()]->getSide() == Side::black){
        for(auto it=black.begin(); it!=black.end(); it++){
            if(*it == chessBoard[piece->getRow()][piece->getCol()])
                black.erase(it);
                return;
        }
    }

   if(chessBoard[piece->getRow()][piece->getCol()]->getSide() == Side::white){
        for(auto it=white.begin(); it!=white.end(); it++){
            if(*it == chessBoard[piece->getRow()][piece->getCol()])
                white.erase(it);
                return;
        }
    }
}


//returns the number of piece on the chessboard, -1 if re
int ChessBoard::nOfPieces(Side side) const{
    if(side == Side::black)
        return black.size();

    else if(side == Side::white)
        return white.size();
    
    return -1;
}


//get position of the piece with index in the piece list of specific side
pair<int, int> ChessBoard::getPosition(int index, Side side) const{
    switch(side){
        case Side::black:
            if(index >= black.size())
                return {-1, -1};

            return {black[index]->getRow(), black[index]->getCol()};
        break;

        case Side::white:
            if(index >= white.size())
                return {-1, -1};
    
            return {white[index]->getRow(), white[index]->getCol()};
        break;
    }
    return {-1, -1};
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
set<pair<int, int>> ChessBoard::getPossiblemovementsByIndex(int index, Side side) const{
    switch(side){
        case Side::black:
            return getPossiblemovements(black[index]->getRow(), black[index]->getCol());
        break;
        case Side::white:
            return getPossiblemovements(white[index]->getRow(), white[index]->getCol());
        break;
    }
    return set<pair<int, int>>{};
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

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            Side side = static_cast<Side>(initial_colors[i][j]);
            Role role = static_cast<Role>(initial_roles[i][j]);
            shared_ptr<ChessPiece> toAdd = newPiece(i, j, side, role);
            chessBoard[i][j] = toAdd;
            if(toAdd->getRole() != Role::dummy)
                addToPieceList(toAdd);
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

    for(auto &i: o.black){      //copy pointers and clear
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
        char xcoord = -1;
        if(chessBoard[0][i]->getRole() == Role::pawn){
            xcoord = 0;
        }
        else if(chessBoard[SIZE-1][i]->getRole() == Role::pawn){
            xcoord = SIZE-1;
        }

        if(xcoord != -1){
            removeFromPieceList(chessBoard[xcoord][i]);
            chessBoard[xcoord][i] = newPiece(0, i, chessBoard[xcoord][i]->getSide(), role);
            break;
        }
        else{
            ;   //eccezzzzzzzzzione
        }
    }
}








#endif