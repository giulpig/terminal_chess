#ifndef MANGEPOSITION_CPP
#define MANGEPOSITION_CPP

#include"ManagePosition.h"

using std::pair;
using std::string;

pair<int, int> mPos::convertPos(std::string toConvert) {

    pair<int, int> convertedPos;
    convertedPos.second = toConvert[0] - 65;
    convertedPos.first = 8 - (toConvert[1] - 48);

    return convertedPos;

}

bool mPos::isValidInput(string pos) {
  if(pos.size() != 2)
    return false;

  if(pos[0] < 65 || pos[0] > 73 || pos[1] < 49 || pos[1]> 56)
    return false;

  return true; 
}

 std::string mPos::reConvertPos(pair<pair<int, int>, pair<int, int>> mov) {

    string st;
    st += (char) mov.first.second + 65;
    st += (char) (8 - mov.first.first) + 48;
    st += ' ';
    st += (char) mov.second.second + 65;
    st += (char) (8 - mov.second.first) + 48;

    return st;

}





#endif