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

void clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Database database(getDatabasePath().string());
    if (!database.isOpen()) {
        std::cerr << "Failed to open database. Exiting.\n";
        return 1;
    }


    int choice;
    int id;
    std::string title, content;
    Notes notes(database.getConnection());


    do {
        clearScreen();
        std::cout << "Меню заметок\n";
        std::cout << "1. Добавить заметку\n";
        std::cout << "2. Показать все заметки\n";
        std::cout << "3. Удалить заметку\n";
        std::cout << "4. Обновить заметку\n";
        std::cout << "0. Выйти\n";
        std::cout << "Выберите действие (1-4): ";
        std::cin >> choice;
        std::cin.ignore();

    switch(choice) {
        case 1:
                std::cout << "Введите заголовок заметки: ";
                std::getline(std::cin, title);
                std::cout << "Введите содержание заметки: ";
                std::getline(std::cin, content);
                notes.addNote(title,content);
                std::cout << "Заметка добавлена.\n";
                std::cin.get();
            break;
        case 2:
            {
                auto allNotes = notes.getAllNote();
                if(allNotes.empty()) {
                    std::cout << "Нет заметок\n";
                } else {
                    std::cout << "Список всех заметок:\n";
                    for (const auto& note : allNotes) {
                        std::cout << "ID: " << note.id << "\n";
                        std::cout << "Заголовок: " << note.title << "\n";
                        std::cout << "Содержание: " << note.content << "\n";
                        std::cout << "Дата создания: " << note.created_at << "\n";
                        std::cout << "-------------------------\n";
                    }
                }
                std::cin.get();
                clearScreen();
            }
            break;
        case 3:
                std::cout << "Введите ID заметки для удаления: ";
                std::cin >> id;
                notes.removeNote(id);
                std::cout << "Заметка с id: " << id << " удалена.\n";
                std::cin.get();
                clearScreen();
            break;
        case 4:
                std::cout << "Введите ID заметки для обновления: ";
                std::cin >> id;
                std::cin.ignore();

                std::cout << "Введите новый заголовок заметки: ";
                std::getline(std::cin, title);

                std::cout << "Введите новое содержание заметки: ";
                std::getline(std::cin, content);

                notes.updateNote(id, title, content);
                std::cout << "Заметка с id: " << id << " обновлена.\n";
                std::cin.get();
                clearScreen();
            break;
    }
    } while(choice != 0);
    
    return 0;
}