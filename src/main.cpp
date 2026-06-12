#include "Database.h"
#include "Notes.h"

#include <iostream>

int main() {
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