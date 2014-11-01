#include "hex.h"

#include <iostream>

Hex::Hex(int row, int column) : _row(row), _column(column)
{
    for (int i = 0; i < 6; i++)
        _neighbors[i] = 0;
}

void Hex::traverseTo(Hex *dst, int count)
{
    // been visited and already has a faster route
    if (_distance > -1 && _distance < count)
        return;

     _distance = count;

    if (dst == this)
        return;

    //std::cout << count << std::endl;

    // traverse neighbors
    for (int i = 0; i < 6; i++) {
        if (_neighbors[i])
            _neighbors[i]->traverseTo(dst, count+1);
    }

}
