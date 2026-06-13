#include <iostream>
#include "Notes.h"

Notes::Notes(sqlite3* dataBase) {
    db = dataBase;
    // навайбкодено для исправления ошибки "no such table: notes"
    if (db) {
        const char* createTableSql =
            "CREATE TABLE IF NOT EXISTS notes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT NOT NULL, "
            "content TEXT NOT NULL, "
            "created_at TEXT NOT NULL" 
            ");";

        char* errMsg = nullptr;
        if (sqlite3_exec(db, createTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cout << "SQLite error creating table: " << (errMsg ? errMsg : "unknown") << "\n";
            if (errMsg) {
                sqlite3_free(errMsg);
            }
        }
    }
}
// метод добавление записи
void Notes::addNote(const std::string &title, const std::string &content) {
    const char* sql =
    "INSERT INTO notes "
    "(title, content, created_at)"
    "VALUES(?,?,datetime('now'))";

    sqlite3_stmt* stmt;
    if (!db) {
        std::cout << "SQLite error: database connection is not open\n";
        return;
    }
    // проверка на подготовленность запроса
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "SQLite error: " << sqlite3_errmsg(db) << "\n";
        return;
    }
    // передать строку
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, content.c_str(), -1, SQLITE_TRANSIENT);

    // проверка полной передачи данных
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "SQLite error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_finalize(stmt);
        return;
    }
    
    sqlite3_finalize(stmt);
}
// метод обновление записи
void Notes::updateNote(int id, const std::string &title, const std::string &content) {
    const char* sql =
    "UPDATE notes SET title = ?, content = ? WHERE id = ?";

    sqlite3_stmt* stmt;
    if (!db) {
        std::cout << "SQLite error: database connection is not open\n";
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "SQLite error: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, content.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "SQLite error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
}

void Notes::removeNote(int id) {
    const char* sql =
    "DELETE FROM notes WHERE id = ?";

    sqlite3_stmt* stmt;
    if (!db) {
        std::cout << "SQLite error: database connection is not open\n";
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "SQLite error: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "SQLite error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_finalize(stmt);
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

    if (!db) {
        std::cout << "SQLite error: database connection is not open\n";
        return notes;
    }

    // проверка на подготовленность запроса
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "SQLite error: " << sqlite3_errmsg(db) << "\n";
        return notes;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Note note;

        note.id = sqlite3_column_int(stmt, 0);

        const unsigned char* titleText = sqlite3_column_text(stmt, 1);
        note.title = titleText ? reinterpret_cast<const char*>(titleText) : "";

        const unsigned char* contentText = sqlite3_column_text(stmt, 2);
        note.content = contentText ? reinterpret_cast<const char*>(contentText) : "";

        const unsigned char* createdAtText = sqlite3_column_text(stmt, 3);
        note.created_at = createdAtText ? reinterpret_cast<const char*>(createdAtText) : "";

        notes.push_back(std::move(note));
    }
    sqlite3_finalize(stmt);
    return notes;
}