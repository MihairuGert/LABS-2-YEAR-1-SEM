#include "ConfigParser.h"

Cmd* ConfigParser::getCommand() {
    std::string line;
    std::getline(*in, line, '\n');
    if (line[0] == '#' || line.empty()) {
        Cmd* cmd = new Cmd("COMMENT", {}, -1);
        return cmd;
    }
    std::istringstream istrstream(line);
    std::string commandName;
    istrstream >> commandName;
    if (commandName == "mute") {
        int begin;
        int end;
        istrstream >> begin >> end;
        if (begin < 0 || end < 0) {
            throw ExceptionMSG("incorrect_time_interval");
        }
        Cmd* cmd = new Cmd("MUTE", {begin, end}, -1);
        return cmd;
    }
    if (commandName == "mix") {
        int begin;
        std::string input;
        istrstream >> input >> begin;
        int inputIndex = stoi(input.substr(1));
        if (begin < 0) {
            throw ExceptionMSG("incorrect_time_interval");
        }
        if (inputIndex < 1) {
            throw ExceptionMSG("incorrect_input_file_index");
        }
        Cmd* cmd = new Cmd("MIX", {begin, -1}, inputIndex);
        return cmd;
    }
    else {
        throw ExceptionMSG("command_does_not_exist");
    }
}

std::string Cmd::getCmdName() const noexcept {
    return cmdName;
}

std::vector<int> Cmd::getInterval() const noexcept {
    return interval;
}

int Cmd::getInputIndex() const noexcept {
    return inputIndex;
}
