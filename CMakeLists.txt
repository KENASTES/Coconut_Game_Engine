cmake_minimum_required(VERSION 3.10)
project(My_Custom_Game_Engine VERSION 1.0)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(src src/Core src/Entities src/Graphics)

add_executable(engine ${SOURCES})

target_link_libraries(engine opengl32 gdi32)

add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:engine>/assets
)