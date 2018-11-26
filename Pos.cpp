#include "Pos.h"
Pos::Pos(int argx,int argy){
    x=argx;
    y=argy;
}
int Pos::getShiftNumber(void){
return 63-8*y-x;
}

bitboard Pos::toBitBoard(void){
return (bitboard)1<<(63-8*y-x);
}