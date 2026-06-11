#include "inputFraction.h"

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

void inputFraction() {

    int64_t A = 439;
    int64_t B = 118;
    int64_t D = 3;

    cout << "Решаем уравнение:" << endl;
    cout << A << "a + " << B << "b = " << D << endl << endl;

    //Цепная дробь
    vector<int64_t> cf;

    int64_t a = A;
    int64_t b = B;

    while (b != 0) {
        cf.push_back(a / b);

        int64_t r = a % b;
        a = b;
        b = r;
    }

    cout << "Цепная дробь " << A << "/" << B << ":" << endl;
    cout << "[" << cf[0];

    for (uint64_t i = 1; i < cf.size(); i++) {
        cout << "; " << cf[i];
    }

    cout << "]" << endl << endl;

    int64_t gcd = a;

    cout << "НОД = " << gcd << endl;

    if (D % gcd != 0) {
        cout << "Целых решений нет." << endl;
        return;
    }

    // Подходящие дроби
    int64_t p2 = 0, p1 = 1;
    int64_t q2 = 1, q1 = 0;

    int64_t p = 0, q = 0;

    cout << endl << "Подходящие дроби:" << endl;

    for (uint64_t i = 0; i < cf.size(); i++) {

        p = cf[i] * p1 + p2;
        q = cf[i] * q1 + q2;

        cout << p << "/" << q << endl;

        p2 = p1;
        p1 = p;

        q2 = q1;
        q1 = q;
    }

    // Предпоследняя подходящая дробь
    int64_t P = p2;
    int64_t Q = q2;

    int64_t x, y;

    if (cf.size() % 2 == 0) {
        x = Q;
        y = -P;
    }
    else {
        x = -Q;
        y = P;
    }

    // Получаем решение для D
    x *= D / gcd;
    y *= D / gcd;

    cout << endl << "Частное решение:" << endl;
    cout << "a = " << x << endl;
    cout << "b = " << y << endl << endl;

    cout << "Общее решение:" << endl;
    cout << "a = " << x << " + " << B / gcd << "t" << endl;
    cout << "b = " << y << " - " << A / gcd << "t" << endl;
    cout << "t принадлежит Z" << endl;
}