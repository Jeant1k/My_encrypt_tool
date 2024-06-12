#include "transformer.hpp"
#include <fstream>
#include <iostream>

// Функция для трансформации файла

bool transformFile(const std::string& inputPath, const std::string& outputPath, const std::unordered_map<uint8_t, uint8_t>& dictionary) {
    std::ifstream inputFile(inputPath, std::ios::binary); // Открытие входного файла в бинарном режиме
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open dictionary file: " + inputPath);
    }

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open dictionary file: " + outputPath);
    }

    char byte;
    while (inputFile.get(byte)) {
        uint8_t inputByte = static_cast<uint8_t>(byte);
        if (dictionary.contains(inputByte)) {
            outputFile.put(static_cast<char>(dictionary.at(inputByte))); // Замена байта по словарю
        } else {
            outputFile.put(byte); // Если байта нет в словаре, он остается без изменений
        }
    }

    if (inputFile.bad()) {
        throw std::runtime_error("Error reading input file: " + inputPath);
    }
    if (outputFile.bad()) {
        throw std::runtime_error("Error writing output file: " + outputPath);
    }

    return true;
}
