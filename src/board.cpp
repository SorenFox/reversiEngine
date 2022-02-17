#include "../include/board.hpp"

board::board(int x, int y, int turn) {
    boardArray.resize(y + 2);
    
    for (int i=0; i<y; i++) {
        for (int j=0; j<x; j++) {
            boardArray[i].emplace_back(new tile(0));
        }
    }

    xSize = x;
    ySize = y;
    playerTurn = turn;
}

int board::getXSize() {
    return xSize;
}

int board::getYSize() {
    return ySize;
}

int board::getNumTiles() {
    int num = 0;

    for (int i=0; i < getYSize(); i++) {
        for (int j=0; j < getXSize(); j++) {
            if (getColour(j,i) != 0) {
                num++;
            }
        }
    }

    return num;
}

int board::getSum() {
    int num = 0;

    for (int i=0; i < getYSize(); i++) {
        for (int j=0; j < getXSize(); j++) {
            num += getColour(j,i);
        }
    }

    return num;
}

board* board::copyBoard() {
    board* _newBoard = new board(xSize, ySize, playerTurn);
    int x, y;

    for (y = 0; y < ySize; y++) {
        for (x = 0; x < xSize; x++) {
            _newBoard->placeTile(getColour(x,y), x, y);
        }
    }

    return _newBoard;
}

int board::placeTile(int playerColour, int x, int y) {
    int retVal = 1;

    if (abs(playerColour) <= 1) {
        boardArray[y][x]->setColour(playerColour);
    } else {
        retVal = 0;
    }

    return retVal;
}

int board::isInBounds(int x, int y) {
    int inBounds = 0;

    if (x >= 0 && x < xSize && y >= 0 && y < ySize) {
        inBounds = 1;
    }

    return inBounds;
}

int board::getColour(int x, int y) {
    return (boardArray[y][x]->getColour());
}