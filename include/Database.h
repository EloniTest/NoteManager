#pragma once

#include <string>
#include "sqlite3.h"

class dataBase {
    private:
        sqlite3* db;
    public:
        // конструктор
        dataBase(const std::string &fileName);
        // деструктор
        ~dataBase();

        sqlite3* getConnection();
};