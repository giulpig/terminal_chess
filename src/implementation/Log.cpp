#ifndef LOG_CPP
#define LOG_CPP

#include"Log.h"

using std::string;
using std::pair;
using namespace mPos;

Log::Log() {}

Log::Log(string _nameFile) {
    nameFile = getName(_nameFile);
    fileStream = std::ofstream (nameFile);
}

Log& Log::operator=(Log&& l) {
    nameFile = l.nameFile;
    l.nameFile = "";
    // Convert to rvalue reference
    fileStream = std::move(l.fileStream);
    return *this;
}

bool Log::exist(string fname) const {
    // distructor will automatically close the stream
    std::ifstream stream (fname);
    return bool(stream);
}

string Log::getName(string str) {
    
    int cp = 0;   
    string cmpFileName;

    //loop until proper name found
    do {
        cmpFileName = createFormatName(str, cp++);
    } while(exist(cmpFileName));

    //cmpFileName = createFormatName(str, cp++);

    return cmpFileName;
}

string Log::createFormatName(const string& name, int cp) {

    if(cp == 0)
        return string(name + ".txt");

    std::stringstream newName;
    newName << name << cp << ".txt";

    return newName.str();
}

string Log::getStrMov(Moves mov, string up) const {
    switch (mov) {

        case Moves::movement:
            return "";
            break;
        case Moves::castling:
            return "-castling ";
            break;
        case Moves::promotion:
            return "-promotion " + up + " ";
            break;
        case Moves::enpassant:
            return "-enpassant ";
            break;

        //those are usefull I think
        /*
        case Moves::staleMate:
            return "-staleMate";
            break;
        case Moves::checkMate:
            return "";
            break;
        */
        default:
            return "";
            break;
    }
}

//void Log::logMove(Moves mov, std::pair<char, int> from, std::pair<char, int> to, char prom = '0') {
void Log::logMove(Moves mov, std::pair<pair<int, int>, pair<int, int>> movement, string prom) {

    fileStream << getStrMov(mov, prom) << reConvertPos(movement) <<std::endl;

}

#endif