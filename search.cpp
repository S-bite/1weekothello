#include "constants.h"
#include "Pos.h"
#include "Board.h"
Pos search(Board b){
    Pos ret={-1,-1};
    int maxScore=-64;
    Board t=b;
    bitboard legal=t.getLegalBoard();
    for (int i=0;i<64;i++){
        if (((legal>>i)&1)!=0){
            t.putStone(Pos(i));
            int score=-t.eval(); //手番が相手側なので、評価を反転する
            if (score>maxScore){ 
                maxScore=score;
                ret=Pos(i);
            }
            t=b;
        }
    
    }
    return ret;
}