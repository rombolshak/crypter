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