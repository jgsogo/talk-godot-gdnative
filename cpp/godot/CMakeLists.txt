cmake_minimum_required(VERSION 3.0)

find_package(godot-cpp REQUIRED)

add_library(godot-game-ia SHARED gdlibrary.cpp godot_ia.h godot_ia.cpp)
target_link_libraries(godot-game-ia PRIVATE godot-cpp::godot-cpp game-ia)
#target_link_libraries(godot-game-ia PRIVATE godot-cpp::godot-cpp)
set_property(TARGET godot-game-ia PROPERTY POSITION_INDEPENDENT_CODE ON)

install(TARGETS godot-game-ia 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(FILES 
            ${CMAKE_CURRENT_LIST_DIR}/godot-game-ia.gdnlib
            ${CMAKE_CURRENT_LIST_DIR}/godot-game-ia.gdns
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
