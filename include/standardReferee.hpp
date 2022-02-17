#pragma once
#include "referee.hpp"

// implements standard Reversi rules
class standardReferee : public referee {
  public:
    void initBoard(board* _board);
    bool isLegalMove(int playerColour, int x, int y, board* _board);
    int handlePlace(int playerColour, int x, int y, board* _board);
  private:
    int checkDirection(int startX, int startY, int incX, int incY, board* _board, int playerColour);
    int flipDirection(int playerColour, int x, int y, int incX, int incY, board* _board);
};