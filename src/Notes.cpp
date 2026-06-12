#include <iostream>
#include "Notes.h"

Notes::Notes(sqlite3* dataBase) {
    db = dataBase;
}
// метод добавление записи
void Notes::addNote(const std::string &title, const std::string &content) {
    const char* sql =
    "INSERT INTO notes "
    "(title, content, created_at)"
    "VALUES(?,?,datetime('now'))";

    sqlite3_stmt* stmt;
    // проверка на подготовленность запроса
    if(sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr) != SQLITE_OK) {
        std::cout << "1";
        return;
    }
    // передать строку
    sqlite3_bind_text(stmt, 1, title.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,content.c_str(),-1,SQLITE_TRANSIENT);

    // проверка полной передачи данных
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "2";
        return;
    }
    
    sqlite3_finalize(stmt);
}

// метод получения записей
std::vector<Note> Notes::getAllNote() {
    std::vector<Note> notes;

    const char* sql = 
    "SELECT id, title, content, created_at "
    "FROM notes;";

    sqlite3_stmt* stmt;

    // проверка на подготовленность запроса
    if(sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr) != SQLITE_OK) {
        std::cout << "1";
        return;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        Note note;

        note.id = sqlite3_column_int(stmt,0);

        note.title = sqlite3_column_int(stmt,1);

        note.content = sqlite3_column_int(stmt,2);

        note.created_at = sqlite3_column_int(stmt,3);

        notes.push_back(note);
    }
    sqlite3_finalize(stmt);
    return notes;
}