#include <random>

#include <iostream>
#include "constants.h"
#include "Pos.h"
#include "Board.h"
#include "BitBoardUtil.hpp"
#include "search.hpp"

using namespace std;
int weight[64] = {100, -40, 20, 5, 5, 20, -40, 100,
                  -40, -80, -1, -1, -1, -1, -80, -40,
                  20, -1, 5, 1, 1, 5, -1, 20,
                  5, -1, 1, 0, 0, 1, -1, 5,
                  5, -1, 1, 0, 0, 1, -1, 5,
                  20, -1, 5, 1, 1, 5, -1, 20,
                  -40, -80, -1, -1, -1, -1, -80, -40,
                  100, -40, 20, 5, 5, 20, -40, 100};

Board::Board()
{
  boardBlack = 0x0;
  boardBlack |= (bitboard)1 << 28;
  boardBlack |= (bitboard)1 << 35;
  boardWhite = 0x0;
  boardWhite |= (bitboard)1 << 27;
  boardWhite |= (bitboard)1 << 36;

  turn = BLACK;
}
void Board::putStone(Pos p)
{
  if (turn == BLACK)
  { //black
    boardBlack |= 1ll << p.getShiftNumber();
  }
  else
  { //white
    boardWhite |= 1ll << p.getShiftNumber();
  }
  Board::flip(p);
  turn = !turn;
  return;
}
bitboard Board::shiftBoardRight(bitboard b)
{
  return (b >> 1) & (bitboard)0x7f7f7f7f7f7f7f7f;
}
bitboard Board::shiftBoardLeft(bitboard b)
{
  return (b << 1) & (bitboard)0xfefefefefefefefe;
}
bitboard Board::shiftBoardDown(bitboard b)
{
  return (b >> 8) & (bitboard)0x00ffffffffffffff;
}
bitboard Board::shiftBoardUp(bitboard b)
{
  return (b << 8) & (bitboard)0xffffffffffffff00;
}

bitboard Board::shiftBoardRightUp(bitboard b)
{
  return Board::shiftBoardRight(Board::shiftBoardUp(b));
}
bitboard Board::shiftBoardRightDown(bitboard b)
{
  return Board::shiftBoardRight(Board::shiftBoardDown(b));
}
bitboard Board::shiftBoardLeftUp(bitboard b)
{
  return Board::shiftBoardLeft(Board::shiftBoardUp(b));
}

bitboard Board::shiftBoardLeftDown(bitboard b)
{
  return Board::shiftBoardLeft(Board::shiftBoardDown(b));
}

bitboard Board::getLegalBoard(void)
{
  bitboard leagalBoard = 0x0000000000000000;
  bitboard blankBoard = ~(boardBlack | boardWhite);
  color mcol = turn;
  color ecol = !mcol;
  bitboard mboard = (mcol == BLACK) ? boardBlack : boardWhite;
  bitboard eboard = (ecol == BLACK) ? boardBlack : boardWhite;

  bitboard mtmp = mboard;
  mtmp = (eboard & shiftBoardRight(mtmp));
  mtmp |= (eboard & shiftBoardRight(mtmp));
  mtmp |= (eboard & shiftBoardRight(mtmp));
  mtmp |= (eboard & shiftBoardRight(mtmp));
  mtmp |= (eboard & shiftBoardRight(mtmp));
  mtmp |= (eboard & shiftBoardRight(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardRight(mtmp)));

  mtmp = mboard;
  mtmp = (eboard & shiftBoardLeft(mtmp));
  mtmp |= (eboard & shiftBoardLeft(mtmp));
  mtmp |= (eboard & shiftBoardLeft(mtmp));

  mtmp |= (eboard & shiftBoardLeft(mtmp));
  mtmp |= (eboard & shiftBoardLeft(mtmp));
  mtmp |= (eboard & shiftBoardLeft(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardLeft(mtmp)));

  mtmp = mboard;
  mtmp = (eboard & shiftBoardUp(mtmp));
  mtmp |= (eboard & shiftBoardUp(mtmp));
  mtmp |= (eboard & shiftBoardUp(mtmp));
  mtmp |= (eboard & shiftBoardUp(mtmp));
  mtmp |= (eboard & shiftBoardUp(mtmp));
  mtmp |= (eboard & shiftBoardUp(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardUp(mtmp)));

  mtmp = mboard;
  mtmp = (eboard & shiftBoardDown(mtmp));
  mtmp |= (eboard & shiftBoardDown(mtmp));
  mtmp |= (eboard & shiftBoardDown(mtmp));
  mtmp |= (eboard & shiftBoardDown(mtmp));
  mtmp |= (eboard & shiftBoardDown(mtmp));
  mtmp |= (eboard & shiftBoardDown(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardDown(mtmp)));

  mtmp = mboard;
  mtmp = (eboard & shiftBoardRightUp(mtmp));
  mtmp |= (eboard & shiftBoardRightUp(mtmp));
  mtmp |= (eboard & shiftBoardRightUp(mtmp));
  mtmp |= (eboard & shiftBoardRightUp(mtmp));
  mtmp |= (eboard & shiftBoardRightUp(mtmp));
  mtmp |= (eboard & shiftBoardRightUp(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardRightUp(mtmp)));

  mtmp = mboard;
  mtmp = (eboard & shiftBoardRightDown(mtmp));
  mtmp |= (eboard & shiftBoardRightDown(mtmp));
  mtmp |= (eboard & shiftBoardRightDown(mtmp));
  mtmp |= (eboard & shiftBoardRightDown(mtmp));
  mtmp |= (eboard & shiftBoardRightDown(mtmp));
  mtmp |= (eboard & shiftBoardRightDown(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardRightDown(mtmp)));

  mtmp = mboard;
  mtmp = (eboard & shiftBoardLeftUp(mtmp));
  mtmp |= (eboard & shiftBoardLeftUp(mtmp));
  mtmp |= (eboard & shiftBoardLeftUp(mtmp));
  mtmp |= (eboard & shiftBoardLeftUp(mtmp));
  mtmp |= (eboard & shiftBoardLeftUp(mtmp));
  mtmp |= (eboard & shiftBoardLeftUp(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardLeftUp(mtmp)));

  mtmp = mboard;
  mtmp = (eboard & shiftBoardLeftDown(mtmp));
  mtmp |= (eboard & shiftBoardLeftDown(mtmp));
  mtmp |= (eboard & shiftBoardLeftDown(mtmp));
  mtmp |= (eboard & shiftBoardLeftDown(mtmp));
  mtmp |= (eboard & shiftBoardLeftDown(mtmp));
  mtmp |= (eboard & shiftBoardLeftDown(mtmp));
  leagalBoard |= (blankBoard & (shiftBoardLeftDown(mtmp)));

  return leagalBoard;
}

