#include "task1.h"
#include "tFerma.h"

#include <iostream>
#include <cstdint>

using namespace std;

void task1() {

    uint64_t a, x, p;

    cout << "Введите a: ";
    cin >> a;

    cout << "Введите x: ";
    cin >> x;

    cout << "Введите p: ";
    cin >> p;

    cout << endl;

    uint64_t result = tFerma(a, x, p);

    cout << "\nОтвет: " << result << endl;
}