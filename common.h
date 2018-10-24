#ifndef __COMMON_H__
#define __COMMON_H__
#include <cmath>
#include <stdint.h>     // Integer standards
#include <iostream>     // cout
#include <iomanip>      // setw, right
#include <vector>

enum class bearing {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, STAY};

struct Point{
    int16_t x;
    int16_t y;
    Point(int X, int Y) : x(X), y(Y){}
};

// Retooled PositionData
struct Meta{
    int16_t id;
    int8_t hp;
    int8_t ap;
    Point p;
    Meta(int ID, int Health, int AP, int X, int Y) : id(ID),
                                                     hp(Health),
                                                     ap(AP),
                                                     p(Point(X,Y)){}
};

int16_t calcDist(const Point &a, const Point &b);

#endif