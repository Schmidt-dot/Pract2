#include "binPowMod.h"

using namespace std;


uint64_t binPowMod(uint64_t base, uint64_t power, uint64_t modul) {

    base %= modul;
    uint64_t result = 1;

    while (power != 0) {
        if (power % 2 == 1) {
            result = (result * base) % modul;
        }
        base = (base * base) % modul;
        power /= 2;
    }
    return result;
}