cmake_minimum_required(VERSION 3.0)

project(Hello)

add_subdirectory(app1)
add_subdirectory(app2)
add_subdirectory(lib1)
add_subdirectory(lib2)
add_subdirectory(lib3)
add_subdirectory(lib4)

add_custom_target(graphviz ALL
    COMMAND ${CMAKE_COMMAND} "--graphviz=foo.dot" .
    COMMAND python ${CMAKE_SOURCE_DIR}/TargetDepsTree.py foo.dot
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)