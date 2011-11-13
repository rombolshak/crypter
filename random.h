#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>
class Random
{
    static const uint32_t	xInit = 123456789,
				yInit = 362436069,
				zInit = 521288629,
				wInit = 88675123;
    
    uint32_t x, y, z, w;
    

public:
    
    Random(uint32_t _seed = 123456789)
    { 
	this->x = _seed;
	y = yInit;
	z = zInit;
	w = wInit;
    }
    
    void seed (uint32_t _seed = xInit);
    
    
    uint32_t next();
    
};
#endif /* RANDOM_H */
