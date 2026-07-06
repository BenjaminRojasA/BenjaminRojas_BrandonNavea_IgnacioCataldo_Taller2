cmake_minimum_required(VERSION 3.14)
project(ReproductorTaller2 CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- ESTA ES LA LÍNEA QUE SOLUCIONA EL ERROR DEL CMD EN WINDOWS ---
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures
        ${CMAKE_CURRENT_SOURCE_DIR}/classes
        ${CMAKE_CURRENT_SOURCE_DIR}/core
)

# Fíjate que aquí ya NO está MaxHeap.cpp, porque los Templates se compilan solos.
set(SOURCES
        core/main.cpp
        core/menus.cpp
        core/Player.cpp
        classes/Song.cpp
        classes/Artist.cpp
)

add_executable(ReproductorTaller2 ${SOURCES})