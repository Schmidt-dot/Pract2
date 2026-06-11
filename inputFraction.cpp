#include "inputFraction.h"
#include "exEvclid.h"

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
    vector<int64_t> q;

    int64_t a = A;
    int64_t b = B;

    while (b != 0) {
        q.push_back(a / b);

        int64_t r = a % b;
        a = b;
        b = r;
    }

    cout << "Цепная дробь " << A << "/" << B << ":" << endl;
    cout << "[" << q[0];

    for (uint64_t i = 1; i < q.size(); i++) {
        cout << "; " << q[i];
    }

    cout << "]" << endl << endl;

    int64_t x, y;
    int64_t gcd = exEvclid(A, B, x, y, true);

    cout << "НОД = " << gcd << endl;

    if (D % gcd != 0) {
        cout << "Целых решений нет." << endl;
        return;
    }

    x *= D / gcd;
    y *= D / gcd;

    cout << "Частное решение:" << endl;
    cout << "a = " << x << endl;
    cout << "b = " << y << endl << endl;

    cout << "Общее решение:" << endl;
    cout << "a = " << x << " + " << B / gcd << "t" << endl;
    cout << "b = " << y << " - " << A / gcd << "t" << endl;
    cout << "t принадлежит Z" << endl;
}