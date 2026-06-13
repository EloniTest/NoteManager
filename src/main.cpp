#include "Database.h"
#include "Notes.h"

#include <filesystem>
#include <iostream>
#include <windows.h>

// Возвращает путь к файлу notes.db.
// Если программа запущена из build/Debug, то путь будет поднят на два уровня вверх.
static std::filesystem::path getDatabasePath() {
    char exePath[MAX_PATH] = {0};
    DWORD length = GetModuleFileNameA(NULL, exePath, MAX_PATH);
    if (length == 0 || length == MAX_PATH) {
        // Если путь к exe получить не удалось, используем относительный путь.
        return std::filesystem::path("data") / "notes.db";
    }

    std::filesystem::path exeDir = std::filesystem::path(exePath).parent_path();
    auto dbPath = exeDir / ".." / ".." / "data" / "notes.db";
    dbPath = dbPath.lexically_normal();
    return dbPath;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Путь к файлу базы данных
    auto dbFilePath = getDatabasePath();
    std::cout << "Using database file: " << dbFilePath.string() << "\n";

    // Открываем базу данных
    Database db(dbFilePath.string());
    if (!db.isOpen()) {
        std::cerr << "Не удалось открыть базу данных. Проверьте путь и права доступа.\n";
        return 1;
    }
    std::cout << "Connected to database.\n";

    // добавление заметки
    Notes note(db.getConnection());

    note.addNote("Изучить SQLite", "Разобраться в его ебучем непонятном синтаксисе");
    auto allNotes = note.getAllNote();

    for(const auto& note : allNotes) {
        std::cout 
        << note.id << "\n"
        << note.title << "\n"
        << note.content << "\n"
        << note.created_at << "\n\n";
    }

    return 0;
}