cmake_minimum_required(VERSION 3.20)

project(adversarial_wordle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB project_SRCS src/*.cpp)

add_executable(adversarial_wordle ${project_SRCS})
target_include_directories(adversarial_wordle PRIVATE include)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-D_DEBUG")

file(GLOB text_files src/*.txt)

foreach(CurrentTextFile IN LISTS text_files)
add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CurrentTextFile}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endforeach()