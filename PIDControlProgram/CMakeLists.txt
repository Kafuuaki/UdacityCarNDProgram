# for a cmake file, we need to tell cmake
# 1. what is the minimum version of cmake we need
# 2. what is the name of the project
# 3. what is the source file of the project
# 4. what is the executable file of the project
# 5. what is the library file of the project
# 6. what is the include file of the project
# 7. what is the install file of the project
# 8. what is the test file of the project

cmake_minimum_required(VERSION 3.5)

project(PIDController)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")

# q: why do we need set SOURCE
# a: because we need to tell cmake what files to compile
#    and we need to tell cmake what files to link
#    and we need to tell cmake what files to include
#    and we need to tell cmake what files to install
#    and we need to tell cmake what files to test

set(SOURCE
    main.cpp
    ./src/PID.cpp)

# include()

add_executable(PIDController ${SOURCE})

# if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 
    # include_directories(/usr/local/include/uWS)
    # link_directories(/usr/local/lib)

include_directories(
    /usr/local/include
    /opt/homebrew/opt/openssl@3/include
    /opt/homebrew/opt/libuv/include
)

link_directories(
    /usr/local/lib
    /opt/homebrew/opt/openssl@3/lib
    /opt/homebrew/opt/libuv/lib
)


# q: what is a frame work for cmake file
# a: https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html

# q: how to write a good cmake
# a: https://cliutils.gitlab.io/modern-cmake/