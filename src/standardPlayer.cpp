#include "../include/standardPlayer.hpp"
#include "../include/render.hpp"

standardPlayer::standardPlayer() {
    srand(time(NULL));
}

// the player decides and makes a move
moveStats* standardPlayer::move(int playerColour, board* _board, standardReferee* _ref, int recurDepth, int maxDepth) {
    std::vector<possibleMove*> moves;
    board* _nextBoard = _board->copyBoard();
    int x = 0, y = 0, possible = 0;
    moveStats* retVal = (moveStats*)malloc(sizeof(moveStats));
    double avg;

    // iterate through board, check move legality, rate on vector
    while (_nextBoard->isInBounds(0,y)) {
        while (_nextBoard->isInBounds(x,y)) {
            if (_ref->isLegalMove(playerColour, x, y, _board)) {
                _nextBoard->placeTile(playerColour, x, y);
                _ref->handlePlace(playerColour, x, y, _nextBoard);

                if (recurDepth < maxDepth) {
                    moves.emplace_back(new possibleMove{x, y, move(0-playerColour, _nextBoard, _ref, recurDepth+1, maxDepth)});
                } else {
                    moves.emplace_back(new possibleMove{x, y, ratePosition(playerColour, _nextBoard)});
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

    // find the moves with the best rating
    if (possible > 0) {
        moveStats rating1{moves[0]->rating->min, moves[0]->rating->max, moves[0]->rating->avg};
        moveStats rating2{moves[0]->rating->min, moves[0]->rating->max, moves[0]->rating->avg};
        possibleMove maxRating{moves[0]->x, moves[0]->y, &rating1};
        possibleMove minRating{moves[0]->x, moves[0]->y, &rating2};
        
        for (x = 1; x < possible; x++) {
            // maximum rating of all possible moves
            if (moves[x]->rating->max > maxRating.rating->max) {
                maxRating.x = moves[x]->x;
                maxRating.y = moves[x]->y;
                maxRating.rating->max = moves[x]->rating->max;
                maxRating.rating->min = moves[x]->rating->min;
                maxRating.rating->avg = moves[x]->rating->avg;
            } else if (moves[x]->rating->max == maxRating.rating->max) {
                if ((rand() % 10) > 5) {
                    maxRating.x = moves[x]->x;
                    maxRating.y = moves[x]->y;
                    maxRating.rating->max = moves[x]->rating->max;
                    maxRating.rating->min = moves[x]->rating->min;
                    maxRating.rating->avg = moves[x]->rating->avg;
                } 
            }
            
            // minimum rating of all possible moves
            if (moves[x]->rating->min < minRating.rating->min) {
                minRating.x = moves[x]->x;
                minRating.y = moves[x]->y;
                minRating.rating->max = moves[x]->rating->max;
                minRating.rating->min = moves[x]->rating->min;
                minRating.rating->avg = moves[x]->rating->avg;

            } else if (moves[x]->rating->min == minRating.rating->min) {
                if ((rand() % 10) > 5) {
                    minRating.x = moves[x]->x;
                    minRating.y = moves[x]->y;
                    minRating.rating->max = moves[x]->rating->max;
                    minRating.rating->min = moves[x]->rating->min;
                    minRating.rating->avg = moves[x]->rating->avg;
                } 
            }
            // start calculating the average
            avg += moves[x]->rating->avg;
            std::cout << moves[x]->rating->avg << std::endl;

            // free the move memory
            free(moves[x]->rating);
            delete moves[x];
        }

        // complete the average calculation
        avg = (int)round(avg/possible);
        
        // make a move based on data n statistics n stuff
        if (playerColour == 1) {
            _ref->handlePlace(playerColour, maxRating.x, maxRating.y, _board);
        } else {
            _ref->handlePlace(playerColour, minRating.x, minRating.y, _board);
        }

        // update return value
        retVal->max = maxRating.rating->max;
        retVal->min = minRating.rating->min;
        retVal->avg = avg;
    } else if (possible == 0) {
        retVal->max = playerColour * -100;
        retVal->min = playerColour * -100;
        retVal->avg = playerColour * -100;
    }

    delete _nextBoard;

    return retVal;
}

// heuristic to rate the desirability of a theoretical position
moveStats* standardPlayer::ratePosition(int playerColour, board* _nextBoard) {
    int rating = 0;
    int x = 0, y = 0;

    // iterate through board, balance number of pieces of each colour
    while (_nextBoard->isInBounds(0,y)) {
        while (_nextBoard->isInBounds(x,y)) {
            // additional points for corners
            if ((x == 0 && y == 0) || (x == 0 && y+1 == _nextBoard->getYSize()) || (x+1 == _nextBoard->getXSize() && y == 0) || (x+1 == _nextBoard->getXSize() && y+1 == _nextBoard->getYSize())) {
                rating += 10 * _nextBoard->getColour(x,y);
            }
            // additional points for edges
            if (x == 0 || y == 0 || x+1 == _nextBoard->getXSize() || y+1 == _nextBoard->getYSize()) {
                rating += _nextBoard->getColour(x,y);
            }
            // points for having more pieces
            rating += _nextBoard->getColour(x,y);
            x++;
        }
        y++;
        x = 0;
    }

    // rating *= playerColour; // account for the player colour
    moveStats* stats = (moveStats*)malloc(sizeof(moveStats));
    stats->avg = rating;
    stats->min = rating;
    stats->max = rating;

    return stats;
}