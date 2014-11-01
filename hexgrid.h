#ifndef HEXGRID_H
#define HEXGRID_H

#include "hex.h"

class HexGrid
{
public:
    HexGrid(int width, int height);
    ~HexGrid();
    int width() { return _width; }
    int height() { return _height; }
    Hex* hex(int row, int column) { return _grid[row][column]; }
private:
    void createNeighbors();

    int _width;
    int _height;
    Hex*** _grid;
};

#endif // HEXGRID_H
