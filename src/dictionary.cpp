#include "dictionary.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <regex>

// Функция для загрузки словаря из файла

bool loadDictionary(const std::string& path, std::unordered_map<uint8_t, uint8_t>& dictionary, bool reverse) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open dictionary file: " + path);
    }

    std::string line;
    std::regex pattern(R"(\s*(0x[0-9A-Fa-f]{2})\s*->\s*(0x[0-9A-Fa-f]{2})\s*)"); // Регулярное выражение для проверки формата строк

    while (std::getline(file, line)) {
        std::smatch match;
        if (!std::regex_match(line, match, pattern)) { // Проверка на соответствие строки формату
            throw std::invalid_argument("Invalid dictionary entry format: " + line);
        }

        std::string fromStr = match[1];
        std::string toStr = match[2];

        uint8_t from = static_cast<uint8_t>(std::stoi(fromStr, nullptr, 16)); // Преобразование строки в число
        uint8_t to = static_cast<uint8_t>(std::stoi(toStr, nullptr, 16));

        if (reverse) {
            if (dictionary.contains(to)) { // Проверка на дублирование ключей
                throw std::invalid_argument("Duplicate key found in dictionary: " + toStr);
            }
            dictionary[to] = from; // Добавление пары в словарь для обратного режима
        } else {
            if (dictionary.contains(from)) {
                throw std::invalid_argument("Duplicate key found in dictionary: " + fromStr);
            }
            dictionary[from] = to; // Добавление пары в словарь для прямого режима
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error reading input file: " + path);
    }

    return true;
}
