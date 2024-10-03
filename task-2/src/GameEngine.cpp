#include "GameEngine.h"

void GameEngine::computeNext(Grid& grid1, Grid& grid2) {
    grid2.clear();
    auto aliveCellListCopy = aliveCellList;
    for (auto& cell : aliveCellListCopy) {
        int neighborsNum = countNeighbors(grid1, cell.getX(), cell.getY());
        if (neighborsNum < 2 || neighborsNum > 3) {
            grid2.setElement(cell.getX(), cell.getY(), false);
            for (int i = 0; i < aliveCellList.size(); i++) {
                if (aliveCellList[i].getX() == cell.getX() && aliveCellList[i].getY() == cell.getY()) {
                    aliveCellList.erase(aliveCellList.begin() + i);
                }
            }
        }
        else {
            grid2.setElement(cell.getX(), cell.getY(), true);
        }
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                int x = (cell.getX() + i + grid1.getColumn()) % grid1.getColumn();
                int y = (cell.getY() + j + grid1.getRow()) % grid1.getRow();
                if (!grid1.getElement( x,y)){
                    neighborsNum = countNeighbors(grid1, x, y);
                    if (neighborsNum == 3) {
                        grid2.setElement(x, y, true);
                        aliveCellList.emplace_back(x, y);
                    }
                }
            }
        }
    }
}

void GameEngine::addAliveCell(int x, int y) {
    aliveCellList.emplace_back(x,y);
}

int GameEngine::countNeighbors(Grid& grid, int x, int y) {
    int row = grid.getRow();
    int column = grid.getColumn();
    int sum = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            sum += grid.getElement((x + i + column) % column,(y + j + row) % row);
        }
    }
    // No need to count.
    sum -= grid.getElement(x,y);
    return sum;
}

void GameEngine::countAliveCells(Grid& grid) {
    for (int i = 0; i < grid.getColumn(); ++i) {
        for (int j = 0; j < grid.getRow(); ++j) {
            if (grid.getElement(i,j)) {
                addAliveCell(i,j);
            }
        }
    }
    for (auto i : aliveCellList) {
        std::cout << "(" << i.getX() << " " << i.getY() << ")" << " ";
    }
    std::cout << '\n';
}
