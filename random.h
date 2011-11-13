#ifndef RANDOM_H
#define RANDOM_H

class Random
{
    static const unsigned long 	xInit = 123456789,
				yInit = 362436069,
				zInit = 521288629,
				wInit = 88675123;
    
    unsigned long x, y, z, w;
    

public:
    
    Random(int _seed = 123456789)
    { 
	this->x = _seed;
	y = yInit;
	z = zInit;
	w = wInit;
    }
    
    void seed (int _seed = xInit);
    
    
    unsigned long next();
    
};
#endif /* RANDOM_H */
