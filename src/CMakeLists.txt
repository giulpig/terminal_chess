cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
# set the project name
project(Chess VERSION 1.0)

include_directories(header)

add_library(ChessPiece
    header/ChessPiece.h
    header/Enums.h
    header/Exceptions.h
    implementation/ChessPiece.cpp
)

add_library(Tower
    implementation/Tower.cpp
    header/Tower.h
)
add_library(Knight
    implementation/Knight.cpp
    header/Knight.h
)

add_library(Bishop
    implementation/Bishop.cpp
    header/Bishop.h
)

add_library(King
    implementation/King.cpp
    header/King.h
)

add_library(Queen
    implementation/Queen.cpp
    header/Queen.h
)

add_library(Pawn
    implementation/Pawn.cpp
    header/Pawn.h
)

add_library(Dummy
    implementation/Dummy.cpp
    header/Dummy.h
)

add_library(ChessBoard
    implementation/ChessBoard.cpp
    implementation/checks.cpp
    header/ChessBoard.h
)

# Game libraries
add_library(Game
    header/Enums.h
    implementation/Game.cpp
    header/Game.h
)

add_library(Player
    implementation/Player.cpp
    header/Player.h
)

add_library(HumanPlayer
    implementation/HumanPlayer.cpp
    header/HumanPlayer.h
)

add_library(PcPlayer
    implementation/PcPlayer.cpp
    header/PcPlayer.h
)

add_library(Log
    implementation/Log.cpp
    header/Log.h
)

add_executable(Main
    ../main.cpp
)
add_executable(Replay
    ../Replay.cpp
)
target_link_libraries(ChessBoard
    Tower 
    Bishop
    Dummy
    King
    Knight
    Pawn 
    Queen 
    ChessPiece
)

target_link_libraries(Game
    ChessBoard
    Player
    HumanPlayer
    PcPlayer
    Log
)

target_link_libraries(HumanPlayer
    Player
)

target_link_libraries(PcPlayer
    Player
)

target_link_libraries(Main
    ChessBoard
    Game
)
