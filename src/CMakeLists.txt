project(battleship)

add_library(bs battleship.cpp bs_grid.cpp bs_player.cpp human_player.cpp console_game.cpp)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} bs)