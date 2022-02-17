#include "../include/standardReferee.hpp"

// places two white and two black pieces in middle of an (8x8) board
// ymmv with a different board size, good luck
void standardReferee::initBoard(board* _board) {
    int x = _board->getXSize();
    int y = _board->getYSize();

    /*if (x % 2 == 0 || y % 2 == 0) {*/
        _board->placeTile(-1, x/2-1, y/2-1);
        _board->placeTile(-1, x/2, y/2);
        _board->placeTile(1, x/2, y/2-1);
        _board->placeTile(1, x/2-1, y/2);
    /*} else { // other starting pattern; limits legal moves on rest of board
        _board->placeTile(-1, x/2-1, y/2-1);
        _board->placeTile(-1, x/2, y/2-1);
        _board->placeTile(-1, x/2, y/2+1);
        _board->placeTile(-1, x/2+1, y/2+1);
        _board->placeTile(1, x/2+1, y/2-1);
        _board->placeTile(1, x/2+1, y/2);
        _board->placeTile(1, x/2-1, y/2);
        _board->placeTile(1, x/2-1, y/2+1);
    }*/
}

// check if a move is legal by standard rules
bool standardReferee::isLegalMove(int playerColour, int x, int y, board* _board) {
    int legal = 0;
    int i, j;

    i = x;
    j = y;

    if ((_board->isInBounds(x,y)) && (_board->getColour(x,y) == 0)) {
        legal += checkDirection(x, y, 1, 0, _board, playerColour);
        legal += checkDirection(x, y, 1, 1, _board, playerColour);
        legal += checkDirection(x, y, 0, 1, _board, playerColour);
        legal += checkDirection(x, y, -1, 1, _board, playerColour);
        legal += checkDirection(x, y, -1, 0, _board, playerColour);
        legal += checkDirection(x, y, -1, -1, _board, playerColour);
        legal += checkDirection(x, y, 0, -1, _board, playerColour);
        legal += checkDirection(x, y, 1, -1, _board, playerColour);
    }

    return (bool)legal;
}

// when a piece is placed, this function handles flipping the appropriate tiles
int standardReferee::handlePlace(int playerColour, int x, int y, board* _board) {
    int piecesFlipped = 0;
    
    if (checkDirection(x, y, 1, 0, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, 1, 0, _board);
    }
    if (checkDirection(x, y, 1, 1, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, 1, 1, _board);
    }
    if (checkDirection(x, y, 0, 1, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, 0, 1, _board);
    }
    if (checkDirection(x, y, -1, 1, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, -1, 1, _board);
    }
    if (checkDirection(x, y, -1, 0, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, -1, 0, _board);
    }
    if (checkDirection(x, y, -1, -1, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, -1, -1, _board);
    }
    if (checkDirection(x, y, 0, -1, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, 0, -1, _board);
    }
    if (checkDirection(x, y, 1, -1, _board, playerColour)) {
        piecesFlipped += flipDirection(playerColour, x, y, 1, -1, _board);
    }

    return piecesFlipped;
}

// flips all the tiles in a direction until it hits a non-opposing tile
int standardReferee::flipDirection(int playerColour, int x, int y, int incX, int incY, board* _board) {
    int i = x, j = y, iter = -1;
    
    do {
        _board->placeTile(playerColour, i, j);
        i += incX;
        j += incY;
        iter++;
    } while ((_board->isInBounds(i,j)) && (_board->getColour(i,j) == -playerColour));

    return iter;
}

// checks if the piece colours in a particular direction allow a legal move
int standardReferee::checkDirection(int startX, int startY, int incX, int incY, board* _board, int playerColour) {
    int i = startX, j = startY, iter = 0, legal = 0;

    do {
        i += incX;
        j += incY;
        iter++;
    } while ((_board->isInBounds(i,j)) && (_board->getColour(i,j) == -playerColour));

    if ((iter > 1) && (_board->isInBounds(i,j)) && (_board->getColour(i,j) == playerColour)) {
        legal = 1;
    }

    return legal;
}