#include "../include/tile.hpp"

tile::tile(int startColour) {
    tile::setColour(startColour);
}

int tile::getColour() {
    return colour;
}

int tile::setColour(int inColour) {
    if (inColour == -1 || inColour == 1 || inColour == 0) {
        colour = inColour;
    } else {
    }

    return 1;
}