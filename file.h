#pragma once

#include<vector>
#include<string>
#include<cstdint>

using namespace std;


vector<uint8_t> readFile(const string& filename);

void writeFile(const string& filename, const vector<uint8_t>& data);

void writeEncryptedFile(const string& filename, const vector<uint64_t>& data, uint64_t n, uint64_t d);

vector<uint64_t> readEncryptedFile(const string& filename, uint64_t& n, uint64_t& d);

