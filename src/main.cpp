#include "Database.h"
#include "Notes.h"

#include <iostream>
#include <windows.h>
int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // test
    dataBase db("notes.db");

    
    // добавление заметки
    Notes note(db.getConnection());

    note.addNote("Изучить SQLite","Разобраться в его ебучем непонятном синтаксисе");

    auto allNotes = note.getAllNote();

    for(const auto& note : allNotes) {
        std::cout 
        << note.id << "\n"
        << note.title << "\n"
        << note.content << "\n"
        << note.created_at << "\n\n";
    }

    return 0;
}