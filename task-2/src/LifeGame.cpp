#include "LifeGame.h"

void LifeGame::runOffline(bool* parseLifeFileStatus) {
    GameEngine gameEngine = GameEngine(grid1, birthCondition,survivalCondition);
    grid1 = gameEngine.computeIterations(iterationsOffline);
    filename += ".life";
    createLifeFile(filename);
}

void LifeGame::runOnline(bool* parseLifeFileStatus) {
    GameEngine gameEngine = GameEngine(grid1, birthCondition,survivalCondition);
    GameStatus gameStatus = GameStatus::CONTINUE;
    while (gameStatus == GameStatus::CONTINUE) {
        Interface::printInterface(grid1.getGrid(), birthCondition, survivalCondition, universeName, iterationNum, parseLifeFileStatus);
        Cmd cmd = Interface::getCommand();
        gameStatus = processCmd(cmd, gameEngine, parseLifeFileStatus);
    }
}

void LifeGame::startGame() {
    if (parseFileStatus == ParseFileStatus::NO_FORMAT) {
        std::cout << "ERROR: WRONG FILE FORMAT.\nPress any button to continue...";
        std::getchar();
        return;
    }
    // If no file is provided, generates universe and runs online mode.
    if (parseFileStatus == ParseFileStatus::GENERATE) {
        generateUniverse();
    }
    // Offline mode.
    if (parseFileStatus == ParseFileStatus::OFFLINE) {
        // Reading name, rules, starting cells from file.
        runOffline(parseLifeFileStatus);
        return;
    }
    // Start game with given rules.
    runOnline(parseLifeFileStatus);
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
        grid1 = gameEngine.computeIterations(attributesInt);
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
            grid1 = gameEngine.computeIterations();
            Interface::printInterface(grid1.getGrid(), birthCondition, survivalCondition, universeName, iterationNum, parseLifeFileStatus);
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

void LifeGame::generateUniverse() {
    srand(time(0));
    int variant = rand() % 5;
    column = DEFAULT_SIZE;
    row = DEFAULT_SIZE;
    grid1 = Grid(DEFAULT_SIZE,DEFAULT_SIZE);
    grid2 = Grid(DEFAULT_SIZE,DEFAULT_SIZE);
    birthCondition = {3};
    survivalCondition = {2,3};
    switch (variant) {
        case 0:
            universeName = "Glider Gun";
            Generator::createGliderGun(grid1);
            break;
        case 1:
            universeName = "Pulsar";
            Generator::createPulsar(grid1);
            break;
        case 2:
            universeName = "R-Pentomino";
            Generator::createRPentamino(grid1);
            break;
        case 3:
            universeName = "Lightweight spaceship";
            Generator::createLightWeightSS(grid1);
            break;
        case 4:
            universeName = "Block-Laying Switch Engine";
            Generator::createBlockLayingSE(grid1);
            break;
        default:
            throw 1;
    }
}

LifeGame::LifeGame(std::vector<int> birthCondition, std::vector<int> survivalCondition, int row, int column, Grid grid1,
                   std::string universeName, ParseFileStatus parseFileStatus, bool* parseLifeFileStatus,
                   std::string filename, int iterationsOffline) {
    this->birthCondition = birthCondition;
    this->survivalCondition = survivalCondition;
    this->row = row;
    this->column = column;
    this->grid1 = grid1;
    this->universeName = universeName;
    this->parseFileStatus = parseFileStatus;
    this->filename = filename;
    this->iterationsOffline = iterationsOffline;
    this->parseLifeFileStatus = parseLifeFileStatus;
}

void Generator::createGliderGun(Grid &grid) {
    grid.setElement(1, 5);
    grid.setElement(1, 6);
    grid.setElement(2, 5);
    grid.setElement(2, 6);
    grid.setElement(11, 5);
    grid.setElement(11, 6);
    grid.setElement(11, 7);
    grid.setElement(12, 4);
    grid.setElement(12, 8);
    grid.setElement(13, 3);
    grid.setElement(13, 9);
    grid.setElement(14, 3);
    grid.setElement(14, 9);
    grid.setElement(15, 6);
    grid.setElement(16, 4);
    grid.setElement(16, 8);
    grid.setElement(17, 5);
    grid.setElement(17, 6);
    grid.setElement(17, 7);
    grid.setElement(18, 6);
    grid.setElement(21, 3);
    grid.setElement(21, 4);
    grid.setElement(21, 5);
    grid.setElement(22, 3);
    grid.setElement(22, 4);
    grid.setElement(22, 5);
    grid.setElement(23, 2);
    grid.setElement(23, 6);
    grid.setElement(25, 1);
    grid.setElement(25, 2);
    grid.setElement(25, 6);
    grid.setElement(25, 7);
    grid.setElement(35, 3);
    grid.setElement(35, 4);
    grid.setElement(36, 3);
    grid.setElement(36, 4);
}

void Generator::createPulsar(Grid &grid) {
    int offset = DEFAULT_SIZE / 3;
    grid.setElement(2 + offset, 4 + offset);
    grid.setElement(2 + offset, 5 + offset);
    grid.setElement(2 + offset, 6 + offset);
    grid.setElement(2 + offset, 10 + offset);
    grid.setElement(2 + offset, 11 + offset);
    grid.setElement(2 + offset, 12 + offset);
    grid.setElement(4 + offset, 2 + offset);
    grid.setElement(4 + offset, 7 + offset);
    grid.setElement(4 + offset, 9 + offset);
    grid.setElement(4 + offset, 14 + offset);
    grid.setElement(5 + offset, 2 + offset);
    grid.setElement(5 + offset, 7 + offset);
    grid.setElement(5 + offset, 9 + offset);
    grid.setElement(5 + offset, 14 + offset);
    grid.setElement(6 + offset, 2 + offset);
    grid.setElement(6 + offset, 7 + offset);
    grid.setElement(6 + offset, 9 + offset);
    grid.setElement(6 + offset, 14 + offset);
    grid.setElement(7 + offset, 4 + offset);
    grid.setElement(7 + offset, 5 + offset);
    grid.setElement(7 + offset, 6 + offset);
    grid.setElement(7 + offset, 10 + offset);
    grid.setElement(7 + offset, 11 + offset);
    grid.setElement(7 + offset, 12 + offset);
    grid.setElement(9 + offset, 4 + offset);
    grid.setElement(9 + offset, 5 + offset);
    grid.setElement(9 + offset, 6 + offset);
    grid.setElement(9 + offset, 10 + offset);
    grid.setElement(9 + offset, 11 + offset);
    grid.setElement(9 + offset, 12 + offset);
    grid.setElement(10 + offset, 2 + offset);
    grid.setElement(10 + offset, 7 + offset);
    grid.setElement(10 + offset, 9 + offset);
    grid.setElement(10 + offset, 14 + offset);
    grid.setElement(11 + offset, 2 + offset);
    grid.setElement(11 + offset, 7 + offset);
    grid.setElement(11 + offset, 9 + offset);
    grid.setElement(11 + offset, 14 + offset);
    grid.setElement(12 + offset, 2 + offset);
    grid.setElement(12 + offset, 7 + offset);
    grid.setElement(12 + offset, 9 + offset);
    grid.setElement(12 + offset, 14 + offset);
    grid.setElement(14 + offset, 4 + offset);
    grid.setElement(14 + offset, 5 + offset);
    grid.setElement(14 + offset, 6 + offset);
    grid.setElement(14 + offset, 10 + offset);
    grid.setElement(14 + offset, 11 + offset);
    grid.setElement(14 + offset, 12 + offset);
}

void Generator::createRPentamino(Grid &grid) {
    int offset = DEFAULT_SIZE / 2;
    grid.setElement(1 + offset, 2 + offset);
    grid.setElement(2 + offset, 1 + offset);
    grid.setElement(2 + offset, 2 + offset);
    grid.setElement(3 + offset, 1 + offset);
    grid.setElement(2 + offset, 3 + offset);
}

void Generator::createLightWeightSS(Grid &grid) {
    int offset = DEFAULT_SIZE / 2;
    grid.setElement(1 + offset, 0 + offset);
    grid.setElement(4 + offset, 0 + offset);
    grid.setElement(0 + offset, 1 + offset);
    grid.setElement(0 + offset, 2 + offset);
    grid.setElement(0 + offset, 3 + offset);
    grid.setElement(1 + offset, 3 + offset);
    grid.setElement(2 + offset, 3 + offset);
    grid.setElement(3 + offset, 3 + offset);
    grid.setElement(4 + offset, 2 + offset);
}

void Generator::createBlockLayingSE(Grid &grid) {
    int offset = DEFAULT_SIZE / 3;
    grid.setElement(2 + offset, 2 + offset);
    grid.setElement(2 + offset, 3 + offset);
    grid.setElement(3 + offset, 1 + offset);
    grid.setElement(3 + offset, 4 + offset);
    grid.setElement(4 + offset, 4 + offset);
    grid.setElement(5 + offset, 1 + offset);
    grid.setElement(5 + offset, 4 + offset);
    grid.setElement(6 + offset, 2 + offset);
    grid.setElement(6 + offset, 3 + offset);
    grid.setElement(7 + offset, 3 + offset);
    grid.setElement(8 + offset, 1 + offset);
    grid.setElement(8 + offset, 4 + offset);
    grid.setElement(9 + offset, 2 + offset);
    grid.setElement(9 + offset, 3 + offset);
    grid.setElement(10 + offset, 2 + offset);
    grid.setElement(10 + offset, 3 + offset);
    grid.setElement(11 + offset, 2 + offset);
    grid.setElement(11 + offset, 3 + offset);
}
