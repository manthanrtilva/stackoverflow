cmake_minimum_required(VERSION 3.8.2)

project(helloworld)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Tell CMake to create the helloworld executable
add_executable(helloworld Main.cpp)

# Add the Qt5 Widgets for linking
target_link_libraries(helloworld Qt5::Widgets)