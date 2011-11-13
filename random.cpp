#include "random.h"

void Random::seed (uint32_t _seed)
{
    x = _seed;
    y = yInit;
    z = zInit;
    w = wInit;
}

uint32_t Random::next()
{
    uint32_t t;
    
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}