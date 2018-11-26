#ifndef _Pos
#define _Pos
#include "constants.h"
class Pos{
    public:
    int x;
    int y;
    Pos(int argx,int argy);
    int getShiftNumber(void);
    bitboard toBitBoard(void);
};
#endif