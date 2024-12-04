cmake_minimum_required(VERSION 3.5.0)

project(Minesweeper)


set(CMAKE_CXX_STANDARD 17)


    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")  # Adjust to where SFML is installed on your Windows machine
    find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)



add_executable(minesweeper
    src/minesweeper.cpp
    src/Button.cpp
    src/GameState.cpp
    src/Tile.cpp
    src/Toolbox.cpp
)


target_link_libraries(minesweeper sfml-graphics sfml-audio)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
