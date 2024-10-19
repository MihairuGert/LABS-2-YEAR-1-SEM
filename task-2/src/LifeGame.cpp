#include "LifeGame.h"

void LifeGame::runOfflineMode(int argc, char** argv, bool* parseLifeFileStatus) {
    parseLifeFile(argv, parseLifeFileStatus);
    GameEngine gameEngine = GameEngine(birthCondition,survivalCondition);
    std::string filename;
    int iterations = 1;
    processConsole(argc, argv, iterations, filename);
    gameEngine.computeIterations(grid1, grid2, iterations);
    filename += ".life";
    createLifeFile(filename);
}

void LifeGame::runOnlineMode(int argc, char** argv, bool* parseLifeFileStatus) {
    GameEngine gameEngine = GameEngine(birthCondition,survivalCondition);
    GameStatus gameStatus = GameStatus::CONTINUE;
    while (gameStatus == GameStatus::CONTINUE) {
        Interface::printInterface(grid1.getGrid(), birthCondition, survivalCondition, universeName, iterationNum, parseLifeFileStatus);
        Cmd cmd = Interface::getCommand();
        gameStatus = processCmd(cmd, gameEngine, parseLifeFileStatus);
    }
}

void LifeGame::startGame(int argc, char** argv) {
    // If no file is provided, generates universe and runs online mode.
    if (!argv[1] && !argv[2]) {
        generateUniverse();
    }
    bool parseLifeFileStatus[6] = {0};
    // Offline mode.
    if (argv[1] && argv[2]) {
        // Reading name, rules, starting cells from file.
        runOfflineMode(argc, argv, parseLifeFileStatus);
        return;
    }
    // Online mode.
    else if (argv[1] && !argv[2] && parseLifeFile(argv, parseLifeFileStatus) == ParseFileStatus::NO_FORMAT) {
        std::cout << "ERROR: WRONG FILE FORMAT.\nPress any button to continue...";
        std::getchar();
        return;
    }
    // Start game with given rules.
    runOnlineMode(argc, argv, parseLifeFileStatus);
}

void LifeGame::processName(std::string& fileLine, bool *parseLifeFileStatus, bool& isSuccessGetLine) {
    universeName = InputInterpreter::getName(fileLine);
    if (universeName.empty()) {
        parseLifeFileStatus[1] = true;
        universeName = "NO_NAME";
        isSuccessGetLine = false;
    }
}

void LifeGame::processConditions(std::string& fileLine, bool *parseLifeFileStatus, bool& isSuccessGetLine) {
    std::vector<std::vector<int>> rules = InputInterpreter::getConditions(fileLine, parseLifeFileStatus);
    if (parseLifeFileStatus[2]) {
        isSuccessGetLine = false;
    } else {
        isSuccessGetLine = true;
    }
    birthCondition = rules[0];
    survivalCondition = rules[1];
}

void LifeGame::processSize(std::string& fileLine, bool *parseLifeFileStatus, bool& isSuccessGetLine) {
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
}

void LifeGame::processCells(std::string &fileLine, bool *parseLifeFileStatus, bool &isSuccessGetLine) {
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
    grid1.setElement(cells[0], cells[1]);
    isSuccessGetLine = true;
}

ParseFileStatus LifeGame::parseLifeFile(char** argv, bool* parseLifeFileStatus) {
    FileReader fileReader = FileReader(argv[1]);
    // If incorrect format, returns the error.
    if (!InputInterpreter::checkFormat(fileReader.getLine())) {
        return ParseFileStatus::NO_FORMAT;
    }
    // Flag not to miss a string if another is absent.
    bool isSuccessGetLine = true;
    // Getting universe name.
    std::string fileLine;
    fileLine = fileReader.getLine();
    processName(fileLine, parseLifeFileStatus, isSuccessGetLine);
    // Getting birth and survival conditions.
    if (isSuccessGetLine) {
        fileLine = fileReader.getLine();
    }
    processConditions(fileLine, parseLifeFileStatus, isSuccessGetLine);
    // Getting the grid size.
    if (isSuccessGetLine) {
        fileLine = fileReader.getLine();
    }
    processSize(fileLine, parseLifeFileStatus, isSuccessGetLine);
    // Getting alive cells.
    while (true) {
        if (isSuccessGetLine) {
            fileLine = fileReader.getLine();
        }
        if (fileLine.empty()) {
            break;
        }
        processCells(fileLine, parseLifeFileStatus, isSuccessGetLine);
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

void LifeGame::processConsole(int argc, char** argv, int& iterations, std::string& filename) {
    iterations = 1;
    filename = "out";
    for (int i = 0; i < argc; ++i) {
        if (strlen(argv[i]) < 2) {
            return;
        }
        if (argv[i][0] == '-' && argv[i][1] == 'i') {
            ++i;
            if (argv[i][0] > '9' || argv[i][0] < '0') {
                throw 1;
            }
            iterations = std::stoi(argv[i]);
        }
        if (argv[i][0] == '-' && argv[i][1] == 'o') {
            ++i;
            filename = argv[i];
        }
        if (argv[i][0] == '-' && argv[i][1] == '-') {
            std::string string = argv[i];
            std::string command = string.substr(2, string.find('=') - 2);
            if (command == "iterations") {
                if (string[string.find('=') + 1] > '9' || string[string.find('=') + 1] < '0') {
                    throw 1;
                }
                iterations = std::stoi(string.substr(string.find('=') + 1));
            }
            else if (command == "output") {
                filename = string.substr(string.find('=') + 1);
            }
        }
    }
}

void LifeGame::generateUniverse() {
    srand(time(0));
    int variant = rand() % 3;
    column = DEFAULT_SIZE;
    row = DEFAULT_SIZE;
    grid1 = Grid(DEFAULT_SIZE,DEFAULT_SIZE);
    grid2 = Grid(DEFAULT_SIZE,DEFAULT_SIZE);
    birthCondition = {3};
    survivalCondition = {2,3};
    switch (variant) {
        case 0:
            universeName = "Glider Gun";
            createGliderGun(grid1);
            break;
        case 1:
            universeName = "Pulsar";
            createPulsar(grid1);
            break;
        case 2:
            universeName = "R-Pentomino";
            createRPentamino(grid1);
            break;
        default:
            throw 1;
    }
}

void LifeGame::createGliderGun(Grid &grid) {
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

void LifeGame::createPulsar(Grid &grid) {
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

void LifeGame::createRPentamino(Grid &grid) {
    int offset = DEFAULT_SIZE / 2;
    grid.setElement(1 + offset, 2 + offset);
    grid.setElement(2 + offset, 1 + offset);
    grid.setElement(2 + offset, 2 + offset);
    grid.setElement(3 + offset, 1 + offset);
    grid.setElement(2 + offset, 3 + offset);
}
