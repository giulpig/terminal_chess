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
            ~ promotion()   [private]
            ~ enpassant()   [private]
*/




/*--------------------------- Section 1 - Utility methods ----------------------------------------*/

Moves ChessBoard::move(const pair<int, int>& from, const pair<int, int>& to, Side side){

    shared_ptr<ChessPiece>& fromPiece = chessBoard[from.first][from.second];    //reference just to not screw...
    shared_ptr<ChessPiece>& toPiece = chessBoard[to.first][to.second];          //...internal shared_ptr counter

    //You can't move other player's pieces
    if(fromPiece->getSide() != side)
        return Moves::NaM;

    //You can't eat a king
    if(toPiece->getRole() == Role::king)
        return Moves::NaM;

    //Check for special moves
    switch(fromPiece->moveType(to.first, to.second, chessBoard)){

        case Moves::castling:
            
        break;
        case Moves::promotion:
            toPromote = chessBoard[from.first][from.second];
        break;
        case Moves::enpassant:
            enpassant(from);
        break;
    }

    doMove(from, to);

    if(threeRep){
        ;////////////////PATTTTTTTTTAAAAA
    }

    return Moves::movement;
}


//changes pointers and returns the type of move that was done
void ChessBoard::doMove(const pair<int, int>& from, const pair<int, int>& to){

    shared_ptr<ChessPiece>& fromPiece = chessBoard[from.first][from.second];    //reference just to not screw...
    shared_ptr<ChessPiece>& toPiece = chessBoard[to.first][to.second];          //...internal shared_ptr counter

    ////if there's a capture or you move a pawn, you can't go back
    if(fromPiece->getRole() == Role::pawn || toPiece->getRole() != Role::dummy){        
        finalCountDown = 0;
        repeatedBoards.clear();
    }

    //update piece information
    fromPiece->setPosition(to.first, to.second);

    //actually swap pointers
    toPiece = fromPiece;
    fromPiece = oneDummyToRuleThemAll;

    //remove from piece list
    if(fromPiece->getRole() != Role::dummy)
        removeFromPieceList(toPiece);

    //update repeated board history
    string key = this->notToString();
    if(repeatedBoards.find(key) != repeatedBoards.end())
        repeatedBoards[key]++;
    else
        repeatedBoards[key] = 1;

    finalCountDown++;   //unrepeatable moves counter

    //PATTA if there are repeated moves (finalCountDown is checked by ...)
    if(repeatedBoards[key]>=3)
        threeRep = true;

    //apply promotion
    if(toPromote != nullptr)        //OOOKKKKKIOOOIOIOIO
        promotion(Role::queen);     //how do I know promotion Role???

}


//adds piece at the end of the corresponding (black or white) list of pieces
void ChessBoard::addToPieceList(const shared_ptr<ChessPiece>& piece){
    if(piece->getSide() == Side::black){
        black.push_back(piece);
        return;
    }

    if(piece->getSide() == Side::white)
        white.push_back(piece);
    
    return;
}


//remove piece from the corresponding (black or white) list of pieces
void ChessBoard::removeFromPieceList(const shared_ptr<ChessPiece>& piece){

    if(piece->getSide() == Side::black){
        for(auto it=black.begin(); it!=black.end(); it++){
            if(*it == piece)
                black.erase(it);
                return;
        }
    }

   if(piece->getSide() == Side::white){
        for(auto it=white.begin(); it!=white.end(); it++){
            if(*it == piece)
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
    res += "\n";
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

    for(auto it = ret.begin(); it!=ret.end(); it++){
        //OKKIO: not possible remove pair from ret, maybe create a new set
        //TODO: you can't put yourself in a check position
        if(false){
            ret.erase(it);
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
shared_ptr<ChessPiece> ChessBoard::copyPiece(const shared_ptr<ChessPiece>& toCopy){
    switch(toCopy->getRole()){
        case Role::king:
            return std::make_shared<King>(dynamic_cast<King&>(*toCopy));

        case Role::queen:
            return std::make_shared<Queen>(dynamic_cast<Queen&>(*toCopy));

        case Role::bishop:
            return std::make_shared<Bishop>(dynamic_cast<Bishop&>(*toCopy));

        case Role::knight:
            return std::make_shared<Knight>(dynamic_cast<Knight&>(*toCopy));

        case Role::tower:
            return std::make_shared<Tower>(dynamic_cast<Tower&>(*toCopy));

        case Role::pawn:
            return std::make_shared<Pawn>(dynamic_cast<Pawn&>(*toCopy));

        case Role::dummy:
            return std::make_shared<Dummy>();
    }

    //it's not possible to reach this
    return nullptr;
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
            return std::make_shared<Dummy>();
    }

    //it's not possible to reach this
    return nullptr;
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
            chessBoard[i][j] = copyPiece(o.chessBoard[i][j]);
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
            chessBoard[i][j] = copyPiece(o.chessBoard[i][j]);
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
void ChessBoard::promotion(Role role){          //I can get info from toPromote attribute

    int row = toPromote->getRow();
    int col = toPromote->getCol();
    Side side = toPromote->getSide();

    removeFromPieceList(toPromote);

    //Place new piece on chessBoard
    chessBoard[row][col] = newPiece(row, col, side, role);

    addToPieceList(chessBoard[row][col]);

    toPromote = nullptr;
}


void ChessBoard::enpassant(const pair<int, int>& pos){
    shared_ptr<ChessPiece>& piece = chessBoard[pos.first][pos.second];

    switch(piece->getSide()){
        case(Side::black):
            removeFromPieceList(chessBoard[pos.first+1][pos.second]);
            chessBoard[pos.first+1][pos.second] = oneDummyToRuleThemAll;
        break;
        case(Side::white):
            removeFromPieceList(chessBoard[pos.first-1][pos.second]);
            chessBoard[pos.first-1][pos.second] = oneDummyToRuleThemAll;
        break;
        default:
            ;//exception?????????
        break;
    }

    return;
}







#endif