bool Board::isFilled()
{
  return (boardBlack | boardWhite) == (bitboard)0xffffffffffffffff;
}
void Board::flip(Pos p)
{
  color mcol = turn;
  color ecol = !mcol;
  bitboard &mboard = (mcol == BLACK) ? boardBlack : boardWhite;
  bitboard &eboard = (ecol == BLACK) ? boardBlack : boardWhite;

  //    std::cout<<"Right"<<std::endl;
  bitboard mtmp = mboard;
  bitboard etmp = eboard;
  bitboard mask = p.toBitBoard();
  mask = shiftBoardRight(mask);
  while ((mask != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardRight(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  //    std::cout<<"Left"<<std::endl;
  mtmp = mboard;
  etmp = eboard;
  mask = p.toBitBoard();
  mask = shiftBoardLeft(mask);
  while ((mask != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardLeft(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  //    std::cout<<"Up"<<std::endl;
  mtmp = mboard;
  etmp = eboard;
  mask = p.toBitBoard();
  mask = shiftBoardUp(mask);
  while ((mask != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardUp(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  //    std::cout<<"Down"<<std::endl;
  mtmp = mboard;
  etmp = eboard;
  mask = p.toBitBoard();
  mask = shiftBoardDown(mask);
  while ((mask != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardDown(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  //    std::cout<<"RightUp"<<std::endl;
  mtmp = mboard;
  etmp = eboard;
  mask = p.toBitBoard();
  mask = shiftBoardRightUp(mask);
  while (((mask & eboard) != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardRightUp(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  //    std::cout<<"RightDown"<<std::endl;
  mtmp = mboard;
  etmp = eboard;
  mask = p.toBitBoard();
  mask = shiftBoardRightDown(mask);
  while ((mask != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardRightDown(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  //    std::cout<<"LeftUp"<<std::endl;
  mtmp = mboard;
  etmp = eboard;
  mask = p.toBitBoard();
  mask = shiftBoardLeftUp(mask);
  while ((mask != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardLeftUp(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  //    std::cout<<"LeftDown"<<std::endl;
  mtmp = mboard;
  etmp = eboard;
  mask = p.toBitBoard();
  mask = shiftBoardLeftDown(mask);
  while ((mask != 0) && ((mask & eboard) != 0))
  {
    mtmp ^= mask;
    etmp ^= mask;
    mask = shiftBoardLeftDown(mask);
  }
  if ((mask & mboard) != 0)
  {
    eboard = etmp;
    mboard = mtmp;
  }

  return;
}

int Board::eval()
{
  color mcol = turn;
  color ecol = !mcol;
  bitboard mboard = (mcol == BLACK) ? boardBlack : boardWhite;
  bitboard eboard = (ecol == BLACK) ? boardBlack : boardWhite;
  if (isFilled())
    return (numOfBits(mboard) > numOfBits(eboard)) ? MAXSCORE : -MAXSCORE;
  int mscore = 0, escore = 0;
  for (int i = 0; i < 64; i++)
  {
    if (((mboard >> i) & 1) == 1)
      mscore += weight[i];
    if (((eboard >> i) & 1) == 1)
      escore += weight[i];
  }
  return mscore - escore;
}

void Board::draw(void)
{
  std::cout << "   0 1 2 3 4 5 6 7" << std::endl;
  std::cout << "  -----------------" << std::endl;
  for (int i = 63; i >= 0; i--)
  {
    if (i % 8 == 7)
      std::cout << (7 - i / 8) << " ";
    char c = ' ';
    if ((boardBlack >> i) & 1ll == 1)
      c = 'x';
    if ((boardWhite >> i) & 1ll == 1)
      c = 'o';
    std::cout << ":" << c;
    if (i % 8 == 0)
      std::cout << ":" << std::endl
                << "  -----------------" << std::endl;
  }
  return;
}
