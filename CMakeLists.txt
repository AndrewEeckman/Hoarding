cmake_minimum_required(VERSION 3.9)
project(hoardingCPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(hoardingCPP
        All3s.txt
        Board.cpp
        Board.h
        CampusBoard.csv
        DiceRoller.cpp
        DiceRoller.h
        GameState.cpp
        GameState.h
        main.cpp
        makefile
        Player.cpp
        Player.h
        Property.cpp
        Property.h
        RandomNums10000.txt
        Rules.cpp
        Rules.h
        Rules.txt
        Space.cpp
        Space.h)
