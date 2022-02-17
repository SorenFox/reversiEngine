#include <iostream>
#include <memory>
#include <algorithm>
#include "../include/standardReferee.hpp"
#include "../include/fastPlayer.hpp"
#include "../include/board.hpp"
#include "../include/render.hpp"

int main() {
    std::string usrInput;
    int x, y, colour;
    board* _board;
    referee* _ref = new standardReferee();
    player* _playerNeg = new fastPlayer();
    player* _playerPos = new fastPlayer();
    
    do {
        std::cout << "reversi> ";
        std::cin >> usrInput;
        std::cout << "\n";

        if (usrInput == "board") {
            std::cout << "input board width: ";
            std::cin >> x;
            std::cout << "\n";
            std::cout << "input board height: ";
            std::cin >> y;
            std::cout << "\n";

            _board = new board(x,y,-1);
            _ref->initBoard(_board);
            renderBoard(_board);
        }

        if (usrInput == "pl") {
            scanf("%d %d %d", &colour, &x, &y);

            if (_ref->isLegalMove(colour, x, y, _board)) {
                _ref->handlePlace(colour, x, y, _board);
            }
            renderBoard(_board);
        }

        if (usrInput == "check") {
            printf("check legality of move (colour x y): ");
            scanf("%d %d %d", &colour, &x, &y);

            if (_ref->isLegalMove(colour, x, y, _board)) {
                std::cout << "legal\n";
            } else {
                std::cout << "not legal\n";
            }
        }

        if (usrInput == "playNeg" || usrInput == "pn") {
            float rating = _playerNeg->move(-1, _board, _ref, 0, std::min(7, _board->getXSize() * _board->getYSize() - _board->getNumTiles() - 2), 100);
            renderBoard(_board);
            std::cout << "move rating = " << rating << "\n";
        }

        if (usrInput == "playPos" || usrInput == "pp") {
            float rating = _playerPos->move(1, _board, _ref, 0, std::min(7, _board->getXSize() * _board->getYSize() - _board->getNumTiles() - 2), -100);
            renderBoard(_board);
            std::cout << "move rating = " << rating << "\n";
        }

        // play a fully-automated game at max speed, negative starts
        if (usrInput == "playFullNeg") {
            int neg;
            
            do {
                renderBoard(_board);
                std::cout << "------------\n";
                neg = _playerNeg->move(-1, _board, _ref, 0, std::min(6, _board->getXSize() * _board->getYSize() - _board->getNumTiles() - 2), 100);
                renderBoard(_board);
                std::cout << "------------\n";
            } while (_playerPos->move(1, _board, _ref, 0, std::min(6, _board->getXSize() * _board->getYSize() - _board->getNumTiles() - 2), -100) > -1000 || neg < 1000);
        }

        // play a fully-automated game at max speed, positive starts
        if (usrInput == "playFullPos") {
            int pos;
            
            do {
                renderBoard(_board);
                std::cout << "------------\n";
                pos = _playerPos->move(1, _board, _ref, 0, std::min(6, _board->getXSize() * _board->getYSize() - _board->getNumTiles() - 1), -100);
                renderBoard(_board);
                std::cout << "------------\n";
            } while (_playerNeg->move(-1, _board, _ref, 0, std::min(6, _board->getXSize() * _board->getYSize() - _board->getNumTiles() - 1), 100) < 1000 || pos > -1000);
        }

        if (usrInput == "sum") {
            std::cout << "pieces sum = " << _board->getSum() << "\n";
        }
    } while (usrInput != "exit");

    delete _board;
    delete _ref;
    delete _playerNeg;
    delete _playerPos;

    return 0;
}
