cmake_minimum_required(VERSION 3.15.0)

project(MediaPlayer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(CMAKE_PREFIX_PATH "c:/Qt/Qt5.12.11/5.12.11/msvc2017_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS REQUIRED
	Widgets 
	Multimedia
	MultimediaWidgets
)

set(SRC_DIR "src")
set(GUI_DIR "${SRC_DIR}/gui")
set(FILE_SYS_DIR "${SRC_DIR}/filesysapi")
set(PLAYER_DIR "${SRC_DIR}/player")
set(PLAYLIST_DIR "${PLAYER_DIR}/playlist")


add_executable(player)

target_sources(player
PRIVATE
	${SRC_DIR}/main.cpp
	${SRC_DIR}/id3reader.cpp
	${FILE_SYS_DIR}/fileSysApi.hpp
	${FILE_SYS_DIR}/fileSysApi.cpp
	${FILE_SYS_DIR}/fileWinSysApi.hpp
	
	${PLAYLIST_DIR}/playlistmodel.hpp
	${PLAYLIST_DIR}/playlistmodel.cpp
	${PLAYLIST_DIR}/playlistgui.hpp
	${PLAYLIST_DIR}/playlistgui.cpp
	# ${PLAYER_DIR}/librarymodel.cpp
	
	# Testing model/view
	# ${GUI_DIR}/player.hpp
	# ${GUI_DIR}/player.cpp
	# ${GUI_DIR}/intListModel.hpp
	# ${GUI_DIR}/intListModel.cpp
)

target_link_libraries(player 
	Qt5::Widgets
	Qt5::Multimedia
	Qt5::MultimediaWidgets
)
