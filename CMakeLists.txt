cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
# set the project name
project(Chess VERSION 1.0)
add_library(ChessPiece
    ChessPiece.cpp
    Tower.cpp
    Knight.cpp
    Bishop.cpp
    King.cpp
    Queen.cpp
    Pawn.cpp
)
add_library(ChessBoard
    ChessBoard.cpp
)
add_executable(Main
    ///
)
target_link_libraries(Main
    ChessPiece
    ChessBoard
)