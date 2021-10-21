# CMakeList.txt : CMake project for calc, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("calc")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
# Add source to this project's executable.
add_executable (calc "calc.h" "calc.cpp" "main.cpp" "scanner.h" "token.h" "scanner.cpp" "parser.h" "parser.cpp" "evaluator.h" "evaluator.cpp" "plugin_loader.h" "plugin_loader.cpp")

# TODO: Add tests and install targets if needed.
add_subdirectory(trigonometry)
add_subdirectory(pow)