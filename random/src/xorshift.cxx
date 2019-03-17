#include "xorshift.h"
#include <random>
#include <iostream>

extern "C" {
    void seed(uint64_t in[4]);
    uint64_t next(void);
    void jump(void);
    void long_jump(void);
}

xorshift::xorshift(bool reseed_generator)
{
    if (reseed_generator)
        reseed();
}

void xorshift::reseed()
{
    std::random_device rd;
    uint64_t seed_value[4];
    for (int i = 0; i < 4; i++)
    {
        uint32_t a, b;
        a = rd();
        b = rd();
        seed_value[i] = (uint64_t)a << 32 | b;
    }

    seed(seed_value);
}

uint64_t xorshift::operator()()
{
    return next();
}
