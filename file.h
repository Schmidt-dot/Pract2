#pragma once

#include <vector>
#include <string>
#include <cstdint>


std::vector<uint8_t> readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::vector<uint8_t>& data);

