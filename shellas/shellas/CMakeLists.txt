cmake_minimum_required(VERSION 3.26)
project(2_shell)

set(CMAKE_CXX_STANDARD 17)

add_executable(2_shell
        src/main.cpp
        src/Command.cpp
        headers/Command.h
        src/CommandExecutor.cpp
        headers/CommandExecutor.h
        src/JobHandler.cpp
        headers/JobHandler.h
        src/Job.cpp
        headers/Job.h
)

target_link_libraries(2_shell readline)
