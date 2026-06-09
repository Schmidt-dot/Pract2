#pragma once

#include <string>
#include <cstdint>

void encrypt(const std::string& inputFile, const std::string& outputFile, int64_t n, int64_t g, int64_t x, int64_t y);
void decrypt(const std::string& inputFile, const std::string& outputFile);

