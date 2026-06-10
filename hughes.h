#pragma once

#include<vector>
#include<cstdint>

using namespace std;


vector<uint64_t> encrypt(const vector<uint8_t>& data, uint64_t n, uint64_t g, uint64_t x, uint64_t y, uint64_t& d);
vector<uint8_t> decrypt(const vector<uint64_t>& encrypted, uint64_t n, uint64_t d);
