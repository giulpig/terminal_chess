#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "ChessBoard.h"

/*
    Index of contents:
        > Section 1 - Utility methods---------------
            ~ move()
            ~ isPossibleMove()
            ~ getPossiblemovements()
            ~ getPossiblemovementsByIndex()
            ~ doMove()              [private]
            ~ addToPieceList()      [private]
            ~ removeFromPieceList() [private]
            ~ getPieceList()        [private]
            ~ nOfPieces()
            ~ notToString()
            ~ getPosition()
            ~ copyPiece()      [static][private]
            ~ newPiece()       [static][private]
            ~ swapPieces()     [static][private]
            ~ otherSide()      [static]

        > Section 2 - Constructors & operators------
            ~ ChessBoard() [constructor]
            ~ ChessBoard() [copy constructor]
            ~ ChessBoard() [move constructor]
            ~ operator=()

        > Section 3 - Special moves & situations----
            ~ promotion()
            ~ doEnpassant()     [private]
            ~ doCastling()      [private]
*/


//TEMPPP
#include <iostream>

/*
TODO:

    >Whatch promotion (swap instead of delete)
    >Same thing castling


/*


/*--------------------------- Section 1 - Utility methods ----------------------------------------*/

Moves ChessBoard::move(const pair<int, int>& from, const pair<int, int>& to, Side side){

    shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];    //reference just to not screw...
    shared_ptr<ChessPiece>& toPiece = _chessBoard[to.first][to.second];          //...internal shared_ptr counter
    Side opponent = otherSide(fromPiece->getSide());
    Moves moveType = fromPiece->moveType(to.first, to.second, _chessBoard);
    shared_ptr<ChessPiece> newEnpassed = nullptr;
    
    if(!isPossibleMove(from, to, side)){
        return Moves::NaM;
    }


    //Check for special moves
    switch(moveType){

        case Moves::castling:
            if(!doCastling(to))
                return Moves::NaM;
            
            if(isStaleMate(opponent))
                return Moves::staleMate;

            //checkMate check, do-undo strategy for all pieces and all moves
            if(isCheck(opponent) && !arePossibleMoves(opponent)){
                return Moves::checkMate;
            }

            return Moves::castling;

        case Moves::promotion:
            _toPromote = _chessBoard[from.first][from.second];
        break;

        case Moves::enpassant:
            doEnpassant(from);  //doEmpassant just removes the other pawn, the move is done in doMove
        break;

        case Moves::doublePawn:
            if(side == Side::black)
                newEnpassed = fromPiece;
            else
                newEnpassed = fromPiece;
        break;

    }

    doMove(from, to);

    if(isStaleMate(opponent))
        return Moves::staleMate;

    //checkMate check, do-undo strategy for all pieces and all moves
    if(isCheck(opponent) && !arePossibleMoves(opponent)){
        return Moves::checkMate;
    }

    if(_toPromote != nullptr)
        return Moves::promotion;

    //overwrite prev double-moved pawn
    if(side == Side::black){
        if(_enpassedBlack != nullptr)
            std::dynamic_pointer_cast<Pawn>(_enpassedBlack)->cancelEnpassant();
        _enpassedBlack = newEnpassed;
    }
    else{
        if(_enpassedWhite != nullptr)
            std::dynamic_pointer_cast<Pawn>(_enpassedWhite)->cancelEnpassant();
        _enpassedWhite = newEnpassed;
    }

    return Moves::movement;
}


//checks if a legal move is actually possible to do
bool ChessBoard::isPossibleMove(const pair<int, int> &from, const pair<int, int> &to, Side s){
    
    const shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];    //reference just to not screw...
    const shared_ptr<ChessPiece>& toPiece = _chessBoard[to.first][to.second];          //...internal shared_ptr counter
    
    
    //You can't move other player's pieces
    if(fromPiece->getSide() != s)
        return false;

    //You can't eat a king
    if(toPiece->getRole() == Role::king)
        return false;

    //Check for legal moves
    set<pair<int,int>> legalMoves = fromPiece->getLegalMoves(_chessBoard);
    if(legalMoves.find(to) == legalMoves.end())
        return false;

    //You can't check yourself
    shared_ptr<ChessPiece> temp = _chessBoard[to.first][to.second];
    _chessBoard[to.first][to.second] = oneDummyToRuleThemAll;

    swapPieces(from, to);
    if(isCheck(s, _chessBoard, to)){
        swapPieces(from, to); //go back
        _chessBoard[to.first][to.second] = temp;
        return false;
    }
    swapPieces(from, to);   //go back
    _chessBoard[to.first][to.second] = temp;

    return true;
}



