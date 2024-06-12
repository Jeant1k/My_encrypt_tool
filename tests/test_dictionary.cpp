#include <gtest/gtest.h>
#include <fstream>
#include "../src/dictionary.hpp"

// Тесты для проверки загрузки словаря

TEST(DictionaryTest, InvalidFormat1) {
    std::ofstream dictFile("invalid_format.txt");
    dictFile << "0xAA -> BB\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_THROW(loadDictionary("invalid_format.txt", dictionary, false), std::invalid_argument);

    std::remove("invalid_format.txt");
}

TEST(DictionaryTest, InvalidFormat2) {
    std::ofstream dictFile("invalid_format.txt");
    dictFile << "0xAA - 0xBB\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_THROW(loadDictionary("invalid_format.txt", dictionary, false), std::invalid_argument);

    std::remove("invalid_format.txt");
}

TEST(DictionaryTest, InvalidFormat3) {
    std::ofstream dictFile("invalid_format.txt");
    dictFile << "0xFG -> 0xZZ\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_THROW(loadDictionary("invalid_format.txt", dictionary, false), std::invalid_argument);

    std::remove("invalid_format.txt");
}

TEST(DictionaryTest, InvalidFormat4) {
    std::ofstream dictFile("invalid_format.txt");
    dictFile << "0x -> 0xBB\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_THROW(loadDictionary("invalid_format.txt", dictionary, false), std::invalid_argument);

    std::remove("invalid_format.txt");
}

TEST(DictionaryTest, DuplicateKeys1) {
    std::ofstream dictFile("duplicate_keys.txt");
    dictFile << "0xAA -> 0xBB\n0xAA -> 0xCC\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_THROW(loadDictionary("duplicate_keys.txt", dictionary, false), std::invalid_argument);

    std::remove("duplicate_keys.txt");
}

TEST(DictionaryTest, DuplicateKeys2) {
    std::ofstream dictFile("duplicate_keys.txt");
    dictFile << "0xAA -> 0xBB\n0xCC -> 0xBB\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_THROW(loadDictionary("duplicate_keys.txt", dictionary, true), std::invalid_argument);

    std::remove("duplicate_keys.txt");
}

TEST(DictionaryTest, ValidDictionary1) {
    std::ofstream dictFile("valid_dict.txt");
    dictFile << "0xAA -> 0xBB\n0xBB -> 0xCC\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_NO_THROW(loadDictionary("valid_dict.txt", dictionary, false));
    EXPECT_EQ(dictionary[0xAA], 0xBB);
    EXPECT_EQ(dictionary[0xBB], 0xCC);

    std::remove("valid_dict.txt");
}

TEST(DictionaryTest, ValidDictionary2) {
    std::ofstream dictFile("valid_dict.txt");
    dictFile << "\t0xAA \t ->  0xBB\n\t0xBB -> 0xCC\n";
    dictFile.close();

    std::unordered_map<uint8_t, uint8_t> dictionary;
    EXPECT_NO_THROW(loadDictionary("valid_dict.txt", dictionary, false));
    EXPECT_EQ(dictionary[0xAA], 0xBB);
    EXPECT_EQ(dictionary[0xBB], 0xCC);

    std::remove("valid_dict.txt");
}

