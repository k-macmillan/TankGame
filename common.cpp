#include "common.h"

/**
 * @author David Donahue
 * @par Description: 
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] x1 - starting point x coordinate
 * @param[in] y1 - starting point y coordinate
 * @param[in] x2 - end point x coordinate
 * @param[in] y2 - end point y coordinate
 * @return distance to the target
 */
int calcDist(const int &x1, const int &y1, const int &x2, const int &y2)
{
    return (std::abs(x1 - x2) + std::abs(y1 - y2));
}