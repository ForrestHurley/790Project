#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <limits>
#include <stdint.h>

class xorshift
{
public:
    xorshift(bool reseed = false);

    void reseed();

    typedef uint64_t result_type;
    static uint64_t min() { return 0; }
    static uint64_t max() { return std::numeric_limits<uint64_t>::max(); }
    uint64_t operator()();
};

#endif
