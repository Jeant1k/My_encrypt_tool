#pragma once

#include <string>
#include <unordered_map>

bool loadDictionary(const std::string& path, std::unordered_map<uint8_t, uint8_t>& dictionary, bool reverse);

