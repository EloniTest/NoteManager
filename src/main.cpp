#include "Database.h"
#include "Notes.h"
#include "tests.cpp"

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

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Меню заметок\n";
    std::cout << "1. Добавить заметку\n";
    std::cout << "2. Показать все заметки\n";
    std::cout << "3. Удалить заметку\n";
    std::cout << "4. Обновить заметку\n";

    

    return 0;
}