#pragma once

#include <vector>
#include <iostream>

enum class ParseFileStatus {ONLINE = 0, OFFLINE, GENERATE, NO_FORMAT};

class Grid {
private:
    std::vector<std::vector<bool>> grid;
    int column;
    int row;
public:
    Grid(int column, int row);
    Grid();
    bool getElement(int columnInd, int rowInd) const;
    void setElement(int columnInd, int rowInd, bool value = true);
    int getRow() const;
    int getColumn() const;
    std::vector<std::vector<bool>> getGrid();
    void clear();
};

class GameEngine {
private:
    int countNeighbors(int x, int y);
    std::vector<int> birthCondition;
    std::vector<int> survivalCondition;
    Grid grid;
    bool isSurvived(int num);
    bool isBorn(int num);
    void computeNext(Grid& grid);
public:
    GameEngine(Grid grid, const std::vector<int>& birthCondition, const std::vector<int>& survivalCondition);
    Grid computeIterations(int iterations = 1);
};
