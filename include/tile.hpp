#pragma once
#include <iostream>

class tile {
    public:
        tile(int startColour);
        int getColour();
        int setColour(int inColour);
    private:
        int colour;
};