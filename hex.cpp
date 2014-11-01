#include "hex.h"

Hex::Hex(int row, int column) : _row(row), _column(column)
{
    for (int i = 0; i < 6; i++)
        _neighbors[i] = 0;
}
