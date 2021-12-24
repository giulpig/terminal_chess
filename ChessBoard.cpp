#ifndef CHESSBOARD_CPP
#define CHESSBOARD_CPP

#include "ChessBoard.h"


ChessBoard::ChessBoard(){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            side thisSide = static_cast<side>(initial_colors[i][j]);
            switch (initial_roles[i][j]){
                case 'R': {
                    shared_ptr<ChessPiece> toAdd(new King(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    if(thisSide == side::black)
                        black.push_back(toAdd);
                    else
                        white.push_back(toAdd);
                    break;
                }
                case 'D': {
                    shared_ptr<ChessPiece> toAdd(new Queen(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    if(thisSide == side::black)
                        black.push_back(toAdd);
                    else
                        white.push_back(toAdd);
                    break;
                }
                case 'A': {
                    shared_ptr<ChessPiece> toAdd(new Bishop(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    if(thisSide == side::black)
                        black.push_back(toAdd);
                    else
                        white.push_back(toAdd);
                    break;
                }
                case 'C':{
                    shared_ptr<ChessPiece> toAdd(new Knight(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    if(thisSide == side::black)
                        black.push_back(toAdd);
                    else
                        white.push_back(toAdd);
                    break;
                }
                case 'T':{
                    shared_ptr<ChessPiece> toAdd(new Tower(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    if(thisSide == side::black)
                        black.push_back(toAdd);
                    else
                        white.push_back(toAdd);
                    break;
                }
                case 'P':{
                    shared_ptr<ChessPiece> toAdd(new Pawn(i, j, thisSide));
                    chessBoard[i][j] = toAdd;
                    if(thisSide == side::black)
                        black.push_back(toAdd);
                    else
                        white.push_back(toAdd);
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


ChessBoard::ChessBoard(const ChessBoard& o){
    for(int i=0; i<SIZE; i++){
        
    }
}

ChessBoard::ChessBoard(const ChessBoard&&){

}

ChessBoard ChessBoard::operator=(const ChessBoard&){

}

bool ChessBoard::isCheck() const{

}

bool ChessBoard::isCheckMate() const{

}

bool ChessBoard::isStaleMate() const{

}

//returns possible movements from a specific chesspiece. the returned set is empty if there isn't any piece or if there aren't any possible moves
set<std::pair<int, int>> ChessBoard::getPossiblemovements(int _row, int _col) const{
    
}

//returns possible movements for a specific chesspiece in the position of the list of pieces chosen by side
set<std::pair<int, int>> ChessBoard::getPossiblemovementsByIndex(int index, side c) const{

}

//returns the type of move that was done
move ChessBoard::move(pair<int, int>, pair<int, int>) const{

}

//returns a string containing the board disposition
std::string ChessBoard::notToString() const{
    
}

//returns the number of piece on the chessboard
int ChessBoard::nOfPieces(side c) const{

}

//does a promotion
void ChessBoard::promotion(role r){

}








#endif