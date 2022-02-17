#pragma once
#include "board.hpp"
#include "standardReferee.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#ifndef STATS
#define STATS
typedef struct stats {
    int min, max;
    int avg;
    stats(int min, int max, int avg): min(min), max(max), avg(avg) {}
} moveStats;
#endif

#ifndef POSMOVE
#define POSMOVE
typedef struct pMove {
    int x, y;
    moveStats* rating;

    // define constructor
    pMove(int xIn, int yIn, moveStats* ratingIn) {
        x = xIn;
        y = yIn;
        rating = ratingIn;
    }
} possibleMove;
#endif

class standardPlayer {
    public:
        standardPlayer();
        moveStats* move(int playerColour, board* _board, standardReferee* _ref, int recurDepth, int maxDepth);
    private:
        moveStats* ratePosition(int playerColour, board* _nextBoard);
};