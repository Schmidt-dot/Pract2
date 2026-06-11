#include "modInverse.h"
#include "exEvclid.h"

#include <iostream>

using namespace std;

int64_t modInverse(int64_t c, int64_t m, bool isPrint) {

    int64_t u, v;

    int64_t gcd = exEvclid(c, m, u, v, true);

    if (isPrint){}
    if (gcd != 1) {

        cout << "\nОбратного элемента не существует," << " так как НОД ≠ 1." << endl;

        return -1;
    }

    int64_t d = (u % m + m) % m;

    if (isPrint){
        cout << "\nВзаимообратное число:" << endl;
        cout << c << "^(-1) mod " << m << " = " << d << endl;
        }
    return d;
}