add_executable(2020_02 main.cpp)

add_custom_command(TARGET 2020_02 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/input.txt)