#include "LifeGame.h"

void LifeGame::startGame(char** argv) {
    // Reading name, rules, starting cells from file.
    // TODO: CHECK FOR NULLPTR AND NO_FORMAT. GENERATE UNIVERSE IF NEEDED.
    bool parseLifeFileStatus[6] = {0};
    if (parseLifeFile(argv, parseLifeFileStatus) == ParseFileStatus::NO_FORMAT) {
        std::cout << "ERROR: WRONG FILE FORMAT.\nPress any button to continue...";
        std::getchar();
        return;
    }
    // Start game with given rules.
    GameEngine gameEngine = GameEngine(birthCondition,survivalCondition);
    GameStatus gameStatus = GameStatus::CONTINUE;
    while (gameStatus == GameStatus::CONTINUE) {
        Interface::printInterface(grid1, birthCondition, survivalCondition, universeName, iterationNum, parseLifeFileStatus);
        Cmd cmd = Interface::getCommand();
        gameStatus = processCmd(cmd, gameEngine, parseLifeFileStatus);
    }
}

ParseFileStatus LifeGame::parseLifeFile(char** argv, bool* parseLifeFileStatus) {
    FileReader fileReader = FileReader(argv[1]);
    // If incorrect format, returns the error.
    if (!InputInterpreter::checkFormat(fileReader.getLine())) {
        return ParseFileStatus::NO_FORMAT;
    }
    // Flag not to miss a string if any is absent.
    bool isSuccessGetLine = true;
    // Getting universe name.
    std::string fileLine = fileReader.getLine();
    universeName = InputInterpreter::getName(fileLine);
    if (universeName.empty()) {
        parseLifeFileStatus[1] = true;
        universeName = "NO_NAME";
        isSuccessGetLine = false;
    }
    // Getting birth and survival conditions.
    if (isSuccessGetLine) {
        fileLine = fileReader.getLine();
    }
    std::vector<std::vector<int>> rules = InputInterpreter::getConditions(fileLine, parseLifeFileStatus);
    if (parseLifeFileStatus[2]) {
        isSuccessGetLine = false;
    } else {
        isSuccessGetLine = true;
    }
    birthCondition = rules[0];
    survivalCondition = rules[1];
    // Getting the grid size.
    if (isSuccessGetLine) {
        fileLine = fileReader.getLine();
    }
    std::vector<int> size = InputInterpreter::getSize(fileLine, parseLifeFileStatus);
    if (parseLifeFileStatus[3]) {
        isSuccessGetLine = false;
    } else {
        isSuccessGetLine = true;
    }
    column = size[0];
    row = size[1];
    grid1 = Grid(size[0], size[1]);
    grid2 = Grid(size[0], size[1]);
    // Getting alive cells.
    while (true) {
        if (isSuccessGetLine) {
            fileLine = fileReader.getLine();
        }
        if (fileLine.empty()) {
            break;
        }
        std::vector<int> cells = InputInterpreter::getCell(fileLine);
        if (cells[0] < 0 || cells[1] < 0) {
            parseLifeFileStatus[4] = true;
            if (cells[0] < 0) {
                while(cells[0] < 0) {
                    cells[0] += column;
                }
            }
            if (cells[1] < 0) {
                while(cells[1] < 0) {
                    cells[1] += row;
                }
            }
        }
        grid1.setElement(cells[0], cells[1], true);
        isSuccessGetLine = true;
    }
    return ParseFileStatus::SUCCESS;
}

GameStatus LifeGame::processCmd(Cmd cmd, GameEngine gameEngine, bool* parseLifeFileStatus) {
    std::string name = cmd.getName();
    std::string attributes = cmd.getAttributes();
    if (cmd.getName() == "exit") {
        return GameStatus::EXIT;
    }
    if (cmd.getName() == "tick" || cmd.getName() == "t") {
        attributes = attributes.substr(attributes.find('=') + 1, attributes.find('>') - attributes.find('=') + 1);
        if (attributes[0] > '9' || attributes[0] < '0') {
            callHelp();
            return GameStatus::CONTINUE;
        }
        int attributesInt = std::stoi(attributes);
        iterationNum += attributesInt;
        gameEngine.computeIterations(grid1,grid2,attributesInt);
    }
    else if (cmd.getName() == "auto") {
        attributes = attributes.substr(attributes.find('=') + 1, attributes.find('>') - attributes.find('=') + 1);
        if (attributes[0] > '9' || attributes[0] < '0') {
            callHelp();
            return GameStatus::CONTINUE;
        }
        int attributesInt = std::stoi(attributes);
        for (int i = 0; i < attributesInt; ++i) {
            ++iterationNum;
            gameEngine.computeIterations(grid1,grid2);
            Interface::printInterface(grid1, birthCondition, survivalCondition, universeName, iterationNum, parseLifeFileStatus);
        }
    }
    else if (cmd.getName() == "dump") {
        std::string filename = attributes.substr(attributes.find('<') +1, attributes.find('>') - attributes.find('<') - 1) + ".life";
        createLifeFile(filename);
    }
    else {
        callHelp();
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

void LifeGame::callHelp() {
    Interface::printHelp();
    std::getchar();
}
