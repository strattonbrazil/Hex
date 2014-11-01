#include "hexgrid.h"

HexGrid::HexGrid(int width, int height)
{
    _width = width;
    _height = height;

    _grid = new Hex**[_height];
    for (int row = 0; row < _height; row++) {
        _grid[row] = new Hex*[_width];
        for (int column = 0; column < _width; column++)
            _grid[row][column] = new Hex(row, column);
    }

    createNeighbors();
}

HexGrid::~HexGrid()
{
    for (int row = 0; row < _height; row++) {
        delete[] _grid[row];
    }
    delete[] _grid;
}

void HexGrid::createNeighbors()
{
    for (int row = 0; row < _height; row++) {
        for (int column = 0; column < _width; column++) {
            Hex* hex = _grid[row][column];
            if (row != 0) {
                hex->setNorth(_grid[row-1][column]);
            } else if (row != _height - 1) {
                hex->setSouth(_grid[row + 1][column]);
            }

            bool lowered = column % 2 == 1;
            if (column != 0) { // make west connections
                if (lowered) {
                    hex->setNorthwest(_grid [row][column - 1]);
                    if (row != _height - 1)
                        hex->setSouthwest(_grid[row + 1][column - 1]);
                } else {
                   if (row != 0)
                        hex->setNorthwest(_grid[row - 1][column - 1]);
                    hex->setSouthwest(_grid[row][column - 1]);
                }
            } else if (column != _width - 1) { // make east connections
                if (lowered) {
                    hex->setNortheast(_grid[row][column + 1]);
                    if (row != _height - 1)
                        hex->setSoutheast(_grid [row + 1] [column + 1]);
                } else {
                    if (row != 0)
                        hex->setNortheast(_grid [row - 1] [column + 1]);
                    hex->setSoutheast(_grid [row][column + 1]);
                }
            }
        }
    }
}

QLinkedList<Hex*> HexGrid::findPath(QPoint startP, QPoint endP)
{
    Hex* start = _grid[startP.x()][startP.y()];
    Hex* end = _grid[endP.y()][endP.y()];
}
