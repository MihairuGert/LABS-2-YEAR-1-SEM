#include "Interface.h"

void Interface::printInterface(const Grid& grid, const std::vector<int>& birthCondition, const std::vector<int>& survivalCondition,
                               const std::string& universeName, int iterationNum) {
    system("cls");
    printGrid(grid);
}

void Interface::printGrid(const Grid& grid) {
    std::cout << " ";
    for (int j = 0; j < grid.getColumn(); ++j) {
        std::cout << "__";
    }
    std::cout << "\n";
    for (int i = 0; i < grid.getRow(); ++i) {
        std::cout << '|';
        for (int j = 0; j < grid.getColumn(); ++j) {
            if (grid.getElement(j, i))
                std::cout << "#" << ' ';
            else {
                std::cout << " " << ' ';
            }
        }
        std::cout << "|\n";
    }
    for (int j = 0; j < grid.getColumn(); ++j) {
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

