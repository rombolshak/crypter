#include "random.h"
void Random::seed (int _seed)
{
    x = _seed;
    y = yInit;
    z = zInit;
    w = wInit;
}

long unsigned int Random::next()
{
    unsigned long t;
    
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}