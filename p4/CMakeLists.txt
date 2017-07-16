cmake_minimum_required(VERSION 3.5)
project(2017_p4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES answer/blackjack.cpp answer/deck.cpp answer/card.cpp answer/hand.cpp answer/player.cpp answer/rand.cpp)

add_executable(2017_p4 ${SOURCE_FILES})