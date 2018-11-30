#include <iostream>
#include "constants.h"
#include "Pos.h"
#include "Board.h"
#include "search.hpp"
#include "BitBoardUtil.hpp"
using std::cout;
using std::endl;
using std::max;
using std::min;

Pos search(Board b)
{
    Pos ret = {-1, -1};
    int maxScore = -1ll << 10;
    Board t = b;
    bitboard legal = t.getLegalBoard();
    for (int i = 0; i < 64; i++)
    {
        if (((legal >> i) & 1) != 0)
        {
            t.putStone(Pos(i));
            int score = -evalDeeply(t, MAXDEPTH, 0, -MAXSCORE, MAXSCORE); //手番が相手側なので、評価を反転する
            if (score > maxScore)
            {
                maxScore = score;
                ret = Pos(i);
            }
            t = b;
        }
    }
    cout << "best score: " << maxScore << endl;
    return ret;
}

int evalDeeply(Board b, int maxDepth, int currentDepth, int alpha, int beta)
{
    bool DBGF = true;
    bool rootTrun = (currentDepth % 2 == 0); //0 2 4 ...番目がsearchで呼び出した方のターンになる
    int bestScore = (rootTrun) ? -MAXSCORE : MAXSCORE;
    Board t = b;
    bitboard legal = b.getLegalBoard();
    if (currentDepth == maxDepth or legal == 0)
        return (currentDepth % 2 == 0) ? b.eval() : b.eval(); //葉がrootと同じ色であることを前提に作っているので、評価値の調節をする
    for (int i = 0; i < 64; i++)
    {
        if (((legal >> i) & 1) == 1)
        {
            t.putStone(Pos(i));
            int score = evalDeeply(t, maxDepth, currentDepth + 1, alpha, beta);
            if (rootTrun)
            {
                bestScore = max(bestScore, score);

                if (bestScore > alpha)
                {
                    cout << "beta cut" << endl;
                    return bestScore;
                }
                else
                    beta = bestScore;
            }
            else
            {
                bestScore = min(bestScore, score);
                if (bestScore < beta)
                {
                    cout << "alpha cut" << endl;
                    return bestScore;
                }
                else
                    alpha = bestScore;
            }
        }
        t = b;
    }
    return bestScore;
}