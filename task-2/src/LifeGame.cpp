#include "LifeGame.h"

void LifeGame::startGame(char** argv) {
    // Reading name, rules, starting cells from file.
    // TODO: ADD CHECKING FOR NULLPTR
    parseLifeFile(argv);
    // Start game with given rules.
    int iterationNum = 0;
    GameEngine gameEngine = GameEngine(birthCondition,survivalCondition);
    Interface interface;
    //gameEngine.computeNext(grid1, grid2);
    GameStatus gameStatus = GameStatus::CONTINUE;
    while (gameStatus == GameStatus::CONTINUE) {
        interface.printInterface(grid1, birthCondition, survivalCondition, universeName, iterationNum);
        Cmd cmd = interface.getCommand();
        gameStatus = processCmd(cmd, gameEngine);
    }
}

bool LifeGame::parseLifeFile(char** argv) {
    FileReader fileReader = FileReader(argv[1]);
    InputInterpreter inputInterpreter;
    // If incorrect format, returns false.
    if (!inputInterpreter.checkFormat(fileReader.getLine())) {
        return false;
    }
    // Getting universe name. //TODO: CHECK IF NAME IS EMPTY
    universeName = inputInterpreter.getName(fileReader.getLine());
    // Getting birth and survival conditions. //TODO: CHECK IF CONDITIONS ARE EMPTY
    std::vector<std::vector<int>> rules = inputInterpreter.getConditions(fileReader.getLine());
    birthCondition = rules[0];
    survivalCondition = rules[1];
    // Getting the grid size.
    std::vector<int> size = inputInterpreter.getSize(fileReader.getLine());
    grid1 = Grid(size[0], size[1]);
    grid2 = Grid(size[0], size[1]);
    // Getting alive cells.
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

GameStatus LifeGame::processCmd(Cmd cmd, GameEngine gameEngine) {
    std::string name = cmd.getName();
    std::string attributes = cmd.getAttributes();
    if (cmd.getName() == "exit") {
        return GameStatus::EXIT;
    }
    if (cmd.getName() == "tick" || cmd.getName() == "t") {
        int attributesInt = std::stoi(attributes.substr(attributes.find('=') + 1, attributes.find('>')));
        gameEngine.computeIterations(grid1,grid2,attributesInt);
    }
    return GameStatus::CONTINUE;
}
