#pragma once

#include <cstdint>

bool isPrime(uint64_t x);

uint64_t gcd(uint64_t a, uint64_t b);

uint64_t binPowMod(uint64_t base, uint64_t power, uint64_t modul, bool isPrint);

uint64_t tFerma(uint64_t a, uint64_t x, uint64_t p, bool isPrint);