#include "../include/fastPlayer.hpp"
#include "../include/render.hpp"

fastPlayer::fastPlayer() {
    srand(time(NULL));
}

float fastPlayer::move(int playerColour, board* _board, referee* _ref, int recurDepth, int maxDepth, float abStandard) {
    board* _nextBoard = _board->copyBoard();
    std::unique_ptr<posMove> bestMove(new posMove{0, 0, (float)((-1000) * playerColour)});
    std::unique_ptr<posMove> tempMove;
    int x = 0, y = 0, possible = 0;
    float retVal = 0;
    bool abPrune = false;

    while (_nextBoard->isInBounds(0,y)) {
        while (_nextBoard->isInBounds(x,y)) {
            // check for alpha-beta prune and move legality
            if (_ref->isLegalMove(playerColour, x, y, _board)) {

                // true: prune the current branch. false: keep going.
                abPrune = ((playerColour == 1) && (bestMove->rating > abStandard)) || ((playerColour == -1) && (bestMove->rating < abStandard));

                _ref->handlePlace(playerColour, x, y, _nextBoard);

                // find ratings or recur to find average ratings
                if (!abPrune && (recurDepth < maxDepth)) {
                    tempMove.reset(new posMove{x, y, move(0-playerColour, _nextBoard, _ref, recurDepth+1, maxDepth, bestMove->rating)});
                } else {
                    tempMove.reset(new posMove{x, y, rateBoard(_nextBoard, playerColour)});
                    /*std::cout << possible << ", rating: " << tempMove->rating << ":\n";
                    renderBoard(_nextBoard);*/
                }

                // decide whether the new move is better than the current best move
                if (abs(tempMove->rating - bestMove->rating) < 0.001) {
                    if ((recurDepth == 0) && (rand() % 10 > 7)) {
                        bestMove = std::move(tempMove); // bestMove now points to the current move
                        //std::cout << playerColour << " x: " << bestMove->x << " y: " << bestMove->y << "\n";
                    }
                } else if ((playerColour == 1) && (tempMove->rating > bestMove->rating) || (possible == 0)) { // forces best move to the first possible move
                    bestMove = std::move(tempMove);
                    //std::cout << playerColour << " x: " << bestMove->x << " y: " << bestMove->y << "\n";
                } else if ((playerColour == -1) && (tempMove->rating < bestMove->rating)) {
                    bestMove = std::move(tempMove);
                    //std::cout << playerColour << " x: " << bestMove->x << " y: " << bestMove->y << "\n";
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

    if (possible == 0) { // check if no legal moves available
        retVal = -1000 * playerColour;
    } else { // if there are legal moves
        // place the piece in the best known spot
        _ref->handlePlace(playerColour, bestMove->x, bestMove->y, _board);

        // complete the calculation of the 'goodness' of this route
        retVal = bestMove->rating;
    }

    delete _nextBoard;

    return retVal;
}

float fastPlayer::rateBoard(board* _board, int playerColour) {
    float rating = 0;
    int x = 0, y = 0;

    // iterate through board, balance number of pieces of each colour
    while (_board->isInBounds(0,y)) {
        while (_board->isInBounds(x,y)) {
            // additional points for corners
            if ((x == 0 && y == 0) || (x == 0 && y+1 == _board->getYSize()) || (x+1 == _board->getXSize() && y == 0) || (x+1 == _board->getXSize() && y+1 == _board->getYSize())) {
                rating += 6 * _board->getColour(x,y);
            }
            // additional points for edges
            if (x == 0 || y == 0 || x+1 == _board->getXSize() || y+1 == _board->getYSize()) {
                rating += 2 * _board->getColour(x,y);
            }
            // points for having more pieces
            rating += _board->getColour(x,y);
            x++;
        }
        y++;
        x = 0;
    }

    return rating;
}