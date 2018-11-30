#ifndef _Search
#define _Search
#include "constants.h"
#include "Pos.h"
#include "Board.h"
Pos search(Board b);
int evalDeeply(Board b, int maxDepth, int currentDepth, int alpha, int beta);

#endif