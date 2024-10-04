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
    Grid(); // FIXME: PROBABLY IT CAN BE LEFT
    bool getElement(int columnInd, int rowInd);
    void setElement(int columnInd, int rowInd, bool value);
    int getRow() const;
    int getColumn() const;
    void copy(Grid& grid); // TODO: COPY CONSTRUCTOR?
    void clear();
    void createGrid();
    void printGrid(); // TODO: MOVE IT TO INTERFACE CLASS
};
