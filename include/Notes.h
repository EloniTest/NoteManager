#pragma once

#include "sqlite3.h"
#include <vector>
#include <string>

struct Note {
    int id;
    std::string title;
    std::string content;
    std::string created_at;
};

class Notes {
    private:
        
    public:
        void addNote(const std::string &title, const std::string &content);
        void removeNote(int id);
        void updateNote(int id, const std::string &title, const std::string &content);
        std::vector<Note> getAllNote();
};
