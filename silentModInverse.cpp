#include "silentModInverse.h"
#include "silentExEvclid.h"

#include <iostream>

using namespace std;

int64_t modInverse(int64_t c, int64_t m) {

    int64_t u, v;

    int64_t gcd = exEvclid(c, m, u, v);

    if (gcd != 1) {
        return -1;
    }
    int64_t d = (u % m + m) % m;

    return d;
}