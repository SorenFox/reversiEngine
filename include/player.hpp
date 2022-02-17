#pragma once
#include <vector>
#include <time.h>
#include <cmath>
#include <memory>
#include "board.hpp"
#include "referee.hpp"
#include "player.hpp"

class player {
  public:
    virtual float move(int playerColour, board* _board, referee* _ref, int recurDepth, int maxDepth, float abStandard) =0;
};