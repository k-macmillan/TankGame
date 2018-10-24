#include "common.h"

int16_t calcDist(const Point &a, const Point &b)
{
    return (std::abs(a.x - b.x) + std::abs(a.y - b.y));
}
