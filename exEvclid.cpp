#include "exEvclid.h"

#include <iostream>
#include<iomanip>


using namespace std;

int64_t exEvclid(int64_t a, int64_t b, int64_t& u, int64_t& v) {

    int64_t u0 = 1, u1 = 0;
    int64_t v0 = 0, v1 = 1;

    int n = 0;

    cout << "\nРасширенный алгоритм Евклида:" << endl;

    cout << setw(4) << "n"
         << setw(6) << "a"
         << setw(6) << "b"
         << setw(6) << "q"
         << setw(6) << "r"
         << setw(6) << "u"
         << setw(6) << "v"
         << endl;

    while (b != 0) {

        int64_t q = a / b;
        int64_t r = a % b;

        cout << setw(4) << n
             << setw(6) << a
             << setw(6) << b
             << setw(6) << q
             << setw(6) << r
             << setw(6) << u0
             << setw(6) << v0
             << endl;

        int64_t temp = b;
        b = r;
        a = temp;

        temp = u1;
        u1 = u0 - q * u1;
        u0 = temp;

        temp = v1;
        v1 = v0 - q * v1;
        v0 = temp;

        n++;
    }

    u = u0;
    v = v0;

    //Последняя строка 
    cout << setw(4) << n
         << setw(6) << a
         << setw(6) << b
         << setw(6) << "-"
         << setw(6) << "-"
         << setw(6) << u
         << setw(6) << v
         << endl;

    cout << "\nНОД = " << a << endl;

    cout << "u = " << u << endl;
    cout << "v = " << v << endl;

    return a;
}