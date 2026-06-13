#include "Database.h"
#include <iostream>

// конструктор
dataBase::dataBase(const std::string &fileName) {
    if (sqlite3_open(fileName.c_str(), &db) !=SQLITE_OK) {
        std::cerr << "Database error\n";
    }
}
// деструктор
dataBase::~dataBase() {
    sqlite3_close(db);
}
// метод getConnection
sqlite3* dataBase::getConnection() {
    std::cout << "database class connected successfully\n";
    return db;
}

void dataBase::createTables()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS notes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "content TEXT NOT NULL,"
        "created_at TEXT NOT NULL"
        ");";

    char* errMsg = nullptr;

    if(sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cout << errMsg << '\n';
        sqlite3_free(errMsg);
    }
}