#include<iostream>
#include<cstdint>
#include<string>
#include<vector>

#include "tFerma.h"
#include "modInverse.h"

using namespace std;

int main() {

    //Общие параметры
    uint64_t n = 257;
    uint64_t g = 7;

    //Секреты участников
    uint64_t xA = 11; //Алиса
    uint64_t yB = 3; //Боб
    uint64_t yE = 13; //Ева

    cout << "\nАТАКА ПОСРЕДИНЕ НА ПРИМЕРЕ АЛГОРИТМА ХЬЮЗА\n";

    //Боб
    uint64_t YB = binPowMod(g, yB, n, false);
    cout << "\nB вычисляет:" << endl;
    cout << "YB = " << YB << endl;

    //Ева
    uint64_t YE = binPowMod(g, yE, n, false);
    cout << "\nE перехватывает сообщение." << endl;
    cout << "E отправляет A своё значение:" << endl;
    cout << "YE = " << YE << endl;

    //Алиса
    uint64_t XA = binPowMod(YE, xA, n, false);
    cout << "\nA вычисляет:" << endl;
    cout << "XA = " << XA << endl;

    //Ключ A-E
    uint64_t zE = modInverse(yE, n - 1, false);
    uint64_t kAE = binPowMod(XA, zE, n, false);
    cout << "\nКлюч A-E: " << kAE << endl;

    //Ключ E-B
    uint64_t XE = binPowMod(YB, yE, n, false);
    uint64_t zB = modInverse(yB, n - 1, false);
    uint64_t kBE = binPowMod(XE, zB, n, false);
    cout << "Ключ E-B: " << kBE << endl;

    //Алиса отправляет
    string message = "HELLO";
    cout << "\nA отправляет сообщение: " << message << endl;

    vector<uint64_t> encryptedByAlice;

    //Алиса шифрует сообщение
    for (char ch : message) {
        uint64_t cipher = binPowMod(static_cast<uint8_t>(ch), kAE, n, false);
        encryptedByAlice.push_back(cipher);
    }

    //Ева перехватывает
    uint64_t dAE = modInverse(kAE, n - 1, false);
    string interceptedMessage;

    cout << "\nE расшифровывает сообщение:" << endl;

    for (uint64_t cipher : encryptedByAlice) {
        uint64_t decrypted = binPowMod(cipher, dAE, n, false);

        interceptedMessage += static_cast<char>(decrypted);
    }

    cout << interceptedMessage << endl;

    //Ева изменяет
    string modifiedMessage = "HI!";
    cout << "\nE изменяет сообщение на: " << modifiedMessage << endl;

    vector<uint64_t> encryptedForBob;

    //Ева шифрует сообщение для Боба
    for (char ch : modifiedMessage) {
        uint64_t cipher = binPowMod(static_cast<uint8_t>(ch), kBE, n, false);
        encryptedForBob.push_back(cipher);
    }

    //Боб получает
    cout << "\nB получает зашифрованное сообщение." << endl;

    uint64_t dB = modInverse(kBE, n - 1, false);
    string receivedMessage;

    for (uint64_t cipher : encryptedForBob) {
        uint64_t decrypted = binPowMod(cipher, dB, n, false);

        receivedMessage += static_cast<char>(decrypted);
    }

    cout << "B расшифровывает сообщение: " << receivedMessage << endl;

    return 0;
}