cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
# set the project name
project(Chess VERSION 1.0)

add_library(ChessPieces

    implementation/ChessPiece.cpp
    header/ChessPiece.h
    implementation/Tower.cpp
    header/Tower.h
    implementation/Knight.cpp
    header/Knight.h
    implementation/Bishop.cpp
    header/Bishop.h
    implementation/King.cpp
    header/King.h
    implementation/Queen.cpp
    header/Queen.h
    implementation/Pawn.cpp
    header/Pawn.h

)

add_library(ChessBoard
    imlementation/ChessBoard.cpp
    header/ChessBoard.h
)

add_executable(Main
    ///
)

target_link_libraries(Main
    ChessPiece
    ChessBoard
)