//returns possible movements from a specific chesspiece,
//the returned set is empty if there isn't any piece or if there are no possible moves
set<std::pair<int, int>> ChessBoard::getPossiblemovements(int row, int col){

    shared_ptr<ChessPiece> &piece = _chessBoard[row][col];

    std::set<std::pair<int, int>> ret = piece->getLegalMoves(_chessBoard);

    for(auto it = ret.begin(); it!=ret.end(); ){
        if(!isPossibleMove({row,col}, *it, piece->getSide()))
            it = ret.erase(it);
        else{
            ++it;
        }
    }

    return ret;
}


//returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side,
//the returned set is empty if there isn't any piece or if there are no possible moves
set<pair<int, int>> ChessBoard::getPossiblemovementsByIndex(int index, Side side){
    switch(side){
        case Side::black:
            return getPossiblemovements(_black[index]->getRow(), _black[index]->getCol());
        break;
        case Side::white:
            return getPossiblemovements(_white[index]->getRow(), _white[index]->getCol());
        break;
    }
    return set<pair<int, int>>{};
}



//changes pointers and returns the type of move that was done
void ChessBoard::doMove(const pair<int, int>& from, const pair<int, int>& to){

    shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];    //reference just to not screw...
    shared_ptr<ChessPiece>& toPiece = _chessBoard[to.first][to.second];          //...internal shared_ptr counter

    ////if there's a capture or you move a pawn, you can't go back
    if(fromPiece->getRole() == Role::pawn || toPiece->getRole() != Role::dummy){        
        _finalCountUp = 0;
        _repeatedBoards.clear();
    }

    //update repeated board history
    string key = this->notToString();
    if(_repeatedBoards.find(key) != _repeatedBoards.end())
        _repeatedBoards[key]++;
    else
        _repeatedBoards[key] = 1;

    _finalCountUp++;   //repeatable moves counter

    //for staleMate by repeated moves (finalCountUp is checked by isStaleMate)
    if(_repeatedBoards[key]>=3)
        _threeRep = true;


    //remove from piece list
    if(toPiece->getRole() != Role::dummy){
        removeFromPieceList(toPiece);
        _chessBoard[to.first][to.second] = oneDummyToRuleThemAll;
    }

    //update piece information
    fromPiece->setPosition(to.first, to.second);

    //actually swap pointers
    swapPieces(from, to);

}


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::addToPieceList(const shared_ptr<ChessPiece>& piece){
    getPieceList(piece->getSide()).push_back(piece);
    return;
}


//remove piece from the corresponding (black or white) list of pieces
void ChessBoard::removeFromPieceList(const shared_ptr<ChessPiece>& piece){

    vector<shared_ptr<ChessPiece>>& pieceList = getPieceList(piece->getSide());
    for(auto it=pieceList.begin(); it!=pieceList.end(); it++){
        if(*it == piece){
            pieceList.erase(it);
            return;
        }
    }
}


vector<shared_ptr<ChessPiece>>& ChessBoard::getPieceList(Side s){
    if(s == Side::black)
        return _black;
    if(s == Side::white)
        return _white;

    throw NoSideException{};
}


//returns the number of piece on the chessboard
int ChessBoard::nOfPieces(Side s) const{
    if(s == Side::black)
        return _black.size();
    if(s == Side::white)
        return _white.size();
    
    throw NoSideException{};
}



