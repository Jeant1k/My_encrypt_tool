#include <gtest/gtest.h>
#include "../src/transformer.hpp"
#include "../src/dictionary.hpp"
#include <fstream>
#include <unordered_map>

class TransformerTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream input("test_input.txt");
        input << "\x41\x42\x43";
        input.close();

        std::ofstream dict("test_dictionary.txt");
        dict << "0x41 -> 0x42\n";
        dict << "0x42 -> 0x43\n";
        dict << "0x43 -> 0x41\n";
        dict.close();
    }

    void TearDown() override {
        remove("test_input.txt");
        remove("test_output.txt");
        remove("test_dictionary.txt");
    }
};

// Тесты для проверки преобразования файла

TEST_F(TransformerTest, DirectTransform) {
    std::unordered_map<uint8_t, uint8_t> dictionary;
    loadDictionary("test_dictionary.txt", dictionary, false);

    ASSERT_TRUE(transformFile("test_input.txt", "test_output.txt", dictionary));

    std::ifstream output("test_output.txt", std::ios::binary);
    std::string result((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());
    output.close();

    EXPECT_EQ(result, "\x42\x43\x41");
}

TEST_F(TransformerTest, ReverseTransform) {
    std::unordered_map<uint8_t, uint8_t> dictionary;
    loadDictionary("test_dictionary.txt", dictionary, true);

    ASSERT_TRUE(transformFile("test_input.txt", "test_output.txt", dictionary));

    std::ifstream output("test_output.txt", std::ios::binary);
    std::string result((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());
    output.close();

    EXPECT_EQ(result, "\x43\x41\x42");
}
