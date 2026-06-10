#include "file.h"

#include<fstream>
#include<iostream>

using namespace std;


//ЧТЕНИЕ ФАЙЛА
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


//ЗАПИСЬ ФАЙЛА
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


//ЗАПИСЬ ЗАШИФРОВАННОГО ФАЙЛА
void writeEncryptedFile(const string& filename, const vector<uint64_t>& data, uint64_t n, uint64_t d) {

    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }

    file << n << " " << d << endl;

    for (uint64_t value : data) {
        file << value << " ";
    }
    file.close();
}


//ЧТЕНИЕ ФАЙЛА
vector<uint64_t> readEncryptedFile(const string& filename, uint64_t& n, uint64_t& d) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return {};
    }

    file >> n >> d;

    vector<uint64_t> data;

    uint64_t value;

    while (file >> value) {
        data.push_back(value);
    }

    file.close();

    return data;
}