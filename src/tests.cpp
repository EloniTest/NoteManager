#include "Database.h"
#include "Notes.h"

#include <filesystem>
#include <iostream>
#include <windows.h>

// возвращает путь к файлу notes.db
// если программа запущена из build/Debug, то путь будет поднят на два уровня вверх
static std::filesystem::path getDatabasePath() {
    char exePath[MAX_PATH] = {0};
    DWORD length = GetModuleFileNameA(NULL, exePath, MAX_PATH);
    if (length == 0 || length == MAX_PATH) {
        return std::filesystem::path("data") / "notes.db";
    }

    std::filesystem::path exeDir = std::filesystem::path(exePath).parent_path();
    auto dbPath = exeDir / ".." / ".." / "data" / "notes.db";
    return dbPath.lexically_normal();
}

class DatabaseTester {
public:
    explicit DatabaseTester(const std::filesystem::path& dbPath)
        : database_(dbPath.string()), notes_(database_.getConnection()) {}

    int run() {
        if (!database_.isOpen()) {
            std::cerr << "Failed to open database. Check the path and permissions\n";
            return 1;
        }

        printPath();
        addNote();
        showNotes("All notes after adding");

        auto allNotes = notes_.getAllNote();
        if (allNotes.empty()) {
            std::cout << "No notes found. Test stopped.\n";
            return 0;
        }

        int firstId = allNotes[0].id;
        updateNote(firstId);
        showNotes("All notes after update");

        deleteNote(firstId);
        showNotes("All notes after delete");

        std::cout << "\nTests finished.\n";
        return 0;
    }

private:
    void printPath() const {
        std::cout << "Using database file: " << databasePath_.string() << "\n";
    }

    void addNote() {
        std::cout << "\n=== Adding a note ===\n";
        notes_.addNote("Изучить SQLite", "Разобраться в его ебучем непонятном синтаксисе");
    }

    void updateNote(int id) {
        std::cout << "\n=== Updating note id=" << id << " ===\n";
        notes_.updateNote(id, "Изучить SQLite (обновлено)", "Теперь я понимаю, как это работает");
    }

    void deleteNote(int id) {
        std::cout << "\n=== Deleting note id=" << id << " ===\n";
        notes_.removeNote(id);
    }

    void showNotes(const char* title) {
        std::cout << "\n=== " << title << " ===\n";
        auto allNotes = notes_.getAllNote();
        std::cout << "Found " << allNotes.size() << " notes.\n\n";
        for (const auto& item : allNotes) {
            std::cout
                << "ID: " << item.id << "\n"
                << "Title: " << item.title << "\n"
                << "Content: " << item.content << "\n"
                << "Created at: " << item.created_at << "\n\n";
        }
    }

    Database database_;
    Notes notes_;
    std::filesystem::path databasePath_ = getDatabasePath();
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    DatabaseTester tester(getDatabasePath());
    return tester.run();
}
