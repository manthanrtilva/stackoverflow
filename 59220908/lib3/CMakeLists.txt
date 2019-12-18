
add_library(lib3 SHARED lib3.cpp)
target_include_directories(lib3 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
