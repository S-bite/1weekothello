#include <iostream>
#include "BitBoardUtil.hpp"
#include "constants.h"
void printBoard(bitboard b){
    for(int i=63;i>=0;i--){
        std::cout<<((b>>i)&1)<<((i%8==0)?"\n":" ");
    }
    return ;
}
int numOfBits(bitboard b){
    b = (b & 0x55555555) + (b >> 1 & 0x55555555);
    b = (b & 0x33333333) + (b >> 2 & 0x33333333);
    b = (b & 0x0f0f0f0f) + (b >> 4 & 0x0f0f0f0f);
    b = (b & 0x00ff00ff) + (b >> 8 & 0x00ff00ff);
    return (b & 0x0000ffff) + (b >>16 & 0x0000ffff);
};

