cmake_minimum_required(VERSION 3.0)
project(QtTest)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(testApp main.cpp)

target_link_libraries(testApp Qt5::Widgets)