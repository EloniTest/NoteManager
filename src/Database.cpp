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
    std::cout << "database class connected successfully";
    return db;
}