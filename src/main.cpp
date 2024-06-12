#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "dictionary.hpp"
#include "transformer.hpp"
#include "../include/constants.hpp"

int main(int argc, char* argv[]) {
    try {
        std::string mode;
        std::string dictionaryPath;
        std::string inputFilePath;
        std::string outputFilePath;

        // Обработка аргументов командной строки
        std::unordered_set<std::string> processedArgs; // Множество для хранения уже обработанных аргументов
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg.contains(MODE_ARG)) {
                if (processedArgs.contains(MODE_ARG)) { // Проверка на дублирующиеся аргументы
                    throw std::invalid_argument("Duplicate argument: " + MODE_ARG);
                }
                mode = arg.substr(MODE_ARG.length()); // Извлечение значения аргумента
                if (mode != DIRECT_MODE && mode != REVERSE_MODE) {
                    throw std::invalid_argument("Invalid mode argument: " + mode);
                }
                processedArgs.insert(MODE_ARG); // Добавление аргумента в множество обработанных
            } else if (arg.contains(DICTIONARY_ARG)) {
                if (processedArgs.contains(DICTIONARY_ARG)) {
                    throw std::invalid_argument("Duplicate argument: " + DICTIONARY_ARG);
                }
                dictionaryPath = arg.substr(DICTIONARY_ARG.length());
                processedArgs.insert(DICTIONARY_ARG);
            } else if (arg.contains(INPUT_FILE_ARG)) {
                if (processedArgs.contains(INPUT_FILE_ARG)) {
                    throw std::invalid_argument("Duplicate argument: " + INPUT_FILE_ARG);
                }
                inputFilePath = arg.substr(INPUT_FILE_ARG.length());
                processedArgs.insert(INPUT_FILE_ARG);
            } else if (arg.contains(OUTPUT_FILE_ARG)) {
                if (processedArgs.contains(OUTPUT_FILE_ARG)) {
                    throw std::invalid_argument("Duplicate argument: " + OUTPUT_FILE_ARG);
                }
                outputFilePath = arg.substr(OUTPUT_FILE_ARG.length());
                processedArgs.insert(OUTPUT_FILE_ARG);
            } else {
                throw std::invalid_argument("Unknown argument: " + arg); // Обработка неизвестных аргументов
            }
        }

        // Проверка на наличие всех необходимых аргументов
        if (mode.empty() || dictionaryPath.empty() || inputFilePath.empty() || outputFilePath.empty()) {
            throw std::invalid_argument("Missing arguments. Usage: my_encrypt_tool --mode=<direct|reverse> --dictionary=/path/to/dictionary --input_file=/path/to/input_file --output_file=/path/to/output_file");
        }

        // Загрузка словаря
        std::unordered_map<uint8_t, uint8_t> dictionary;
        if (!loadDictionary(dictionaryPath, dictionary, mode == REVERSE_MODE)) {
            throw std::runtime_error("Failed to load dictionary");
        }

        // Трансформация файла
        if (!transformFile(inputFilePath, outputFilePath, dictionary)) {
            throw std::runtime_error("Failed to transform file");
        }

        std::cout << "Transformation completed successfully\n";

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
