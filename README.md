# ProjectLabC++_Chess

This is a chess game board program developed by the team *C++ mi +* = {Giulio_Codutti; Gabriele_Miotti; Giovanni_Artico}.

[[_TOC_]]

## TODO list

- [ ] Initial steps
  - [x] Init Repo
  - [ ] Main structure of the program
  - [ ] Program headers
  - [ ] BASIC and minimal functioning program
- [ ] Full functioning game
  - [ ] Check check
  - [ ] ChechMate check
  - [ ] Special moves
    - [ ] Castling
    - [ ] Em passant
    - [ ] Promotion
- [ ] Final steps
  - [ ] Replay module
  - [ ] Cross revision
  - [ ] Test
  - [ ] Optimize



## Classes

- ChessPiece
  - King&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**R**
  - Queen&nbsp;&nbsp;**D**
  - Bishop&nbsp;&nbsp;**A**
  - Tower&nbsp;&nbsp;&nbsp;**T**
  - Horse&nbsp;&nbsp;&nbsp;**C**
  - Pawn&nbsp;&nbsp;&nbsp;&nbsp;**P**
- ChessBoard
- Game
- In/Out
- main (not actually a class - RIP java)



## Replay Module

- [ ] Choose format
- [ ] Logging
- [ ] ?? Validate format




## Notes

- Enum with possible special moves
>
- Split the 2 castling cases (kingside/corto, queenside/lungo) and check each indipendently
- Study castling (arrocco) carachteristics
  - NOT if king is checked
  - NOT if king moved
  - NOT if tower moved
  - NOT if king's travel path is under attack
>
- When promoting on promotion, give a choice between queen and horse
>
- Map for triple position repetition, if board exact configuration counter is 3 --> PATTA,
  - It can be cleared after a piece removal or after pawn movement (it can't go back)
