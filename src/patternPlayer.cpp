#include "../include/patternPlayer.hpp"
#include "../include/render.hpp"

patternPlayer::patternPlayer() {
    srand(time(NULL));
}

// the player decides and makes a move
int patternPlayer::move(int playerColour, board* _board, standardReferee* _ref, int recurDepth, int maxDepth) {
    std::vector<possibleMove> moves;
    board* _nextBoard = _board->copyBoard();
    int x = 0, y = 0, possible = 0;
    int retVal = 1;

    // iterate through board, check move legality, rate on vector
    while (_nextBoard->isInBounds(0,y)) {
        while (_nextBoard->isInBounds(x,y)) {
            if (_ref->isLegalMove(playerColour, x, y, _board)) {
                _nextBoard->placeTile(playerColour, x, y);
                _ref->handlePlace(playerColour, x, y, _nextBoard);

                if (recurDepth < maxDepth) {
                    moves.emplace_back(x, y, move(0-playerColour, _nextBoard, _ref, recurDepth+1, maxDepth));
                } else {
                    moves.emplace_back(x, y, ratePosition(playerColour, _nextBoard));
                }
                
                delete _nextBoard;
                _nextBoard = _board->copyBoard();
                possible++;
            }

            x++;
        }
        y++;
        x = 0;
    }

    if (possible > 0) {
        possibleMove maxRating{moves[0].x, moves[0].y, moves[0].rating};
        
        for (x = 1; x < possible; x++) {
            if (moves[x].rating > maxRating.rating) {
                maxRating.x = moves[x].x;
                maxRating.y = moves[x].y;
                maxRating.rating = moves[x].rating;
            } else if (moves[x].rating == maxRating.rating) {
                if ((rand() % 10) > 5) {
                    maxRating.x = moves[x].x;
                    maxRating.y = moves[x].y;
                    maxRating.rating = moves[x].rating;
                } 
            }
        }

        _board->placeTile(playerColour, maxRating.x, maxRating.y);
        _ref->handlePlace(playerColour, maxRating.x, maxRating.y, _board);
        retVal = maxRating.rating;
    } else if (possible == 0) {
        retVal = -100;
    }

    delete _nextBoard;

    return retVal;
}

// heuristic to rate the desirability of a theoretical position
int patternPlayer::ratePosition(int playerColour, board* _nextBoard) {
    int rating = 0;
    int x = 0, y = 0;
    bool xEven, yEven;

    // iterate through board, balance number of pieces of each colour
    while (_nextBoard->isInBounds(0,y)) {
        while (_nextBoard->isInBounds(x,y)) {
            xEven = (x % 2 == 0);
            yEven = (y % 2 == 0);
            // points for having pieces in a checkerboard pattern
            if (xEven != yEven) {
                rating += _nextBoard->getColour(x,y);
            } else {
                rating -= _nextBoard->getColour(x,y);
            }
            x++;
        }
        y++;
        x = 0;
    }

    return rating;
}