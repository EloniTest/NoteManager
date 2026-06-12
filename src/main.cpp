#include "dataBase.h"
#include "Notes.h";

int main() {
    // test
    dataBase db("notes.db");

    
    // добавление заметки
    Notes note(db.getConnection());

    note.addNote("Изучить SQLite","Разобраться в его ебучем непонятном синтаксисе");

    

    return 0;
}