cmake_minimum_required(VERSION 3.15.0)

project(GitGUIApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)

if(WIN32)
	set(CMAKE_PREFIX_PATH "c:/Qt/Qt5.12.11/5.12.11/msvc2017_64")
endif(WIN32)

if(UNIX)
	set(CMAKE_PREFIX_PATH "~/Qt5.12.11/5.12.11/gcc_64")
endif(UNIX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS REQUIRED
	Core
	Widgets 
)

set(SRC_DIR "src")

add_executable(gitgui)

target_sources(gitgui
PRIVATE
	${SRC_DIR}/main.cpp
	${SRC_DIR}/process.cpp
	${SRC_DIR}/startWindow.cpp
	${SRC_DIR}/editGitWindow.cpp
	${SRC_DIR}/viewGitWindow.cpp
	${SRC_DIR}/mainWindow.cpp
	${SRC_DIR}/gitapi.cpp
	${SRC_DIR}/cloneRepoDialog.cpp
	${SRC_DIR}/gitObjects.cpp
	${SRC_DIR}/treeCommitNode.cpp
	${SRC_DIR}/gitRepository.cpp
	${SRC_DIR}/modelCommitTree.cpp
	${SRC_DIR}/modelBranchList.cpp
	${SRC_DIR}/utility.cpp
)

target_link_libraries(gitgui 
	Qt5::Core
	Qt5::Widgets
)
