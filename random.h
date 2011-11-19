/**
 * @version 1.0
 * 
 * This file is part of cmc2011RM blockcrypt.
 * 
 * cmc2011RM blockcrypt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cmc2011RM blockcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cmc2011RM blockcrypt.  If not, see <http://www.gnu.org/licenses/>.
 */
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
