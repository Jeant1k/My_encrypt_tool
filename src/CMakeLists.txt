set(SOURCES
    main.cpp
    dictionary.cpp
    transformer.cpp
)

add_library(encrypt_tool_lib ${SOURCES})

add_executable(my_encrypt_tool main.cpp)
target_link_libraries(my_encrypt_tool encrypt_tool_lib)
