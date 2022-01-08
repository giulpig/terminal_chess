#ifndef LOG_H
#define LOG_H

#include<fstream>
#include<utility>
#include"Enums.h"
//TODO: Solve this, where put the reconverPos function
#include"ManagePosition.h"

class Log {

    private:
        std::string nameFile;
        //defaul distructor will close correctly the ofstrem
        std::ofstream fileStream;
        bool exist(std::string) const;
        std::string getName(std::string);
        std::string createFormatName(std::string&, int);
        std::string getStrMov(Moves, char) const;

    public:

        /*
        * This constuctor create the file,
        * if the file already exist add a sequence integer to the end
        */
        Log();
        Log(std::string _nameFile);

        //Log& operator=(const Log& l);
        //void logMove(Moves, std::pair<char, int>, std::pair<char, int>, char);
        void logMove(Moves, std::pair<std::pair<int, int>, std::pair<int, int>>, char);
};


#endif