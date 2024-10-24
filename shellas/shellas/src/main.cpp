#include <iostream>
#include <readline/readline.h>
#include "../headers/Command.h"
#include "../headers/CommandExecutor.h"

auto BLUE_TEXT = "\033[34m";
auto YELLOW_TEXT = "\033[33m";
auto WHITE_TEXT = "\033[0m";
const int MAX_ARG_LEN = 1000;
pid_t child_pid = -1;

std::string printCurrentDirectory() {
    std::array<char, MAX_ARG_LEN> cwd{};
    std::array<char, MAX_ARG_LEN> username{};
    std::array<char, MAX_ARG_LEN> hostname{};

    getlogin_r(username.data(), username.size());
    gethostname(hostname.data(), hostname.size());
    getcwd(cwd.data(), cwd.size());

    std::string dir = std::string(YELLOW_TEXT) + username.data() + "@" + hostname.data()
                      + std::string(BLUE_TEXT) + " ~" + cwd.data() + " $ " + std::string(WHITE_TEXT);
    std::string input = std::string(readline(dir.c_str()));
    std::cout << std::flush;
    return input;
}

bool isChangeDirCommand(const Command &command) {
    return strcmp(command.getArguments()[0], "cd") == 0;
}

void handleChangeDir(const Command &command) {
    if (command.getArguments().size() < 2 || chdir(command.getArguments()[1]) >= 0) {
        return;
    }
    perror("chdir");
}

void executeSingleCommand(const Command &command, CommandExecutor *commandExecutor) {
    if (isChangeDirCommand(command)) {
        handleChangeDir(command);
    } else if (CommandExecutor::isBackgroundTask(command)) {
        commandExecutor->execArgsBackground(command);
    } else {
        commandExecutor->execArgs(command);
    }
}

void handleExecution(const std::string &input, CommandExecutor *commandExecutor) {
    std::vector<Command> commands = Command::splitCommands(input, " | ");
    if (commands.size() > 1) {
        commandExecutor->execArgsPiped(commands);
    } else {
        executeSingleCommand(commands[0], commandExecutor);
    }
}


int main() {
    auto *commandExecutor = new CommandExecutor(child_pid);

    while (true) {
        std::string input = printCurrentDirectory();
        handleExecution(input, commandExecutor);
    }
    return 0;
}
