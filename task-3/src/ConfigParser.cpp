#include "ConfigParser.h"

Cmd* ConfigParser::getCommand() {
    std::string line;
    std::getline(*in, line, '\n');
    if (line[0] == '#') {
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
            throw ExceptionMSG("wrong_time_interval");
        }
        Cmd* cmd = new Cmd("MUTE", {begin, end}, -1);
        return cmd;
    }
    else {
        throw ExceptionMSG("command_does_not_exists");
    }
}

std::string Cmd::getCmdName() const noexcept {
    return cmdName;
}

std::vector<int> Cmd::getInterval() const noexcept {
    return interval;
}
