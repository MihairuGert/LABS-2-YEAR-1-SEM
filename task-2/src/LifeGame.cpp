#include "LifeGame.h"

void LifeGame::startGame() {
    grid1.setElement(0,2, true);
    grid1.setElement(1,2, true);
    grid1.setElement(2,2, true);
    grid1.setElement(2,1, true);
    grid1.setElement(1,0, true);
    GameEngine gameEngine = GameEngine({3},{2,3}); // make custom
    grid1.printGrid();
    std::cout << '\n';
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    for (int i = 0; i < 100; ++i) {
        gameEngine.computeNext(grid1, grid2);
        grid2.printGrid();
        std::cout << '\n';
        sleep_for(milliseconds (500));//
        grid1 = grid2;
    }
}

LifeGame::LifeGame(int column, int row) {
    this->row = row;
    this->column = column;
    grid1 = Grid(10,10);
    grid2 = Grid(10,10);
}
