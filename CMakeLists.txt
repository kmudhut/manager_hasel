cmake_minimum_required(VERSION 3.27)
project(manager_hasel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(manager_hasel main.cpp
        Tekran.cpp
        Tekran.h
        TBaza_Hasel.cpp
        TBaza_Hasel.h
)
