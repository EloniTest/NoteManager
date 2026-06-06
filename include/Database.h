#pragma once

#include <string>
#include "sqlite3.h"

class dataBase {
    private:
        sqlite3* db;
    public:
        dataBase(const std::string &fileName);
        ~dataBase();

        sqlite3* getConnection();
};