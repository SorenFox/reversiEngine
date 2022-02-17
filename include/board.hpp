#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "tile.hpp"

// represents the reversi board
class board {
    public:
        board(int x, int y, int turn);
        int isInBounds(int x, int y);
        int getXSize();
        int getYSize();
        int getColour(int x, int y);
        int getNumTiles();
        int getSum();
        int placeTile(int playerColour, int x, int y);
        board* copyBoard();
    private:
        std::vector<std::vector<std::shared_ptr<tile>>> boardArray;
        int playerTurn;
        int xSize, ySize;
};