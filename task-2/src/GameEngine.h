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
    bool getElement(int columnInd, int rowInd) const;
    inline void setElement(int columnInd, int rowInd, bool value = true);
    int getRow() const;
    int getColumn() const;
    std::vector<std::vector<bool>> getGrid();
    void clear();
    void createGrid();
};

class GameEngine {
private:
    static int countNeighbors(Grid& grid, int x, int y);
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    bool isSurvived(int num);
    bool isBorn(int num);
public:
    GameEngine(const std::vector<int>& birthCondition, const std::vector<int>& survivalCondition);
    void computeNext(Grid& grid1, Grid& grid2);
    void computeIterations(Grid& grid1, Grid& grid2, int iterations = 1);
};
