#include <random>
#include <iostream>
#include "constants.h"
#include "Pos.h"
#include "Board.h"
#include "BitBoardUtil.hpp"
#include "search.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<int> rpos(0, 63);
  color mturn;
  string t;
  cout << "type your color (b:black w:white). black play first." << endl;

  cin >> t;
  mturn = (t == "b") ? BLACK : WHITE;

  Board b = Board();
  b.draw();

  while (!b.isFilled())
  {
    if (b.turn == mturn)
    {
      bitboard legal = b.getLegalBoard();
      if (legal == 0)
      {
        cout << "you can't put stone. pass." << endl;
        b.turn = !b.turn;
        continue;
      }
      int x, y;
      std::cin >> x >> y;
      Pos p = {x, y};
      if ((legal >> (p.getShiftNumber()) & 1) == 0)
      {
        cout << "you can't put here." << endl;
        continue;
      }
      b.putStone(p);
      b.draw();
      cout << "black : " << numOfBits(b.boardBlack) << " , white : " << numOfBits(b.boardWhite) << endl;
    }
    else
    {
      bitboard legal = b.getLegalBoard();
      if (legal == 0)
      {
        cout << "CPU can't put stone. pass." << endl;
        b.turn = !b.turn;
        continue;
      }
      //std::cout << b.eval() << std::endl;
      Pos best = search(b);
      b.putStone(best);
      b.draw();
      cout << "black : " << numOfBits(b.boardBlack) << " , white : " << numOfBits(b.boardWhite) << endl;
    }
  }
  b.draw();
  cout << "black : " << numOfBits(b.boardBlack) << " , white : " << numOfBits(b.boardWhite) << endl;
  return 0;
}