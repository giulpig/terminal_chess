//Artico Giovanni n.matr. 2000178
#ifndef REPLAY_CPP
#define REPLAY_CPP

#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "ManagePosition.h"
#include "Enums.h"
#include "Exceptions.h"
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
//prints the board
std::string print();
//Clears the terminal
void Clear();
//moves the piece and returns the initial and final position in pair format
std::pair<std::pair<int,int>, std::pair<int,int>> movePiece(std::string, std::string);

int main(int argc, char** argv){
    //if there are less than 2 arguments there isn't a file name given
    if(argc < 3){
        throw NoFileGiven{};
    }
    if(argv[1][0] != 'v' && argv[1][0] != 'f'){
        throw WrongArguments{};
    }

    if(argc < 4 && argv[1][0] == 'f'){
        throw WrongArguments{};
    }

    std::ifstream in{argv[2]};

    std::vector<std::string> vec;//contains the boards
    vec.push_back(print());      //initial matrix
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
                //std::getline(temp, s,  (char)1);
                //std::cout << s[1] /*<< (int)s[1]*/ <<std::endl;
                //the name of the promoted piece can't be more than one character
                if(s.size() != 1){
                    std::cout <<  "dio cane il promotion \n" <<s<<std::flush;
                    throw WrongFormat{};
                }
                temp>>from>>to;
                std::pair<std::pair<int,int>, std::pair<int,int>> movement = movePiece(from, to);
                chess[movement.second.first][movement.second.second] = s[0];
                chess[movement.first.first][movement.first.second] = ' ';
            }

            //castling case
            else if(from == "-castling"){
                temp>>from>>to;
                std::pair<std::pair<int,int>, std::pair<int,int>> movement = movePiece(from, to);
                //moving the respective rook
                if(movement.first.second < movement.second.second){
                    chess[movement.first.first][movement.first.second + 1] = chess[movement.first.first][7];
                    chess[movement.first.first][7] = ' ';
                }
                else{
                    chess[movement.first.first][movement.first.second - 1] = chess[movement.first.first][0];
                    chess[movement.first.first][0] = ' ';
                }
            }
            else if(from == "-enpassant"){
                temp>>from>>to;
                std::pair<std::pair<int,int>, std::pair<int,int>> movement = movePiece(from, to);
                chess[movement.first.first][movement.second.second] = ' ';
            }
            //none of the right commands were used
            else{
                std::cout <<  "dio cane il caco \n" <<std::flush;
                throw WrongFormat{};
            }
        }
        //no Special move
        else{
            temp>>to;
            movePiece(from, to);
        }
        vec.push_back(print());
    }

    //if the argument was given to print to file
    if(argv[1][0] == 'f'){
        std::ofstream out{argv[3]};
        for(int i = 0; i < vec.size(); i++){
            out << vec[i] << std::endl;
        }
        out.close();
    }
    //default: print to cout
    else{
        for(int i = 0; i < vec.size(); i++){
            std::cout << vec[i];
            //sets the time between outputs to 5 seconds
            std::chrono::milliseconds timespan(5000);
            //waits for the given timespan
            std::this_thread::sleep_for(timespan);
            Clear();
        } 
    }
}
//returns the string representing the matrix
std::string print(){
    std::string ret = "";
    for(int i = 0; i < 8; i ++){
        ret += std::to_string(8 - i);
        ret +=" "; 
        for(int j = 0; j < 8; j++){
            ret += chess[i][j];
        }
        ret += "\n";
    }
    ret += "\n  ABCDEFGH\n";
    return ret;
}

//clears the terminal
void Clear()
{
#if  defined(__linux__) || defined(__gnu_linux__) || defined (__LINUX__)
    //system("clear");
    std::cout<< u8"\033[2J\033[1;1H"; //using ANSI Escape Sequences 
#elif defined _WIN32
    std::system("cls");
#endif
}

std::pair<std::pair<int,int>, std::pair<int,int>> movePiece(std::string from, std::string to){
    std::pair<int,int> fromp, top;
    if(mPos::isValidInput(from) && mPos::isValidInput(to)){
        fromp = mPos::convertPos(from);
        top = mPos::convertPos(to);
    }
    else{
        throw WrongFormat{};
    }
    chess[top.first][top.second] = chess[fromp.first][fromp.second];
    chess[fromp.first][fromp.second] = ' ';
    return {fromp, top};
}
#endif