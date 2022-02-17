#pragma once
#include <vector>
#include <time.h>
#include <cmath>
#include <memory>
#include "board.hpp"
#include "referee.hpp"
#include "player.hpp"

typedef struct pmove {
    int x, y;
    float rating;

    pmove(int xIn, int yIn, float ratingIn) {
        x = xIn;
        y = yIn;
        rating = ratingIn;
    }
} posMove;

class fastPlayer : public player {
  public:
    fastPlayer();
    float move(int playerColour, board* _board, referee* _ref, int recurDepth, int maxDepth, float abStandard);
  private:
    float rateBoard(board* _board, int playerColour);
};