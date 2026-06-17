#include "Database.h"
#include "Notes.h"
#include "tests.cpp"

#include <filesystem>
#include <iostream>
#include <windows.h>

// возвращает путь к файлу notes.db
// если программа запущена из build/Debug, то путь будет поднят на два уровня вверх


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    databaseTester tester(getDatabasePath());
    tester.run();

    std::cout << "Меню заметок\n";
    std::cout << "1. Добавить заметку\n";
    std::cout << "2. Показать все заметки\n";
    std::cout << "3. Удалить заметку\n";
    std::cout << "4. Обновить заметку\n";

    

    return 0;
}