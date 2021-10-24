# CMakeList.txt: проект CMake для Client; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Client")

# specify the C++ standart
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Client "Client.cpp" "Client.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
