#include "hughes.h"

#include "file.h"
#include "modInverse.h"
#include "binModPow.h"

#include <iostream>
#include <fstream>

using namespace std;


//ШИФРОВАНИЕ
void encrypt(const string& inputFile, const string& outputFile, int64_t n, int64_t g, int64_t x, int64_t y) {

    vector<uint8_t> data = readFile(inputFile);

    if (data.empty()) {
        return;
    }
    
    cout << "\nШИФРОВАНИЕ\n";

    cout << "n = " << n << endl;
    cout << "g = " << g << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    cout << "\nШаг 1" << endl;

    int64_t k = binModPow(g, x, n);

    cout << "k = g^x mod n = " << k << endl;

    cout << "\nШаг 2" << endl;

    int64_t Y = binModPow(g, y, n);

    cout << "Y = g^y mod n = " << Y << endl;

    cout << "\nШаг 3" << endl;

    int64_t X = binModPow(Y, x, n);

    cout << "X = Y^x mod n = " << X << endl;

    cout << "\nШаг 4" << endl;

    int64_t z = modInverse(y, n - 1);

    if (z == -1) {
        cerr << "Ошибка: невозможно вычислить z" << endl;
        return;
    }

    int64_t k2 = binModPow(X, z, n);

    cout << "k' = X^z mod n = " << k2 << endl;

    if (k != k2) {
        cerr << "Ошибка: k != k'" << endl;
        return;
    }

    cout << "\nk = k' = " << k << endl;

    int64_t d = modInverse(k, n - 1);

    if (d == -1) {
        cerr << "Ошибка: невозможно вычислить d" << endl;
        return;
    }

    cout << "d = " << d << endl;

    ofstream out(outputFile);

    if (!out.is_open()) {
        cerr << "Ошибка: не удалось создать файл " << outputFile << endl;
        return;
    }

    out << n << " " << d << endl;

    for (uint8_t byte : data) {

        uint64_t enc = binModPow(byte, k, n);

        out << enc << " ";
    }

    out.close();

    cout << "Файл зашифрован: " << outputFile << endl;
}


//ДЕШИФРОВАНИЕ
void decrypt(const string& inputFile, const string& outputFile) {

    ifstream in(inputFile);

    if (!in.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return;
    }

    cout << "\nДЕШИФРОВАНИЕ\n";

    int64_t n, d;

    in >> n >> d;

    cout << "n = " << n << endl;
    cout << "d = " << d << endl;

    vector<uint8_t> decrypted;

    int64_t enc;

    while (in >> enc) {

        uint64_t dec = binModPow(enc, d, n);

        decrypted.push_back(static_cast<uint8_t>(dec));
    }

    in.close();

    writeFile(outputFile, decrypted);

    cout << "Расшифрованный файл: "<< outputFile << endl;
}