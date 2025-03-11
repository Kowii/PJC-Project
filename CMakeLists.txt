cmake_minimum_required(VERSION 3.25)
project(projektBaza)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.0.0
)
FetchContent_MakeAvailable(fmt)
add_executable(projektBaza main.cpp
        tabela.hpp
        tabela.cpp)
target_link_libraries(projektBaza fmt)