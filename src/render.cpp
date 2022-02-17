#include "../include/render.hpp"
#include <iostream>

// renders a text version of the board
void renderBoard(board* _board) {
    int x = 0, y = 0;

    while (_board->isInBounds(0,y)) {
        while (_board->isInBounds(x,y)) {
            if (_board->getColour(x,y) == -1) {
                std::wcout << "| @ ";
            } else if (_board->getColour(x,y) == 1) {
                std::cout << "| O ";
            } else {
                std::cout << "|   ";
            }

            x++;
        }

        std::cout << "|\n";
        
        x = 0;
        while (_board->isInBounds(x,y)) {
            std::cout << "----";
            x++;
        }
        
        std::cout << "\n";
        y++;
        x = 0;
    }
}