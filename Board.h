#ifndef _Board
#define _Board
#include "constants.h"
#include "Pos.h"
class Board{
private:
public:
bitboard boardBlack;
bitboard boardWhite;
color turn;
Board();
void putStone(Pos p);

bitboard shiftBoardRight(bitboard b);
bitboard shiftBoardLeft(bitboard b);
bitboard shiftBoardDown(bitboard b);
bitboard shiftBoardUp(bitboard b);
bitboard shiftBoardRightUp(bitboard b);
bitboard shiftBoardRightDown(bitboard b);
bitboard shiftBoardLeftUp(bitboard b);
bitboard shiftBoardLeftDown(bitboard b);

bitboard getLegalBoard(void);
bool isFilled(void);
void flip(Pos p);
void draw(void);
int eval(void);
};
#endif