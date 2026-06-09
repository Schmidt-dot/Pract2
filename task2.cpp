#include "task2.h"
#include "exEvclid.h"

#include <iostream>
#include <cstdint>

using namespace std;

void task2() {

    int64_t a, b;

    cout << "Расширенный алгоритм Евклида" << endl;

    cout << "Введите a: ";
    cin >> a;

    cout << "Введите b: ";
    cin >> b;

    int64_t u, v;

    exEvclid(a, b, u, v);
}