#include "ChessPiece.h"
#include "Pawn.h"
#include "memory"
#include <iostream>
using std::shared_ptr;
int main(void){
    shared_ptr<ChessPiece> p = std::make_shared<Pawn>(0, 0, side::white);
    shared_ptr<ChessPiece> h = std::make_shared<Pawn>(*std::dynamic_pointer_cast<Pawn>(p));
    p->setPosition(1, 1);
    std::cout << h->getCol() << h->getRow()<<std::endl;
    std::cout << p->getCol() << p->getRow()<<std::endl;
    std::dynamic_pointer_cast<Pawn>(h)->getEnpassant();
    //Pawn p{0, 0, side:white};
}