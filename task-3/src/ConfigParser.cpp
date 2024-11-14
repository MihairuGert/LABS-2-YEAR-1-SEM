#include "ConfigParser.h"

Cmd* ConfigParser::getCommand() {
    std::string line;
    std::getline(*in, line, '\n');
    if (line[0] == '#' || line.empty()) {
        Cmd* cmd = new Cmd("COMMENT", {});
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
        Cmd* cmd = new Cmd("MUTE", {begin, end});
        return cmd;
    }
    if (commandName == "boost") {
        int begin;
        int end;
        double coef;
        istrstream >> begin >> end >> coef;
        if (begin < 0 || end < 0) {
            throw ExceptionMSG("incorrect_time_interval");
        }
        if (coef <= 0) {
            throw ExceptionMSG("incorrect_boost_coef");
        }
        Cmd* cmd = new Cmd("BOOST", {begin, end}, -1, coef);
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
        Cmd* cmd = new Cmd("MIX", {begin}, inputIndex);
        return cmd;
    }
    else {
        throw ExceptionMSG("command_does_not_exist");
    }
}

std::string Cmd::getCmdName() const {
    return cmdName;
}

std::vector<int> Cmd::getInterval() const {
    return interval;
}

int Cmd::getInputIndex() const {
    return inputIndex;
}

double Cmd::getCoef() const {
    return doubleArg;
}
