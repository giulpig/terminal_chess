#ifndef LOG_H
#define LOG_H

#include<fstream>
#include<utility>
#include<iostream>
#include<sstream>
#include"Enums.h"
#include"ManagePosition.h"

/* Formato Log:
 *
 * A2 A4
 * 
 * -promotion k B3 B7
 * -castling
 * -enpassant 
 */

class Log {

    private:
        std::string nameFile;

        //defaul distructor will close correctly the ofstream
        std::ofstream fileStream;

        /*
        ** Check if the file exists already using file input stream
        */
        bool exist(std::string) const;

        /*
        ** Test if the name of the file is avaiable and 
        ** if it is not add a sequentially number to the end
        */
        std::string getName(std::string);

        /*
        ** Adding the sequence number and the extension to the name
        */
        std::string createFormatName(const std::string&, int);

        /*
        ** Get the string of movement from the enum type
        */
        std::string getStrMov(Moves, std::string) const;

    public:

        //Log();

        /*
        * This constuctor create the file,
        * if the file already exist add a sequence integer to the end
        */
        Log(std::string _nameFile);

        // Move Operator
        Log& operator=(Log&&);

        // copy the log is usefull
        Log(Log&) = delete;
        Log& operator=(const Log& l) = delete;

        /*
        ** Log the move to a specified file using a specified format,
        ** log the movement and also special movements with the possible promotion piece
        */
        void logMove(Moves, std::pair<std::pair<int, int>, std::pair<int, int>>, std::string);
};


#endif