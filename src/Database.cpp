#include "Database.h"
#include <iostream>

// конструктор
Database::Database(const std::string &fileName) {
    db = nullptr;
    int result = sqlite3_open_v2(fileName.c_str(), &db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
        nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Database error opening '" << fileName << "': "
                  << sqlite3_errmsg(db) << "\n";
        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }
}
// деструктор
Database::~Database() {
    if (db) sqlite3_close(db);
}
// метод getConnection
sqlite3* Database::getConnection() {
    return db;
}

bool Database::isOpen() const {
    return db != nullptr;
}

