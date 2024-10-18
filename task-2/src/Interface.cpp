#include "Interface.h"

void Interface::printInterface(const std::vector<std::vector<bool>>& grid, const std::vector<int>& birthCondition, const std::vector<int>& survivalCondition,
                               const std::string& universeName, int iterationNum, const bool* parseLifeFileStatus) {
    system("cls");
    if (parseLifeFileStatus[1]) {
        std::cout << "ERROR: NO NAME" << '\n';
    }
    if (parseLifeFileStatus[2]) {
        std::cout << "ERROR: NO CONDITIONS" << '\n';
    }
    if (parseLifeFileStatus[3]) {
        std::cout << "ERROR: NO SIZE" << '\n';
    }
    if (parseLifeFileStatus[4]) {
        std::cout << "ERROR: NEGATIVE CELLS" << '\n';
    }
    std::cout << "Universe name: " << universeName << "\nB";
    for (const int i : birthCondition) {
        std::cout << i;
    }
    std::cout << " S";
    for (const int i : survivalCondition) {
        std::cout << i;
    }
    std::cout << "\nIteration: " << iterationNum << '\n';
    printGrid(grid);
}

void Interface::printGrid(const std::vector<std::vector<bool>>& grid) {
    std::cout << " ";
    for (int j = 0; j < grid[0].size(); ++j) {
        std::cout << "__";
    }
    std::cout << "\n";
    for (int i = 0; i < grid.size(); ++i) {
        std::cout << '|';
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j])
                std::cout << "#" << ' ';
            else {
                std::cout << " " << ' ';
            }
        }
        std::cout << "|\n";
    }
    for (int j = 0; j < grid[0].size(); ++j) {
        std::cout << "--";
    }
    std::cout << "\n$  ";
}

Cmd Interface::getCommand() {
    std::string cmdLine;
    std::getline(std::cin, cmdLine);
    Cmd cmd = Cmd(cmdLine);
    return cmd;
}

void Interface::printHelp() {
    std::cout << "\n\ttick[t] <n=int>\tComputes n ticks and shows the final grid in the console.\n"
                 "\tauto <n=int>\tComputes n ticks and shows the grid step by step in the console.\n"
                 "\tdump <filename>\tSaves the universe in the file.\n"
                 "\texit\t\tExits the game.\n"
                 "Press any button to continue...";

}

Cmd::Cmd(const std::string& cmd) {
    // Getting command name.
    name = cmd.substr(0, cmd.find(' '));
    // Getting attributes.
    int start = cmd.find('<');
    int end = cmd.find('>');
    // Checking if there is no attributes.
    if (start == -1 || end == -1) {
        attributesString = "";
        return;
    }
    attributesString = cmd.substr(start, end - start);
}

std::string Cmd::getName() {
    return name;
}

std::string Cmd::getAttributes() {
    return attributesString;
}

