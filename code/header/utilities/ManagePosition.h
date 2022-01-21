#ifndef MANAGEPOSITION_H
#define MANAGEPOSITION_H

#include<utility>
#include<string>

namespace mPos{

    /**
     * Convert the position from pairs of int to string, formatted in the right way
     * Example:
     * {1,2}, {1,2} --> A7 A7 
     */
    std::string reConvertPos(std::pair<std::pair<int, int>, std::pair<int, int>>);

    /**
     * Convert from the stirng format to integer that point to the same position in the matrix
     */
    std::pair<int, int> convertPos(std::string);

    /**
     * Check the format of the input
     */
    bool isValidInput(std::string);
}


#endif