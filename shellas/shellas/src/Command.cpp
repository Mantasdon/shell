#include <stdexcept>
#include <cstring>
#include "../headers/Command.h"

Command Command::split(const std::string_view &str, const std::string &delimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    std::string token;
    Command result;

    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        if (!token.empty()) {
            auto *arg = new char[token.length() + 1];
            std::strcpy(arg, token.c_str());
            result.arguments.emplace_back(arg);
        }
        pos_start = pos_end + delimiter.length();
    }
    token = str.substr(pos_start);
    if (!token.empty()) {
        auto *arg = new char[token.length() + 1];
        std::strcpy(arg, token.c_str());
        result.arguments.emplace_back(arg);
    }
    result.arguments.emplace_back(nullptr);
    return result;
}

std::vector<Command> Command::splitCommands(const std::string_view &str, const std::string &delimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    std::string token;
    std::vector<Command> commands;

    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delimiter.length();
        commands.push_back(split(token, " "));
    }

    token = str.substr(pos_start);
    commands.push_back(split(token, " "));

    return commands;
}

std::vector<char *> Command::getArguments() const {
    return arguments;
}

std::string Command::toString() const {
    std::string result;
    for (const auto &item: arguments) {
        result += item;
    }
    return result;
}
