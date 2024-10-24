#pragma once

#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include "Command.h"
#include "JobHandler.h"

class Command;

class CommandExecutor {
public:
    explicit CommandExecutor(pid_t &pid) : child_pid(pid) {}

    void execArgs(const Command &);

    void execArgsPiped(const std::vector<Command> &);

private:
    void execute(const Command &) const;

    pid_t &child_pid;
};
