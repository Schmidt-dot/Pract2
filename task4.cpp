#include "task4.h"

#include "hughes.h"
#include "binPowMod.h"
#include "modInverse.h"
#include "tFerma.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void task4() {

    uint64_t n, g, x, y;
    uint64_t mode;

    cout << "\nАЛГОРИТМ ХЬЮЗА " << endl;

    cout << "1 - Работа с текстом" << endl;
    cout << "2 - Работа с файлом" << endl;
    cout << "Выберите режим: ";
    cin >> mode;

    cout << "\nВведите простое число n (>255): ";
    cin >> n;

    if (!isPrime(n)) {
        cout << "Ошибка: n не является простым" << endl;
        return;
    }

    if (n <= 255) {
        cout << "Ошибка: n должно быть больше 255" << endl;
        return;
    }

    cout << "Введите примитивный элемент g: ";
    cin >> g;

    if (g >= n) {
        cout << "Ошибка: g должно быть меньше n" << endl;
        return;
    }

    cout << "Введите секретный ключ Алисы x: ";
    cin >> x;

    cout << "Введите секретный ключ Боба y: ";
    cin >> y;

    if (gcd(y, n - 1) != 1) {
        cout << "Ошибка: gcd(y, n - 1) != 1" << endl;
        return;
    }

    if (mode == 1) {

        cin.ignore();

        string text;

        cout << "Введите текст: ";
        getline(cin, text);

        vector<uint8_t> data(text.begin(), text.end());

        int64_t k = binPowMod(g, x, n);

        int64_t Y = binPowMod(g, y, n);

        int64_t z = modInverse(y, n - 1);

        if (z == -1) {
            cout << "Ошибка: невозможно вычислить z" << endl;
            return;
        }

        int64_t X = binPowMod(Y, x, n);

        int64_t k2 = binPowMod(X, z, n);

        if (k != k2) {
            cout << "Ошибка: k != k'." << endl;
            return;
        }

        int64_t d = modInverse(k, n - 1);

        if (d == -1) {
            cout << "Ошибка: невозможно вычислить d" << endl;
            return;
        }

        vector<uint64_t> encrypted;

        cout << "\nЗашифрованный текст:" << endl;

        for (uint8_t byte : data) {

            uint64_t enc = binPowMod(byte, k, n);

            encrypted.push_back(enc);

            cout << enc << " ";
        }

        cout << "\n\nРасшифрованный текст:" << endl;

        for (uint64_t enc : encrypted) {

            uint64_t dec = binPowMod(enc, d, n);

            cout << static_cast<char>(dec);
        }

        cout << endl;
    }

    else if (mode == 2) {

        string inputFile;
        string encryptedFile;
        string decryptedFile;

        cout << "Введите имя исходного файла: ";
        cin >> inputFile;

        cout << "Введите имя зашифрованного файла: ";
        cin >> encryptedFile;

        cout << "Введите имя расшифрованного файла: ";
        cin >> decryptedFile;

        encrypt(inputFile, encryptedFile, n, g, x, y);

        decrypt(encryptedFile, decryptedFile);
    }

    else {

        cout << "Ошибка: неверный режим" << endl;
    }
}