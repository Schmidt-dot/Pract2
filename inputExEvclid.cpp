#include "inputExEvclid.h"
#include "exEvclid.h"

#include <iostream>
#include <cstdint>

using namespace std;

void inputExEvclid() {

    int64_t a, b;

    cout << "Расширенный алгоритм Евклида" << endl;

    cout << "Введите a: ";
    cin >> a;

    cout << "Введите b: ";
    cin >> b;

    int64_t u, v;

    exEvclid(a, b, u, v);
}