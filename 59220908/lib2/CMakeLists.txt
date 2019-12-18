
add_library(lib2 SHARED lib2.cpp)
target_include_directories(lib2 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
