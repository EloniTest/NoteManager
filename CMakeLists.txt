cmake_minimum_required(VERSION 3.10.0)
project(NoteManager VERSION 0.1.0 LANGUAGES C CXX)

include_directories(
    include
    lib/sqlite3
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    NoteManager
    src/main.cpp
    src/Database.cpp
    src/Notes.cpp
    lib/sqlite3/sqlite3.c
)

set_property(TARGET NoteManager PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
