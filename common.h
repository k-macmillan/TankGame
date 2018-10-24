#ifndef __COMMON_H__
#define __COMMON_H__
#include <cmath>
#include <stdint.h>     // Integer standards
#include <iostream>     // cout
#include <iomanip>      // setw, right
#include <vector>

enum class bearing {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, STAY};

int calcDist(const int &x1, const int &y1, const int &x2, const int &y2);

#endif