#ifndef _Board
#define _Board
#include "constants.h"
#include "Pos.h"
class Board{
private:
bitboard boardBlack;
bitboard boardWhite;
public:
void setStone(Pos p, color col);
bitboard shiftBoardRight(bitboard b);
bitboard shiftBoardLeft(bitboard b);
bitboard shiftBoardDown(bitboard b);
bitboard shiftBoardUp(bitboard b);
void flip(Pos p,color col);
void draw(void);
};
#endif