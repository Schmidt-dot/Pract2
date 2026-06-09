#include "tFerma.h"

#include <iostream>
#include <cstdint>

using namespace std;


//ПРОВЕРКА НА ПРОСТОТУ
bool isPrime(uint64_t x) {

    if (x <= 1) return false;

    if (x <= 3) return true;

    if (x % 2 == 0) return false;

    for (uint64_t i = 3; i <= x / i; i += 2) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}


//ПОИСК ОБЩЕГО ДЕЛИТЕЛЯ
uint64_t gcd(uint64_t a, uint64_t b) {

    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}


//БИНАРНОЕ ВОЗВДЕНИЕ В СТЕПЕНЬ ПО МОДУЛЮ
uint64_t binPowMod(uint64_t base, uint64_t power, uint64_t modul) {

    cout << "\nВозведение в степень:" << endl;

    base %= modul;

    uint64_t result = 1;

    while (power != 0) {

        cout << "Результат = " << result << ", основание = " << base << ", степень = " << power << endl;

        if (power % 2 == 1) {

            uint64_t oldResult = result;

            result = (result * base) % modul;

            cout << oldResult << " * " << base << " mod " << modul << " = " << result << endl;
        }

        uint64_t oldBase = base;

        base = (base * base) % modul;

        cout << oldBase << "^2 mod " << modul << " = " << base << endl;

        power /= 2;
    }
    return result;
}


//ТЕОРЕМА ФЕРМА
uint64_t tFerma(uint64_t a, uint64_t x, uint64_t p) {

    if (!isPrime(p) || gcd(a, p) != 1) {

        cout << "Условия теоремы Ферма не выполняются" << endl;
        cout << "Вычисление выполняется бинарным возведением:" << endl;

        uint64_t result = binPowMod(a, x, p);

        cout << "\nРезультат: " << result << endl;

        return result;
    }

    uint64_t reducePow = x % (p - 1);

    cout << "Условия теоремы Ферма выполняются." << endl;

    cout << "Сокращение степени:" << endl;

    cout << x << " mod " << (p - 1) << " = " << reducePow << endl;

    uint64_t result = binPowMod(a, reducePow, p);

    cout << "\nРезультат (Ферма): " << result << endl;

    return result;
}