#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "ChessBoard.h"

/*
    Index of contents:
        > Section 1 - Utility methods---------------
            ~ move()
            ~ doMove()              [private]
            ~ addToPieceList()      [private]
            ~ removeFromPieceList() [private]
            ~ getPieceList()        [private]
            ~ nOfPieces()
            ~ notToString()
            ~ getPossiblemovements()
            ~ getPossiblemovementsByIndex()
            ~ isPossibleMove()
            ~ getPosition()
            ~ copyPiece()      [static]
            ~ newPiece()       [static]
            ~ otherSide()      [static]

        > Section 2 - Constructors & operators------
            ~ ChessBoard() [constructor]
            ~ ChessBoard() [copy constructor]
            ~ ChessBoard() [move constructor]
            ~ operator=()

        > Section 3 - Special moves & situations----
            ~ promotion()
            ~ doEnpassant()    [private]
            ~ swapPieces()     [private]
*/




/*--------------------------- Section 1 - Utility methods ----------------------------------------*/

Moves ChessBoard::move(const pair<int, int>& from, const pair<int, int>& to, Side side){

    shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];    //reference just to not screw...
    shared_ptr<ChessPiece>& toPiece = _chessBoard[to.first][to.second];          //...internal shared_ptr counter
    Side oppositeSide = otherSide(fromPiece->getSide());
    
    if(!isPossibleMove(from, to, side)){
        return Moves::NaM;
    }

    //Check for special moves
    switch(fromPiece->moveType(to.first, to.second, _chessBoard)){

        case Moves::castling:       //TODO: check for check
            swapPieces(from, to);
            fromPiece->setPosition(to.first, to.second);
            toPiece->setPosition(from.first, from.second);

            //TODO: check for checkmate

            return Moves::castling;

        case Moves::promotion:
            _toPromote = _chessBoard[from.first][from.second];
        break;

        case Moves::enpassant:
            doEnpassant(from);  //doEmpassant just removes the other pawn, the move is done in doMove
        break;
    }


    doMove(from, to);

    //staleMate if board is repeated 3 times
    if(isStaleMate(side))
        return Moves::staleMate;

    //checkMate check, do-undo strategy for all pieces and all moves
    if(isCheck(oppositeSide, _chessBoard, from) && arePossibleMoves(oppositeSide)){
        return Moves::checkMate;
    }

    if(_toPromote != nullptr)
        return Moves::promotion;

    return Moves::movement;
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

    //update piece information
    fromPiece->setPosition(to.first, to.second);

    //actually swap pointers
    toPiece = fromPiece;
    fromPiece = _oneDummyToRuleThemAll;

    //remove from piece list
    if(fromPiece->getRole() != Role::dummy)
        removeFromPieceList(toPiece);

    //update repeated board history
    string key = this->notToString();
    if(_repeatedBoards.find(key) != _repeatedBoards.end())
        _repeatedBoards[key]++;
    else
        _repeatedBoards[key] = 1;

    _finalCountUp++;   //repeatable moves counter

    //for staleMate by repeated moves (finalCountUp is checked by ...)
    if(_repeatedBoards[key]>=3)
        _threeRep = true;

}


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::addToPieceList(const shared_ptr<ChessPiece>& piece){
    getPieceList(piece->getSide()).push_back(piece);
    return;
}


//remove piece from the corresponding (black or white) list of pieces
void ChessBoard::removeFromPieceList(const shared_ptr<ChessPiece>& piece){

    vector<shared_ptr<ChessPiece>> pieceList = getPieceList(piece->getSide());
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

    //eccezione
}


//returns the number of piece on the chessboard, -1 if re
int ChessBoard::nOfPieces(Side s) const{
    if(s == Side::black)
        return _black.size();
    if(s == Side::white)
        return _white.size();
    
    //eccezione
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

    //you can't check yourself, do-undo strategy
    bool goodMove = true;
    swapPieces(from, to);
    if(isCheck(fromPiece->getSide(), _chessBoard, to)){
        goodMove = false;
    }
    swapPieces(to, from);                           //go back

    return goodMove;
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


//returns possible movements from a specific chesspiece,
//the returned set is empty if there isn't any piece or if there are no possible moves
set<std::pair<int, int>> ChessBoard::getPossiblemovements(int row, int col){

    shared_ptr<ChessPiece> piece = _chessBoard[row][col];

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
            return _oneDummyToRuleThemAll;
    }

    //it's not possible to reach this
    return nullptr;
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
ChessBoard::ChessBoard(const ChessBoard& o){
    
    *this = o;      //call equal operator
}


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


//equals operator, does a copy of the chessPiece objects
ChessBoard& ChessBoard::operator=(const ChessBoard& o){
    
    if(this == &o)
        return *this;

    //copy local variables
    _toPromote = o._toPromote;
    _empassed = o._empassed;
    _finalCountUp = o._finalCountUp;
    _repeatedBoards = o._repeatedBoards;
    _threeRep = o._threeRep;
    
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            _chessBoard[i][j] = _oneDummyToRuleThemAll;
        }
    }

    for(const auto &i: o._black){
        shared_ptr<ChessPiece> newPiece = copyPiece(i);
        _black.push_back(newPiece);
        _chessBoard[i->getCol()][i->getRow()] = newPiece;
    }
    for(const auto &i: o._white){
        shared_ptr<ChessPiece> newPiece = copyPiece(i);
        _white.push_back(newPiece);
        _chessBoard[i->getCol()][i->getRow()] = newPiece;
    }

    return *this;
}


/*--------------------------- Section 3 - Special moves & situations --------------------------------------*/


//does a promotion
void ChessBoard::promotion(Role role){          //I can get info from toPromote attribute

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

    //TODO: check for checkmate
}


void ChessBoard::doEnpassant(const pair<int, int>& pos){
    shared_ptr<ChessPiece>& piece = _chessBoard[pos.first][pos.second];

    switch(piece->getSide()){

        case(Side::black):
            removeFromPieceList(_chessBoard[pos.first+1][pos.second]);
            _chessBoard[pos.first+1][pos.second] = _oneDummyToRuleThemAll;
        break;

        case(Side::white):
            removeFromPieceList(_chessBoard[pos.first-1][pos.second]);
            _chessBoard[pos.first-1][pos.second] = _oneDummyToRuleThemAll;
        break;

        default:
            ;//exception?????????
        break;
    }

    return;
}


//forced castling, just swap pointers
void ChessBoard::swapPieces(const pair<int, int>& from, const pair<int,int>& to){
    shared_ptr<ChessPiece>& fromPiece = _chessBoard[from.first][from.second];
    shared_ptr<ChessPiece>& toPiece   = _chessBoard[to.first][to.second];

    std::swap(fromPiece, toPiece);

    return;
}


#endif