# Подключение GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
    test_main.cpp
    test_dictionary.cpp
    test_transformer.cpp
)

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests gtest gtest_main encrypt_tool_lib)

include(GoogleTest)
gtest_discover_tests(run_tests)

