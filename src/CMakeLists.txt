project(battleship)

add_library(
    bs
    bs_grid.cpp
    console_game.cpp
    battleship.cpp
    bs_player.cpp
    human_player.cpp
    slick_player.cpp
)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} bs)