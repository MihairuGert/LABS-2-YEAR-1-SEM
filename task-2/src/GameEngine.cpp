#include "GameEngine.h"

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
