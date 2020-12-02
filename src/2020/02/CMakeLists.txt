add_executable(02 main.cpp)

add_custom_command(TARGET 02 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/input.txt)