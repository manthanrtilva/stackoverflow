
add_library(lib4 SHARED lib4.cpp)
target_include_directories(lib4 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(lib4 lib3)