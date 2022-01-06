#ifndef REPLAY_CPP
#define REPLAY_CPP

#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "Enums.h"

/*
the format for the log is:
    the movement is represented by two coordinates(in letter(upper-case)-number format)
    the special moves commands are
        -"-promotion" followed by the character representing the new piece and the movement of the pawn
        -"-castling" followed by the movement of the king
        -"-enpassant" followed by the movement of the pawn
the program doesn't check if the moves are legal but only if the format is right throwing an exception
*/
char chess[8][8] = {

    {'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'t', 'c', 'a', 'd', 'r', 'a', 'c', 't'}
};


std::pair<int, int> convertPos(std::string s);
bool isValidInput(std::string pos);
std::string print();

class NoFileGiven{};
class WrongFormat{};

int main(int argc, char** argv){
    //if there are less than 2 arguments there isn't a file name given
    if(argc < 2){
        throw NoFileGiven{};
    }

    std::ifstream in{argv[1]};

    std::vector<std::string> vec;//contains the boards
    vec.push_back(print()); //initial matrix
    std::string line;

    while(std::getline(in, line)){
        std::istringstream temp{line};
        std::string from, to;
        temp >>from;

        //different cases for special moves start with "-"
        if(from[0] == '-'){

            //promotion case
            if(from == "-promotion"){
                std::string s;
                temp >> s;

                //the name of the promoted piece can't be more than one character
                if(s.size() != 1){
                    throw WrongFormat{};
                }
                temp>>from>>to;
                std::pair<int,int> fromp, top;

                if(isValidInput(from) && isValidInput(to)){
                    fromp = convertPos(from);
                    top = convertPos(to);
                }
                else{
                    throw WrongFormat{};
                }
                chess[top.first][top.second] = s[0];
                chess[fromp.first][fromp.second] = ' ';
            }

            //castling case
            else if(from == "-castling"){
                temp>>from>>to;
                std::pair<int,int> fromp, top;
                if(isValidInput(from) && isValidInput(to)){
                    fromp = convertPos(from);
                    top = convertPos(to);
                }
                else{
                    throw WrongFormat{};
                }

                chess[top.first][top.second] = chess[fromp.first][fromp.second];
                chess[fromp.first][fromp.second] = ' ';

                //moving the tower
                if(fromp.second < top.second){
                    chess[fromp.first][fromp.second + 1] = chess[fromp.first][7];
                    chess[fromp.first][7] = ' ';
                }
                else{
                    chess[fromp.first][fromp.second - 1] = chess[fromp.first][7];
                    chess[fromp.first][0] = ' ';
                }
            }
            else if(from == "-enpassant"){
                temp>>from>>to;
                std::pair<int,int> fromp, top;

                if(isValidInput(from) && isValidInput(to)){
                    fromp = convertPos(from);
                    top = convertPos(to);
                }
                else{
                    std::cout << "invalid file format";
                    return 0;
                }
                chess[top.first][top.second] = chess[fromp.first][fromp.second];
                chess[fromp.first][fromp.second] = ' ';
                if(fromp.second < top.second){
                    chess[fromp.first][fromp.second + 1] = ' ';
                }
                else{
                    chess[fromp.first][fromp.second - 1] = ' ';
                }
            }
            else{
                std::cout << "invalid file format";
                return 0;
            }
        }
        //no Special move
        else{
            temp >>to;
            std::pair<int,int> fromp, top;
            if(isValidInput(from) && isValidInput(to)){
                fromp = convertPos(from);
                top = convertPos(to);
            }
            else{
                throw WrongFormat{};
            }
            chess[top.first][top.second] = chess[fromp.first][fromp.second];
            chess[fromp.first][fromp.second] = ' ';
        }
        vec.push_back(print());
    }

    if(argc == 3){
        std::ofstream out{argv[2]};
        for(int i = 0; i < vec.size(); i++){
            out << vec[i];
        }
        out.close();
    }
    else{
        for(int i = 0; i < vec.size(); i++){
            std::cout << vec[i];
            std::chrono::milliseconds timespan(5000);
            std::this_thread::sleep_for(timespan);
            std::system("CLS");
        } 
    }
}

std::pair<int, int> convertPos(std::string toConvert){

    std::pair<int, int> convertedPos;
    convertedPos.second = toConvert[0] - 65;
    convertedPos.first = 8 - (toConvert[1] - 48);

    return convertedPos;

}

bool isValidInput(std::string pos){
  if(pos.size() != 2)
    return false;

  if(pos[0] < 65 || pos[0] > 73 || pos[1] < 48 || pos[1]> 56)
    return false;

  return true; 
}

std::string print(){
    std::string ret = "";
    for(int i = 0; i < 8; i ++){
        ret += std::to_string(i + 1);
        ret +=" "; 
        for(int j = 0; j < 8; j++){
            ret += chess[i][j];
        }
        ret += "\n";
    }
    ret += "\n  ABCDEFGH\n";
    return ret;
}

#endif