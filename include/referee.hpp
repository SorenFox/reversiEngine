#pragma once
#include <iostream>
#include "board.hpp"

class referee {
  public:
    virtual void initBoard(board* _board) =0;
    virtual bool isLegalMove(int playerColour, int x, int y, board* _board) =0;
    virtual int handlePlace(int playerColour, int x, int y, board* _board) =0;
};