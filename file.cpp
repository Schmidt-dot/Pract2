#include "file.h"

#include <fstream>
#include <iostream>

using namespace std;

vector<uint8_t> readFile(const string& filename) {

    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return {};
    }

    vector<uint8_t> data;

    char byte;

    while (file.get(byte)) {
        data.push_back(static_cast<uint8_t>(byte));
    }

    file.close();

    return data;
}

void writeFile(const string& filename, const vector<uint8_t>& data) {

    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }

    for (uint8_t byte : data) {
        file.put(static_cast<char>(byte));
    }

    file.close();
}