#include<iostream>
#include "constants.h"
#include "Pos.h"
#include "Board.h"
using namespace std;

void Board::setStone(Pos p, color col){
      if (col){ //black
          boardBlack|=1ll<<p.getShiftNumber();
      }else{    //white
          boardWhite|=1ll<<p.getShiftNumber();
      }
      return;
  }
bitboard Board::shiftBoardRight(bitboard b){
  return (b>>1)&(bitboard)0x7f7f7f7f7f7f7f7f;
}
bitboard Board::shiftBoardLeft(bitboard b){
  return (b<<1)&(bitboard)0xfefefefefefefefe;
}
bitboard Board::shiftBoardDown(bitboard b){
  return (b>>8)&(bitboard)0xffffffffffffffff;
}
bitboard Board::shiftBoardUp(bitboard b){
  return (b<<8)&(bitboard)0xffffffffffffffff;
}

void Board::flip(Pos p,color mcol){
    color ecol=!mcol;
    bitboard &mboard=(mcol==BLACK)?boardBlack:boardWhite;
    bitboard &eboard=(ecol==BLACK)?boardBlack:boardWhite;
    bitboard mtmp=mboard;
    bitboard etmp=eboard;
    bitboard mask=p.toBitBoard();
    mask=shiftBoardRight(mask);
    while ((mask!=0) && (mask&eboard!=0)){
    mtmp^=mask;
    etmp^=masl;
    mask=shiftBoardRight(mask);  
    }
    if (mask!=0){
      eboard=etmp;
      mboard=mtmp;
    }
    
    return;
  }
void Board::draw(void){
    std::cout<<"+--------+"<<std::endl;
    for (int i=63;i>=0;i--){
        if (i%8==7) std::cout<<"|";
        char c=' ';
        if ((boardBlack>>i)&1ll==1) c='x';
        if ((boardWhite>>i)&1ll==1) c='o';
        std::cout<<c;
        if (i%8==0)std::cout<<"|"<<std::endl;
    }

    std::cout<<"+--------+"<<std::endl;
    return;
}



int main(){
  
  int a=0;
  int &b=a;
  int c=b;
  c=111;
  b=222;
  std::cout<<"a:"<<a<<",b:"<<b<<",c:"<<c<<std::endl;
  //Board b= Board();
  //b.draw();
  return 0;
}