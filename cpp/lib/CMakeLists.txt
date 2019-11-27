
cmake_minimum_required(VERSION 3.0)

find_package(tgbot REQUIRED)

add_library(game-ia STATIC ia.h ia.cpp)
target_link_libraries(game-ia PRIVATE tgbot::tgbot)

install(TARGETS game-ia 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
