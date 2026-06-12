cmake_minimum_required(VERSION 3.10.0)
project(NoteManager VERSION 0.1.0 LANGUAGES C CXX)

include_directories(
    include
    lib/sqlite3
)

add_executable(
    NoteManager
    src/main.cpp
    src/Database.cpp
    src/Notes.cpp
    lib/sqlite3/sqlite3.c
)

