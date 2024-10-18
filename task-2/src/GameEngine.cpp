#include "GameEngine.h"

bool Grid::getElement(int columnInd, int rowInd) const{
    return grid[rowInd][columnInd];
}

void Grid::setElement(int columnInd, int rowInd, bool value) {
    grid[rowInd][columnInd] = value;
}

void Grid::clear() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            grid[i][j] = false;
        }
    }
}

void Grid::createGrid() {
    grid.resize(row);
    for (int i = 0; i < row; ++i) {
        grid[i].resize(column);
    }
    clear();
}

Grid::Grid(int row, int column) {
    this->row = row;
    this->column = column;
    createGrid();
}

Grid::Grid() {}

int Grid::getColumn() const {
    return column;
}

int Grid::getRow() const {
    return row;
}

std::vector<std::vector<bool>> Grid::getGrid() {
    return grid;
}

void GameEngine::computeNext(Grid& grid1, Grid& grid2) {
    grid2.clear();
    for (int i = 0; i < grid1.getRow(); ++i) {
        for (int j = 0; j < grid1.getColumn(); ++j) {
            int neighborsNum = countNeighbors(grid1, j, i);
            if (grid1.getElement(j, i)) {
                if (isSurvived(neighborsNum)) {
                    grid2.setElement(j, i, true);
                }
            }
            else {
                if (isBorn(neighborsNum)) {
                    grid2.setElement(j, i, true);
                }
            }
        }
    }
}

void GameEngine::computeIterations(Grid &grid1, Grid &grid2, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        computeNext(grid1,grid2);
        grid1 = grid2;
    }
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

GameEngine::GameEngine(const std::vector<int>& birthCondition, const std::vector<int>& survivalCondition) {
    this->birthCondition = birthCondition;
    this->survivalCondition = survivalCondition;
}

bool GameEngine::isSurvived(int num) {
    for (auto& i : survivalCondition){
        if (num == i) {
            return true;
        }
    }
    return false;
}

bool GameEngine::isBorn(int num) {
    for (auto& i : birthCondition){
        if (num == i) {
            return true;
        }
    }
    return false;
}
