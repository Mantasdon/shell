#pragma once

#include <array>
#include <string>
#include <vector>

class Command {
public:
    static Command split(const std::string_view &, const std::string &);

    static std::vector<Command> splitCommands(const std::string_view &, const std::string &);

    std::vector<char *> getArguments() const;

    std::string toString() const;

private:
    std::vector<char *> arguments{};
};
