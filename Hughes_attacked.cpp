#include<iostream>
#include<cstdint>
#include<string>
#include<vector>

#include "binModPow.h"
#include "silentModInverse.h"

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
    uint64_t YB = binModPow(g, yB, n);
    cout << "\nB вычисляет:" << endl;
    cout << "YB = " << YB << endl;

    //Ева
    uint64_t YE = binModPow(g, yE, n);
    cout << "\nE перехватывает сообщение." << endl;
    cout << "E отправляет A своё значение:" << endl;
    cout << "YE = " << YE << endl;

    //Алиса
    uint64_t XA = binModPow(YE, xA, n);
    cout << "\nA вычисляет:" << endl;
    cout << "XA = " << XA << endl;

    //Ключ A-E
    uint64_t zE = modInverse(yE, n - 1);
    uint64_t kAE = binModPow(XA, zE, n);
    cout << "\nКлюч A-E: " << kAE << endl;

    //Ключ E-B
    uint64_t XE = binModPow(YB, yE, n);
    uint64_t zB = modInverse(yB, n - 1);
    uint64_t kBE = binModPow(XE, zB, n);
    cout << "Ключ E-B: " << kBE << endl;

    //Алиса отправляет
    string message = "HELLO";
    cout << "\nA отправляет сообщение: " << message << endl;

    vector<uint64_t> encryptedByAlice;

    //Алиса шифрует сообщение
    for (char ch : message) {
        uint64_t cipher = binModPow(static_cast<uint8_t>(ch), kAE, n);
        encryptedByAlice.push_back(cipher);
    }

    //Ева перехватывает
    uint64_t dAE = modInverse(kAE, n - 1);
    string interceptedMessage;

    cout << "\nE расшифровывает сообщение:" << endl;

    for (uint64_t cipher : encryptedByAlice) {
        uint64_t decrypted = binModPow(cipher, dAE, n);

        interceptedMessage += static_cast<char>(decrypted);
    }

    cout << interceptedMessage << endl;

    //Ева изменяет
    string modifiedMessage = "HI!";
    cout << "\nE изменяет сообщение на: " << modifiedMessage << endl;

    vector<uint64_t> encryptedForBob;

    //Ева шифрует сообщение для Боба
    for (char ch : modifiedMessage) {
        uint64_t cipher = binModPow(static_cast<uint8_t>(ch), kBE, n);
        encryptedForBob.push_back(cipher);
    }

    //Боб получает
    cout << "\nB получает зашифрованное сообщение." << endl;

    uint64_t dB = modInverse(kBE, n - 1);
    string receivedMessage;

    for (uint64_t cipher : encryptedForBob) {
        uint64_t decrypted = binModPow(cipher, dB, n);

        receivedMessage += static_cast<char>(decrypted);
    }

    cout << "B расшифровывает сообщение: " << receivedMessage << endl;

    return 0;
}