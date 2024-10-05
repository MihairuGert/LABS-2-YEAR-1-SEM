#include "Grid.h"

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
