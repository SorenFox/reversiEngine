#pragma once
#include "board.hpp"
#include "standardReferee.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#ifndef POSMOVE
#define POSMOVE
typedef struct pMove {
    int x, y;
    int rating;

    // define constructor
    pMove(int x, int y, int rating): x(x), y(y), rating(rating) {}
} possibleMove;
#endif

class patternPlayer {
    public:
        patternPlayer();
        int move(int playerColour, board* _board, standardReferee* _ref, int recurDepth, int maxDepth);
    private:
        int ratePosition(int playerColour, board* _nextBoard);
};