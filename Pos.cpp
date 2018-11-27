#include "Pos.h"
Pos::Pos(int num){
    x=7-(num%8);
    y=7-num/8;

}
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