//get position of the piece with index in the piece list of specific side
pair<int, int> ChessBoard::getPosition(int index, Side side) const{
    switch(side){
        case Side::black:
            if(index >= _black.size())
                return {-1, -1};

            return {_black[index]->getRow(), _black[index]->getCol()};
        break;

        case Side::white:
            if(index >= _white.size())
                return {-1, -1};
    
            return {_white[index]->getRow(), _white[index]->getCol()};
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
            if(_chessBoard[i][j]->getSide() == Side::black)
                res += static_cast<char>(_chessBoard[i][j]->getRole());
            else
                res += std::tolower(static_cast<char>(_chessBoard[i][j]->getRole()));

            //TOREMOVE
            if(_chessBoard[i][j]->getRole() != Role::dummy && (_chessBoard[i][j]->getRow()!=i || _chessBoard[i][j]->getCol()!=j)){
                std::cout << "Dio merdone ladro cane" << std::endl;
                throw IllegalMoveException();
            }

        }
        res += "\n";
    }
    
    res += "\n  ";
    for(int i=0; i<SIZE; i++){
        res += 'A'+i;
    }
    res += "\n";
    return res;
}


//static method to get copy of a piece
shared_ptr<ChessPiece> ChessBoard::copyPiece(const shared_ptr<ChessPiece>& toCopy){
    return newPiece(toCopy->getRow(), toCopy->getCol(), toCopy->getSide(), toCopy->getRole());
}


//static method to get shared pointer of new ChessPiece
shared_ptr<ChessPiece> ChessBoard::newPiece(int row, int col, Side side, Role role){
    switch(role){
        case Role::king:
            return std::make_shared<King>(row, col, side);

        case Role::queen:
            return std::make_shared<Queen>(row, col, side);

        case Role::bishop:
            return std::make_shared<Bishop>(row, col, side);

        case Role::knight:
            return std::make_shared<Knight>(row, col, side);

        case Role::tower:
            return std::make_shared<Tower>(row, col, side);

        case Role::pawn:
            return std::make_shared<Pawn>(row, col, side);

        case Role::dummy:
            return oneDummyToRuleThemAll;
    }

    //it's not possible to reach this
    return nullptr;
}


//foreced swap between two pieces
void ChessBoard::swapPieces(const pair<int, int>& from, const pair<int,int>& to){
    shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];
    shared_ptr<ChessPiece>& toPiece   = _chessBoard[to.first][to.second];

    std::swap(fromPiece, toPiece);

    return;
}


Side ChessBoard::otherSide(Side s){
    if(s==Side::white)
        return Side::black;
    if(s==Side::black)
        return Side::white;
    return Side::noSide;
}




/*--------------------------- Section 2 - Constructors & operators --------------------------------------*/


//constructor
ChessBoard::ChessBoard(){

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            Side side = static_cast<Side>(initial_colors[i][j]);
            Role role = static_cast<Role>(initial_roles[i][j]);
            shared_ptr<ChessPiece> toAdd = newPiece(i, j, side, role);
            _chessBoard[i][j] = toAdd;
            if(toAdd->getRole() != Role::dummy)
                addToPieceList(toAdd);
        }
    }
}


//copy constructor
/*ChessBoard::ChessBoard(const ChessBoard& o){
    
    *this = o;      //call equal operator
}*/


//move constructor
ChessBoard::ChessBoard(ChessBoard&& o){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            _chessBoard[i][j] = o._chessBoard[i][j];
            o._chessBoard[i][j] = nullptr;
        }
    }

    for(auto &i: o._black){      //copy pointers and clear
        _black.push_back(i);
    }
    o._black.clear();

    for(auto &i: o._white){
        _white.push_back(i);
    }
    o._white.clear();
}


//assignment operator, does a copy of the chessPiece objects
/*ChessBoard& ChessBoard::operator=(const ChessBoard& o){
    
    if(this == &o)
        return *this;

    //copy local variables
    _toPromote = o._toPromote;
    _enpassed = o._enpassed;
    _finalCountUp = o._finalCountUp;
    _repeatedBoards = o._repeatedBoards;
    _threeRep = o._threeRep;
    
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            _chessBoard[i][j] = oneDummyToRuleThemAll;
        }
    }

    for(const auto &i: o._black){
        _chessBoard[i->getRow()][i->getCol()] = copyPiece(i);
        _black.push_back(_chessBoard[i->getRow()][i->getCol()]);
    }
    for(const auto &i: o._white){
        _chessBoard[i->getRow()][i->getCol()] = copyPiece(i);
        _white.push_back(_chessBoard[i->getRow()][i->getCol()]);
    }

    return *this;
}*/


