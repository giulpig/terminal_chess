cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE, "-O2")

# set the project name
project(Chess VERSION 1.0)


include_directories("code/header/chessboard" "code/header/pieces" "code/header/utilities" "code/header/game"
                    "code/src/chessboard" "code/src/pieces" "code/src/utilities" "code/src/game")

add_library(ChessPiece
    code/header/pieces/ChessPiece.h
    code/header/utilities/Enums.h
    code/header/utilities/Exceptions.h
    code/src/pieces/ChessPiece.cpp
)

add_library(DirectionalPieces
    code/header/pieces/DirectionalPieces.h
    code/src/pieces/DirectionalPieces.cpp
)

add_library(Rook
    code/src/pieces/Rook.cpp
    code/header/pieces/Rook.h
)
add_library(Knight
    code/src/pieces/Knight.cpp
    code/header/pieces/Knight.h
)

add_library(Bishop
    code/src/pieces/Bishop.cpp
    code/header/pieces/Bishop.h
)

add_library(King
    code/src/pieces/King.cpp
    code/header/pieces/King.h
)

add_library(Queen
    code/src/pieces/Queen.cpp
    code/header/pieces/Queen.h
)

add_library(Pawn
    code/src/pieces/Pawn.cpp
    code/header/pieces/Pawn.h
)

add_library(Dummy
    code/src/pieces/Dummy.cpp
    code/header/pieces/Dummy.h
)

add_library(ChessBoard
    code/header/chessboard/ChessBoard.h
    code/src/chessboard/ChessBoard.cpp
    code/src/chessboard/checks.cpp
    code/src/chessboard/specialMoves.cpp
    code/src/chessboard/utilityChessBoard.cpp
)


add_library(ManagePosition
    code/src/utilities/ManagePosition.cpp
    code/header/utilities/ManagePosition.h
)

add_library(Game
    code/header/utilities/Enums.h
    code/src/game/Game.cpp
    code/header/game/Game.h
)

add_library(Player
    code/src/game/Player.cpp
    code/header/game/Player.h
)

add_library(HumanPlayer
    code/src/game/HumanPlayer.cpp
    code/header/game/HumanPlayer.h
)

add_library(PcPlayer
    code/src/game/PcPlayer.cpp
    code/header/game/PcPlayer.h
)

add_library(Log
    code/src/utilities/Log.cpp
    code/header/utilities/Log.h
)

add_executable(scacchiera
    code/main.cpp
)
add_executable(replay
    code/Replay.cpp
)

target_link_libraries(ChessBoard
    Rook 
    Bishop
    Dummy
    King
    Knight
    Pawn 
    Queen 
    ChessPiece
)

target_link_libraries(Queen
    DirectionalPieces
)

target_link_libraries(Game
    ChessBoard
    Player
    HumanPlayer
    PcPlayer
    Log
    ManagePosition
)

target_link_libraries(Player
    ManagePosition
)

target_link_libraries(HumanPlayer
    Player
)

target_link_libraries(PcPlayer
    Player
)

target_link_libraries(scacchiera
    ChessBoard
    Game
)

target_link_libraries(replay
    ManagePosition
)
