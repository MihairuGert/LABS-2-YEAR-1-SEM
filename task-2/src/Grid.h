#pragma once
#include <vector>
#include <iostream>

class Grid {
private:
    std::vector<std::vector<bool>> grid;
    int column;
    int row;
public:
    Grid(int column, int row);
    Grid();
    bool getElement(int columnInd, int rowInd);
    void setElement(int columnInd, int rowInd, bool value);
    int getRow() const;
    int getColumn() const;
    void copy(Grid& grid);
    void clear();
    void createGrid();
    void printGrid();
};
