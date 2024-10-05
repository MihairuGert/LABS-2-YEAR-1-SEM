#include "LifeGame.h"

void LifeGame::startGame(char** argv) {
    // Reading name, rules, starting cells from file.
    // TODO: ADD CHECKING FOR NULLPTR
    parseLifeFile(argv);
    // Start game with given rules.
    GameEngine gameEngine = GameEngine(birthCondition,survivalCondition);
    Interface interface;
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
    column = size[0];
    row = size[1];
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
        // TODO: HANDLE NO ATTRIBUTES OR WRONG ATTRIBUTES.
        int attributesInt = std::stoi(attributes.substr(attributes.find('=') + 1, attributes.find('>') - attributes.find('=') + 1));
        iterationNum += attributesInt;
        gameEngine.computeIterations(grid1,grid2,attributesInt);
    }
    else if (cmd.getName() == "auto") {
        int attributesInt = std::stoi(attributes.substr(attributes.find('=') + 1, attributes.find('>') - attributes.find('=') + 1));
        Interface interface;
        for (int i = 0; i < attributesInt; ++i) {
            ++iterationNum;
            gameEngine.computeIterations(grid1,grid2);
            interface.printInterface(grid1, birthCondition, survivalCondition, universeName, iterationNum);
        }
    }
    else if (cmd.getName() == "help") {
        Interface interface;
        interface.printHelp();
        std::getchar();
    }
    else if (cmd.getName() == "dump") {
        std::string filename = attributes.substr(attributes.find('<') +1, attributes.find('>') - attributes.find('<') - 1) + ".life";
        createLifeFile(filename);
    }
    else {
        Interface interface;
        interface.printHelp();
        std::getchar();
    }
    return GameStatus::CONTINUE;
}

void LifeGame::createLifeFile(const std::string& filename) {
    FilePrinter filePrinter = FilePrinter(filename);
    // Writing file format.
    filePrinter.printString("#Life 1.06\n");
    // Writing universe name.
    filePrinter.printString("#N " + universeName + '\n');
    // Writing universe rules.
    filePrinter.printString("#R ");
    std::string string;
    filePrinter.printString("B");
    for (const int i : birthCondition) {
        string += i + '0';
    }
    string += "/S";
    for (const int i : survivalCondition) {
        string += i + '0';
    }
    filePrinter.printString(string + '\n');
    // Writing universe size.
    filePrinter.printString( "#S C");
    filePrinter.printInt(column);
    filePrinter.printString( "/R");
    filePrinter.printInt(row);
    filePrinter.printString( "\n");
    // Writing alive cells.
    for (int i = 0; i < grid1.getRow(); ++i) {
        for (int j = 0; j < grid1.getColumn(); ++j) {
            if (grid1.getElement(j, i)) {
                filePrinter.printInt(j);
                filePrinter.printString(" ");
                filePrinter.printInt(i);
                filePrinter.printString("\n");
            }
        }
    }
    filePrinter.close();
}
