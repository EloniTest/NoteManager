#pragma once

#include <string>
#include "sqlite3.h"

class Database {
    private:
        sqlite3* db = nullptr;
    public:
        // конструктор
        Database(const std::string &fileName);
        // деструктор
        ~Database();

        sqlite3* getConnection();
        bool isOpen() const;
};