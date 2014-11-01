#ifndef HEX_H
#define HEX_H

class Hex
{
public:
    Hex(int row, int column);

    void setNorth(Hex* h) { _neighbors[0] = h; }
    void setNortheast(Hex* h) { _neighbors[1] = h; }
    void setSoutheast(Hex* h) { _neighbors[2] = h; }
    void setSouth(Hex* h) { _neighbors[3] = h; }
    void setSouthwest(Hex* h) { _neighbors[4] = h; }
    void setNorthwest(Hex* h) { _neighbors[5] = h; }

    int row() { return _row; }
    int column() { return _column; }
    bool visited() { return _visited; }
    void setVisited(bool v) { _visited = v; }

private:
    Hex* _neighbors[6];
    const int _row;
    const int _column;
    bool _visited;
};

#endif // HEX_H
