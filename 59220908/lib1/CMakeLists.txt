
add_library(lib1 SHARED lib1.cpp)
target_include_directories(lib1 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
