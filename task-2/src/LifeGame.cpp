#include "LifeGame.h"

void LifeGame::startGame(char** argv) {
    // Reading name, rules, starting cells from file.
    // TODO: ADD CHECKING FOR NULLPTR
    parseLifeFile(argv);
    // Start game with given rules.
    GameEngine gameEngine = GameEngine(birthCondition,survivalCondition);
    grid1.printGrid();
    std::cout << '\n';
    using namespace std::this_thread;
    using namespace std::chrono;
    for (int i = 0; i < 1000; ++i) {
        gameEngine.computeNext(grid1, grid2);
        system("cls");
        grid2.printGrid();
        std::cout << '\n';
        //std::getchar();
        sleep_for(milliseconds (100));//
        grid1 = grid2;
    }
}

bool LifeGame::parseLifeFile(char** argv) {
    FileReader fileReader = FileReader(argv[1]);
    InputInterpreter inputInterpreter;
    if (!inputInterpreter.checkFormat(fileReader.getLine())) {
        return false;
    }
    std::string universeName = inputInterpreter.getName(fileReader.getLine());
    std::vector<std::vector<int>> rules = inputInterpreter.getConditions(fileReader.getLine());
    std::vector<int> size = inputInterpreter.getSize(fileReader.getLine());
    grid1 = Grid(size[0], size[1]);
    grid2 = Grid(size[0], size[1]);
    birthCondition = rules[0];
    survivalCondition = rules[1];
    std::string line;
    while (true) {
        line = fileReader.getLine();
        if (line.empty()) {
            break;
        }
        std::vector<int> cells = inputInterpreter.getCell(line);
        grid1.setElement(cells[0], cells[1], true);
    }
    return true;
}
