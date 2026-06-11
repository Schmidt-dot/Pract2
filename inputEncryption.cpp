#include "inputEncryption.h"

#include "hughes.h"
#include "file.h"
#include "tFerma.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

void inputEncryption() {

    uint64_t n, g, x, y;
    uint64_t mode;

    cout << "\nАЛГОРИТМ ХЬЮЗА" << endl;

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

        vector<uint8_t> decrypted =
            decrypt(encrypted, n, d);

        for (uint8_t byte : decrypted) {
            cout << static_cast<char>(byte);
        }
        cout << endl;
    }

    else if (mode == 2) {

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
    else {
        cout << "Ошибка: неверный режим" << endl;
    }
}