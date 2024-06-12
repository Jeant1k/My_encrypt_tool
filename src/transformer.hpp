#pragma once

#include <string>
#include <unordered_map>

bool transformFile(const std::string& inputPath, const std::string& outputPath, const std::unordered_map<uint8_t, uint8_t>& dictionary);
