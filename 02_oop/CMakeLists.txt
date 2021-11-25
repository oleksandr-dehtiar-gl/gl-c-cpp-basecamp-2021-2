cmake_minimum_required(VERSION 3.15.0)

project(MediaPlayer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(CMAKE_PREFIX_PATH "c:/Qt/Qt5.12.11/5.12.11/msvc2017_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS REQUIRED
	Core
	Widgets 
	Multimedia
	MultimediaWidgets
)

set(SRC_DIR "src")
set(MEDIAPLAYER_DIR "${SRC_DIR}/mediaplayer")

set(FILE_SYS_DIR "${SRC_DIR}/filesysapi")
set(MEDIADATA_DIR "${MEDIAPLAYER_DIR}/mediadata")
set(PLAYER_DIR "${MEDIAPLAYER_DIR}/player")
set(PLAYLIST_DIR "${MEDIAPLAYER_DIR}/playlist")
set(LIBRARY_DIR "${MEDIAPLAYER_DIR}/library")

add_executable(player)

target_sources(player
PRIVATE
	${SRC_DIR}/main.cpp
	
	${SRC_DIR}/id3reader.cpp
	
	${FILE_SYS_DIR}/fileSysApi.cpp
	
	${MEDIADATA_DIR}/mediadata.cpp
	
	${PLAYLIST_DIR}/playlistmodel.cpp
	${PLAYLIST_DIR}/playlistgui.cpp
	
	${LIBRARY_DIR}/librarygui.cpp
	${LIBRARY_DIR}/librarymodel.cpp
	
	${PLAYER_DIR}/playergui.cpp
)

target_link_libraries(player 
	Qt5::Core
	Qt5::Widgets
	Qt5::Multimedia
	Qt5::MultimediaWidgets
)
