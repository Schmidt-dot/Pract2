#include "task3.h"
#include "modInverse.h"

#include <iostream>
#include <cstdint>

using namespace std;

void task3() {

    int64_t c, m;

    cout << "Вычисление c^(-1) mod m" << endl;

    cout << "Введите c: ";
    cin >> c;

    cout << "Введите m: ";
    cin >> m;

    if (m == 0) {

        cout << "Ошибка: m не может быть равно 0" << endl;

        return;
    }

    cout << endl;

    int64_t d = modInverse(c, m);

    if (d == -1) {
        return;
    }

    cout << "\nПроверка:" << endl;

    cout << c << " * " << d << " mod " << m << " = " << (c * d) % m << endl;
}