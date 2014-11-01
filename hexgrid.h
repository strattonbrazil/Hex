#ifndef HEXGRID_H
#define HEXGRID_H

#include <QPoint>
#include <QLinkedList>

#include "hex.h"

class HexGrid
{
public:
    HexGrid(int width, int height);
    ~HexGrid();
    int width() { return _width; }
    int height() { return _height; }
    Hex* hex(int row, int column) { return _grid[row][column]; }
    QLinkedList<Hex*> findPath(QPoint startP, QPoint endP);
private:
    void createNeighbors();

    int _width;
    int _height;
    Hex*** _grid;
};

#endif // HEXGRID_H
