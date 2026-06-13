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
        // если путь к exe получить не удалось, используем относительный путь.
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

    // путь к файлу базы данных
    auto dbFilePath = getDatabasePath();
    std::cout << "Using database file: " << dbFilePath.string() << "\n";

    // открытие базы данных
    Database db(dbFilePath.string());
    if (!db.isOpen()) {
        std::cerr << "Failed to open database. Check the path and permissions\n";
        return 1;
    }
    std::cout << "Connected to database.\n";

    // тесты
    Notes note(db.getConnection());

    std::cout << "\n... Добавление заметки ...\n";
    note.addNote("Изучить SQLite", "Разобраться в его ебучем непонятном синтаксисе");

    std::cout << "\n... Все заметки после добавления ...\n";
    auto allNotes = note.getAllNote();
    
    for (const auto& item : allNotes) {
        std::cout
            << item.id << "\n"
            << item.title << "\n"
            << item.content << "\n"
            << item.created_at << "\n\n";
    }

    if (!allNotes.empty()) {
        int firstId = allNotes[0].id;
        int secondId = allNotes[1].id;

        std::cout << "\n... Обновление заметки с id= " << firstId << " ...\n";
        note.updateNote(firstId, "Изучить SQLite (обновлено)", "Теперь я понимаю, как это работает");

        std::cout << "\n... Все заметки после обновления ...\n";
        allNotes = note.getAllNote();

        for (const auto& item : allNotes) {
            std::cout
                << item.id << "\n"
                << item.title << "\n"
                << item.content << "\n"
                << item.created_at << "\n\n";
        }

        std::cout << "\n... Удаление всех заметок ...\n";
        note.removeNote(firstId);
        note.removeNote(secondId);

        std::cout << "\n... Все заметки после удаления ...\n";
        allNotes = note.getAllNote();

        for (const auto& item : allNotes) {
            std::cout
                << item.id << "\n"
                << item.title << "\n"
                << item.content << "\n"
                << item.created_at << "\n\n";
        }
    } else {
        std::cout << "Заметок нет, тест обновления и удаления пропущен.\n";
    }

    return 0;
}