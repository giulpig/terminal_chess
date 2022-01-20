#ifndef MANAGEPOSITION_H
#define MANAGEPOSITION_H

#include<utility>
#include<string>

namespace mPos{
    std::string reConvertPos(std::pair<std::pair<int, int>, std::pair<int, int>>);

    std::pair<int, int> convertPos(std::string);

    bool isValidInput(std::string);
}


#endif