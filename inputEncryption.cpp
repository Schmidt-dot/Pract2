#include "inputEncryption.h"

#include "hughes.h"
#include "file.h"
#include "tFerma.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void inputEncryption() {

    uint64_t n, g, x, y;
    uint64_t mode;

    cout << "\nАЛГОРИТМ ХЬЮЗА" << endl;

    while (true) {
        cout << "1 - Работа с текстом" << endl;
        cout << "2 - Работа с файлом" << endl;
        cout << "Выберите режим: ";
        cin >> mode;

        if (mode == 1 || mode == 2) {
            break;
        }

        cout << "Ошибка: неверный режим. Попробуйте ещё раз.\n";
    }

    while (true) {
        cout << "\nВведите простое число n (>255): ";
        cin >> n;

        if (!isPrime(n)) {
            cout << "Ошибка: n не является простым. Попробуйте ещё раз.\n";
            continue;
        }

        if (n <= 255) {
            cout << "Ошибка: n должно быть больше 255. Попробуйте ещё раз.\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "Введите элемент g < n: ";
        cin >> g;

        if (g < n) {
            break;
        }

        cout << "Ошибка: g должно быть меньше n. Попробуйте ещё раз.\n";
    }

    cout << "Введите секретный ключ Алисы x: ";
    cin >> x;

    while (true) {
        cout << "Введите секретный ключ Боба y: ";
        cin >> y;

        if (gcd(y, n - 1) == 1) {
            break;
        }

        cout << "Ошибка: gcd(y, n - 1) должно быть равно 1. Попробуйте ещё раз.\n";
    }

    if (mode == 1) {

        cin.ignore();

        string text;

        cout << "Введите текст: ";
        getline(cin, text);

        vector<uint8_t> data(text.begin(), text.end());

        uint64_t d;

        vector<uint64_t> encrypted = encrypt(data, n, g, x, y, d);

        if (encrypted.empty()) {
            return;
        }

        cout << "\nЗашифрованный текст:" << endl;

        for (uint64_t value : encrypted) {
            cout << value << " ";
        }

        cout << "\n\nРасшифрованный текст:" << endl;

        vector<uint8_t> decrypted = decrypt(encrypted, n, d);

        for (uint8_t byte : decrypted) {
            cout << static_cast<char>(byte);
        }

        cout << endl;
    }
    else {

        string inputFile;

        cout << "Введите имя исходного файла: ";
        cin >> inputFile;

        vector<uint8_t> data = readFile(inputFile);

        if (data.empty()) {
            return;
        }

        uint64_t d;

        vector<uint64_t> encrypted = encrypt(data, n, g, x, y, d);

        if (encrypted.empty()) {
            return;
        }

        ofstream encryptedFile("encrypted.txt");

        if (!encryptedFile.is_open()) {
            cout << "Ошибка создания encrypted.txt" << endl;
            return;
        }

        encryptedFile << n << " " << d << endl;

        for (uint64_t value : encrypted) {
            encryptedFile << value << " ";
        }

        encryptedFile.close();

        ifstream encryptedInput("encrypted.txt");

        if (!encryptedInput.is_open()) {
            cout << "Ошибка открытия encrypted.txt" << endl;
            return;
        }

        uint64_t n2, d2;

        encryptedInput >> n2 >> d2;

        vector<uint64_t> encryptedData;

        uint64_t value;

        while (encryptedInput >> value) {
            encryptedData.push_back(value);
        }

        encryptedInput.close();

        vector<uint8_t> decrypted = decrypt(encryptedData, n2, d2);

        writeFile("decrypted.txt", decrypted);

        cout << "\nСоздан файл encrypted.txt" << endl;
        cout << "Создан файл decrypted.txt" << endl;
    }
}