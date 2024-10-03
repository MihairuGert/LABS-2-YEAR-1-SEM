#pragma once
#include "Grid.h"
#include "Cell.h"

class GameEngine {
private:
    std::vector<Cell> aliveCellList;
    int countNeighbors(Grid& grid, int x, int y);
public:
    void addAliveCell(int x, int y);
    void computeNext(Grid& grid1, Grid& grid2);
    void countAliveCells(Grid& grid);
};
