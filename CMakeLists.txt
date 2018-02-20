cmake_minimum_required(VERSION 3.8)
project(hoardingCPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Rules.cpp Rules.h Board.cpp Board.h Player.cpp Player.h Property.cpp Property.h GameState.cpp GameState.h DiceRoller.cpp DiceRoller.h Space.cpp Space.h)
add_executable(hoardingCPP ${SOURCE_FILES})