# CMakeList.txt: проект CMake для Srever; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Srever")

# specify the C++ standart
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Srever "Serever.cpp" "Serever.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
