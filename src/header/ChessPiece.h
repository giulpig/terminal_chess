#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <utility>
#include <set>

#include "Enums.h"
#include "Exceptions.h"
#include <memory>

class ChessPiece{

private:
    std::pair<int, int> location;
    Side color;
    //used for special moves
    bool moved = false;

protected:
    Role rol;
    ChessPiece(int _row, int _col, Side s);
    //utility functions
    bool checkBoundaries(int, int) const;
    bool isDummy(const std::shared_ptr<ChessPiece>[8][8], int , int) const;
    bool isOppositeSide(const std::shared_ptr<ChessPiece>[8][8], int , int) const;
public:

    ChessPiece(const ChessPiece&);

    int getRow() const;
    int getCol() const;
    Role getRole() const;
    bool isMoved() const;
    Side getSide() const;
    std::pair<int, int> getPosition() const;

    //moves without validating the move
    virtual void setPosition(int _row, int _col) = 0;


    /*
    //
    // Non so perchè, ma senza il         "const", non funzionava
    //                                       \
    //                                        v
    */

    //returns legal moves not counting the possible autocheck
    virtual std::set<std::pair<int, int>>getLegalMoves(const std::shared_ptr<ChessPiece>[8][8]) const = 0;
    
    //returns the type of move that they did
    virtual Moves moveType(int _row, int _col, const std::shared_ptr<ChessPiece>[8][8]) const = 0;
};

