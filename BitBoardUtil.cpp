#include <iostream>
#include "BitBoardUtil.hpp"
#include "constants.h"
void printBoard(bitboard b){
    for(int i=63;i>=0;i--){
        std::cout<<((b>>i)&1)<<((i%8==0)?"\n":" ");
    }
    return ;
}
