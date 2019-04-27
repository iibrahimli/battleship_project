project(battleship_test)

add_executable(tests main.cpp)
target_link_libraries(tests cppunit bs)

enable_testing()

add_test(all ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)