#endif
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxnxxxxxnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxMnnxxxxnnxxnnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxnnnnnnnnxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxMWWWWMMxnnnxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxMMWWW#@@@@WWWWWWMMxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxMW@@@@@WWWWMMWMWWWWWxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxW@@@WW@WWWWWMMWMMWWWWWMnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxxnMxxxM@@@@@@@W@@@@WWMxMMWMWWWWMMnnxnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxnxxxxMW@@@@@@@@@WWWWWMMWWWWWWWW@Wxnnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxnxxxnMWWWWWW@WWMMMMMxxxMMMMWWWWWWMMnnnnnnnnnnnnnnnnnnnnnnnnn
xxxxxxxxxxxxxxxxxxxxxxxxxnxxxxWxMMMMMMMxxxxxnnnxxMMMMWWMMMWWnnnnnnnnnnnnnnnnnnnzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxMMnnnxMxxxxxxxnnnnnnxMWWWWWWWWWnnnnnnnnnnnnnnnnzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxMnzznxMxxxxxxnnnzzznxMWWWWWWW@@Mnnnnnnnnnnnnnzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxxxMxzznxxMMxxxxxnnnzzznxMWWWWMMM@W@nnznnnnnnnnzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxxxWz#nnxxMMMMxMxnnnnnnnxxMWWMMWMWM@nznnnnnnnnnzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxnxxn#znxxMMMMMxxxnnnnnznnxxMWWWWWMWWxznnnnnnzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxnMz##xxxxxMxxxMxxnnnzzznxMMMMWW@WWWMznnnnnnzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxnM###MxnnxMxxMxMMxnnnnznxxxMMMW@WWWWnnnnnnzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxnx+zzMnnnMWWWWWWWMxnnzzzznxMMMWWW@@Wnznnnzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxnxxn+#nxxxMW@@@W@WMMMMxnnz#znMWMMWW@@Wzznnzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxnxx##zxnMWWWW@@WMMMMxxxxnnzzzxMWWWW@@Wznzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxxnnxMxMWWWW@@WWWWWxnnnnnnzznMWWWWWWWznzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxxxM@@MxxMMW@@@#@MWWWxnznzzznMWMMMxxMznzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxW@@W@xznzx@@@WWMMMMMxnnzzzzzxWMxn+xnnnzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxnnW@WWznzxW@@WWWWMMxxxnnzzzzxMnn#nzMzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxnxnM@#@MnnznMW@@WWWMxnnnnzzzzznxn#znzxnzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxnxx#WW#zxxzzxMWWWWMxxnzzzzzzznxMn#xnxzxzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxnMnMWnxzzznMWWWMMxnnzzznnnnxMWnznMMMnzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxxxzxWnxnzzznMWWMWMMxnnnnnnnnxMWzz#xW@nnzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxnnnzWMnxnznnnMWWWWMMxxxnnnnznxMWn##zMMnnzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxxxxxn+zx#xxnznz#xMWWMxxMMxnnnnnxMWMnznxxxzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxnnnnxi#znnMnxMMnxMWWWMxnxWxxxxxMMMWxznznznzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxxnnnxxi*nxnxxxxMMWWMW@@WnzxWMMMMMxxWxznznznzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxxnnnnnx*iM@xxxWW@#@@M@@@@Mzx@WMWMxxxMMnzznznzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxxnnnnnnxz*xWxnn@WWWW@@WWW@@xx@WMWWxxxMMnzznzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxxxxxxxxxxxnnnnnnnxx#zMMxM@MWMMxnMWW@WxM@@MMMxxMMMx#znzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxnnnnnnnnnnnnnnnnnnxnzMxnnMMWxMxxM@@@WxW@@WMMMMMMxx#znzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxnnnnnnnnnnnnnnnnnnnxnxnzxnMzz#zxMW@@WM@@@WMMWMxxxMzzzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxnnnnnnnnnnnnnnnnnxzxxWM@+;nzMxMMxM@@WM@@@@WWWMnnxMzzzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxnnnnnnnnnnnnnnnnnnnxMW#x#nxMxxxxWW@@WMW@WWWWWxxxnWz#nzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxxnnnnnnnnnnnnnnnnnnnxMMW##nxMxMMMWW@@WW@@WWWWMxxMMWz#nzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxnnnnnnnnnnnnnnnnnxnnnMMM#zxWWWWW@@@@@WW@@@WWWWMMMWMzznzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxxnnnnnnnnnnnnnnnnnnxnnxxWxnM@@@W@@@@@@WW@@@WWWWWMWWx#znznzzzzzzzzzzzzzzzzzzzzzz
xxxxxxnnnnnnnnnnnnnnnnnnnnnnxnMMnMW@WWWW@@@@WW@@@WWWMMW@Mn#zzznzzzzzzzzzzzzzzzzzzzzzz
xxxxxxnnnnnnnnnnnnnnnnnnnnnnxnMxnxWWWWW@@@@@WW@@@WWW@@WMnz#zzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxnnnnnnnnnnnnnnnnnnnxznxnMWxMW@@@@@@@@WWW@@@WW@@Wxzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxnnnnnnnnnnnnnnnnnnnxnnnzxWMWW@@@@@@WWWMW@W@@#Wxnzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxnnnnnnnnnnnnnnnnnnnnnxnnxWW@@W@@@WWWWWWW@@#Wxnzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxxnnnnnnnnnnnnnnnnnnnnnnnznxMW@W@@@WWMMMW@@WWxnnnnnzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxnnnnnnnnnnnnnnnnnnnxnnnnznxMW@WWWWWMMMM@@WMxnnnnnnzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
xxxxxnnnnnnnnnnnnnnnnnnnnnnxnnnxWW@@WWWWWWW@@@Mxnnnnnnnzzz##zznnzzzzzzzzzzzzzzzzzzzzz
xxxxxnnnnnnnnnnnnnnnnnnnnnnnnnxMWWWWWWWWW@@@WMxnnnxnnnzzzz###znnzzzzzzzzzzzzzzzzzzzzz
xxxxxnnnnnnnnnnnnnnnnnnnnnnnnnxMMWW@@@@@@@@WMxnnnnnnnnnnzz###znnnnzzzzzzzzzzzzzzzzzzz
xxxxnnnnnnnnnnnnnnnnnnnnnnnnnnxxWW@@@@@@WWWMxnnnnnnnnnnnzzzzzzznxnnnzzzzzzzzzzzzzzzzz
xxxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnxMWWMxxxWWWWMxnnnnnnnnzzzzzzzzzzxxxxxnnnzzzzzzzzzzzzz
xxxxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn+*+zxWMMxxnznnnnnzzzzzzzzznnxxxnxxxMxnz###zzzzzz
xxxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn#i*#nMMxxnnznnnnnzzzzzzzzznnnxxxxxxxxxxxnnzzzzzz
xxxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn#i*+zMMMxnnznxnnnzzzzzzzzznnnnxxxxxxxxMMxxxzzzz#
xxxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnzi**zMMMxnnznxxnnzzzzzzz#zznznxMxxxxxxxxxxMxxnzz
xxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnzi*+zxMMxxnnxxxnnzzzzzzz#zzzznxMMMMxxMMMMxxMMxxn
xxxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnzni++#nMMMxnnxxxnnzzzzzzz#zzznnxMWWWMMMMMMxxMMxxx
xxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnzni+++#xMMxxnxxxnnzzzzzzzzzzznxxMWWWWWMMMMMMxxxxM
xxnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnzxi*#+#nMMxnxxxxnnzznzzzzzzzznxxMWWWWWWWMMMMMMMMx
nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnz#**#z#zxWxxxxMnnnznnzzzzzzznnxxMWWWWWWWMMMMMMMMx
nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnzz##**+zzzxMMMMMMnnnznnnzzzzzznnxxMMWWWWWWWWWMMMMMM
nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnzzz#+#**+#nzxxWMMMMxnnnnnnzznnnnnnxxMMWWWWWWWWWWWMMMM
nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnz#####z**+#nnnxWMMMMxnnnxxxnnnnnnnxxxMMWWWWWWWWWMMWWWW
nnnnnnnnnnnnnnnnnnnnnnnnnnnnnzz#####zn+i+##nxMMMMxMxnnnxxxxxxMxxxMMMMWWWWMMMMMMMMMWWW
nnnnnnnnnnnnnnnnnnnnnnnnnnnnzz###zznxx+i+++nxMMMMxMxnnxMMMMMWWWWMMMMMMMMxxxxxnxxMWWWW
nnnnnnnnnnnnnnnnnnnnnnnnnnnz###znnnxxn*i+++zxMMMMnxMnxMMWWMMMMMxxMMxxxxxxxnnnnxMWWWWW
nnnnnnnnnnnnnnnnnnnnnnnnnnnz##znnnxxnz*i*+++MMWMMzxxxxMWMxxxxxxxxMMxxMMMxxxxxxMWWWWWM
nnnnnnnnnnnnnnnnnnnnnnnnxz####znnnnxn#+***#+xWWMM+nMMMxxxnnnxMMxMMMMMMMMxxxxxxMW@WMMx
nnnnnnnnnnnnnnnnnnnnnnnnz####znznnnnnz###++*zMWMz+xxnnxxMxxxxMMMMMMMMMMMxMMMMMWWWMMxx
nnnnnnnnnnnnnnnnnnnnnzzzzzzzznnznnxxxnnxxz+++MMM##xzznnxMMMMMMMMMMMMMMMMxxxxMMMMMMxnn
nnnnnnnnnnnnnnnnnnnzzzznxxxzzzzznnnnxxxxxnzz#MMx##z#znxMMMMMMMMMMMMMMMxxxxxxMMMMMxxnn
nnnnnnnnnnxnnnnnnzzzznxxxMxnz##zzzzznnnxxnxxznxnzz##zxnxxMMMMMMMMMxxxxxxMxxMMMMMMxxnn
nnnnnnnnnnnnnnnnzzznnxxxMMMxz##zzzzznnxxxxMxnznzzzznxxnxxMMMMxxxxxxxxxxxMMMMMMMMxxxxx
nnnnnnnnnnzzzzzzzzznnxxxMMMxzzzzzzzznnnxxMMMxnnzznnMxMxMMMMMxxxxxxxxxxMMMMMMMMMMxxxxx
nnnnnnnnnz##zzzzzzznnnxxxMMnznxnzznnnnxMxMxMMxxzznnxxMMMMMxxxxxxxxxxxxMMMMMMMMMMxxxxx
xnnnxxn#+##zz##zzznnxxMxxnnzznnxxnnnnnxxxMMxMMn#znxxxMMMMxxxxxxxxxxxxMMMMMMMMMMMxxxxx
nnxxnz+*######zzznnxxxxxnnnnnnxxxxnnxxxMMMMMWMn#znxxxxMxMMxxnnnnxxxxxMMMMMMMMMMMxxxxx
xxxz+*++#####zznnnxxxxnnnnnnnnxxxxxxxxxMMMMMMxz#znxxxxxxMxxxnnnnxxxxxMMMMMMMMMMMxxxxx
xxz+**+z####zzznnxxxxnnzznnnnxxxxxxxxxxMMMMMMn##znxxxxxxxxxnnxxxxxxxxMMMMMMMMMMMMMMMx
nn+*++#####zzzznxxxnnnnzznnnnxxxxnnnnnxMMMMMMn##znxxxxxxxnnnnxxxxxxxxMMMMMMMMMMMMMMMM*/
