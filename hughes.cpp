#include "hughes.h"

#include "binModPow.h"
#include "modInverse.h"

#include<iostream>

using namespace std;

vector<uint64_t> encrypt(const vector<uint8_t>& data, uint64_t n, uint64_t g, uint64_t x, uint64_t y, uint64_t& d) {

    vector<uint64_t> encrypted;

    uint64_t k = binModPow(g, x, n);

    uint64_t Y = binModPow(g, y, n);

    int64_t z = modInverse(y, n - 1);

    if (z == -1) {
        cout << "Ошибка: невозможно вычислить z" << endl;
        return {};
    }

    uint64_t X = binModPow(Y, x, n);

    uint64_t k2 = binModPow(X, static_cast<uint64_t>(z), n);

    if (k != k2) {
        cout << "Ошибка: k != k'" << endl;
        return {};
    }

    int64_t dTemp = modInverse(k, n - 1);

    if (dTemp == -1) {
        cout << "Ошибка: невозможно вычислить d" << endl;
        return {};
    }

    d = static_cast<uint64_t>(dTemp);

    for (uint8_t byte : data) {
        encrypted.push_back(binModPow(byte, k, n));
    }
    return encrypted;
}

vector<uint8_t> decrypt(const vector<uint64_t>& encrypted, uint64_t n, uint64_t d) {

    vector<uint8_t> decrypted;

    for (uint64_t value : encrypted) {

        uint64_t byte = binModPow(value, d, n);

        decrypted.push_back(static_cast<uint8_t>(byte));
    }
    return decrypted;
}