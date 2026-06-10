#include "hughes.h"

#include "modInverse.h"
#include "binModPow.h"

#include<iostream>

using namespace std;


//ШИФРОВАНИЕ
vector<uint64_t> encrypt(const vector<uint8_t>& data, uint64_t n, uint64_t g, uint64_t x, uint64_t y, uint64_t& d) {

    vector<uint64_t> encrypted;

    cout << "\nШИФРОВАНИЕ\n";

    cout << "n = " << n << endl;
    cout << "g = " << g << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    cout << "\nШаг 1" << endl;

    uint64_t k = binModPow(g, x, n);

    cout << "k = g^x mod n = " << k << endl;

    cout << "\nШаг 2" << endl;

    uint64_t Y = binModPow(g, y, n);

    cout << "Y = g^y mod n = " << Y << endl;

    cout << "\nШаг 3" << endl;

    uint64_t X = binModPow(Y, x, n);

    cout << "X = Y^x mod n = " << X << endl;

    cout << "\nШаг 4" << endl;

    int64_t z = modInverse(y, n - 1);

    if (z == -1) {
        cerr << "Ошибка: невозможно вычислить z" << endl;
        return {};
    }

    uint64_t k2 = binModPow(X, z, n);

    cout << "k' = X^z mod n = " << k2 << endl;

    if (k != k2) {
        cerr << "Ошибка: k != k'" << endl;
        return {};
    }

    cout << "\nk = k' = " << k << endl;

    d = modInverse(k, n - 1);

    if (d == static_cast<uint64_t>(-1)) {
        cerr << "Ошибка: невозможно вычислить d" << endl;
        return {};
    }

    cout << "d = " << d << endl;

    for (uint8_t byte : data) {

        uint64_t enc = binModPow(byte, k, n);

        encrypted.push_back(enc);
    }
    return encrypted;
}


// ДЕШИФРОВАНИЕ
vector<uint8_t> decrypt(const vector<uint64_t>& encrypted, uint64_t n, uint64_t d) {

    cout << "\nДЕШИФРОВАНИЕ\n";

    cout << "n = " << n << endl;
    cout << "d = " << d << endl;

    vector<uint8_t> decrypted;

    for (uint64_t enc : encrypted) {

        uint64_t dec = binModPow(enc, d, n);
        decrypted.push_back(static_cast<uint8_t>(dec));
    }
    return decrypted;
}