/*--------------------------- Section 3 - Special moves & situations --------------------------------------*/


//does a promotion
Moves ChessBoard::promotion(Role role){          //I can get info from toPromote attribute

    class Fuck{};                           //TOREMOVE!!!
                                            //TOREMOVE!!!
    if(_toPromote == nullptr){
        throw(Fuck());
    }

    int row = _toPromote->getRow();
    int col = _toPromote->getCol();
    Side side = _toPromote->getSide();

    removeFromPieceList(_toPromote);

    //Place new piece on chessBoard
    _chessBoard[row][col] = newPiece(row, col, side, role);

    addToPieceList(_chessBoard[row][col]);

    _toPromote = nullptr;

    //staleMate check
    if(isStaleMate(side))
        return Moves::staleMate;

    //checkMate check, do-undo strategy for all pieces and all moves
    if(isCheck(otherSide(side), _chessBoard, {row, col}) && !arePossibleMoves(otherSide(side))){
        return Moves::checkMate;
    }

    return Moves::movement;
}


void ChessBoard::doEnpassant(const pair<int, int>& pos){
    shared_ptr<ChessPiece> piece = _chessBoard[pos.first][pos.second];

    switch(piece->getSide()){

        case(Side::black):
            removeFromPieceList(_chessBoard[pos.first+1][pos.second]);
            _chessBoard[pos.first+1][pos.second] = oneDummyToRuleThemAll;
        break;

        case(Side::white):
            removeFromPieceList(_chessBoard[pos.first-1][pos.second]);
            _chessBoard[pos.first-1][pos.second] = oneDummyToRuleThemAll;
        break;

        default:
            throw NoSideException{};
        break;
    }

    return;
}


bool ChessBoard::doCastling(const pair<int, int> &rookPos){

    const int& rookCol = rookPos.first;
    constexpr int kingCol = 4;              //king has not moved

    shared_ptr<ChessPiece> kingPiece = _chessBoard[rookPos.first][kingCol];
    shared_ptr<ChessPiece> rookPiece = _chessBoard[rookPos.first][rookPos.second];
    Side side = kingPiece->getSide();


    if(rookCol < kingCol){     //left~long castling
        for(int i=1; i<=2; i++){
            //move king to the left one by one
            swapPieces({rookPos.first, kingCol-i-1}, {rookPos.first, kingCol-i});
            //check for check situation --> (invalid castling)
            if(isCheck(side)){
                //go back
                swapPieces({rookPos.first, kingCol}, {rookPos.first, kingCol-i});
                return false;
            }
        }

        //move rook
        swapPieces({rookPos.first, rookPos.second}, {rookPos.first, rookPos.second+3});

        //update piece information
        kingPiece->setPosition(rookPos.first, kingCol-2);
        rookPiece->setPosition(rookPos.first, rookPos.second+3);
        return true;
    }


    if(rookCol < kingCol){     //right~short castling
        for(int i=1; i<=2; i++){
            //move king to the left one by one
            swapPieces({rookPos.first, kingCol+i-1}, {rookPos.first, kingCol+i});
            
            //check for check situation --> (invalid castling)
            if(isCheck(side)){
                //go back
                swapPieces({rookPos.first, kingCol}, {rookPos.first, kingCol+i});
                return false;
            }
        }

        //update piece information
        kingPiece->setPosition(rookPos.first, kingCol+2);
        rookPiece->setPosition(rookPos.first, rookPos.second-2);

        //move rook
        swapPieces({rookPos.first, rookPos.second}, {rookPos.first, rookPos.second-2});

        return true;
    }

    //this should be unreachable
    return false;
}



#endif