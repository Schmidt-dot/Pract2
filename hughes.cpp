#include "hughes.h"

#include "tFerma.h"
#include "modInverse.h"

#include<iostream>

using namespace std;

vector<uint64_t> encrypt(const vector<uint8_t>& data, uint64_t n, uint64_t g, uint64_t x, uint64_t y, uint64_t& d) {

    vector<uint64_t> encrypted;

    uint64_t k = binPowMod(g, x, n, false); //ключ шифрования сообщения

    uint64_t Y = binPowMod(g, y, n, false); //открытый ключ B-A

    int64_t z = modInverse(y, n - 1, false); //обрытный ключ B

    if (z == -1) {
        cout << "Ошибка: невозможно вычислить z" << endl;
        return {};
    }

    uint64_t X = binPowMod(Y, x, n, false); //открытый ключ A-B

    uint64_t k2 = binPowMod(X, static_cast<uint64_t>(z), n, false); //восстановленный ключ шифрования

    if (k != k2) {
        cout << "Ошибка: k != k'" << endl;
        return {};
    }

    int64_t dTemp = modInverse(k, n - 1, false); //ключ дешифрования

    if (dTemp == -1) {
        cout << "Ошибка: невозможно вычислить d" << endl;
        return {};
    }

    d = static_cast<uint64_t>(dTemp);

    for (uint8_t byte : data) {
        encrypted.push_back(binPowMod(byte, k, n, false));
    }
    return encrypted;
}

vector<uint8_t> decrypt(const vector<uint64_t>& encrypted, uint64_t n, uint64_t d) {

    vector<uint8_t> decrypted;

    for (uint64_t value : encrypted) {

        uint64_t byte = binPowMod(value, d, n, false);

        decrypted.push_back(static_cast<uint8_t>(byte));
    }
    return decrypted;
}