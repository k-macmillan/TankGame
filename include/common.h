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
    Point();
    Point(int X, int Y) : x(X), y(Y){}

    // Copy constructor
    Point(const Point &p2) {x = p2.x; y = p2.y; } 

    // Useless for this game?
    int16_t L1dist(const Point &rhs){
        return std::abs(x - rhs.x) + std::abs(y - rhs.y);
    }

    // Since we can move diagonally this is our movement distance...Uniform norm
    int16_t Linf(const Point &rhs){
        return std::max(std::abs(x - rhs.x), std::abs(y - rhs.y));
    }
};

// Retooled PositionData
struct Meta{
    int16_t id;
    int16_t hp = 2;
    int16_t ap = 2;
    int16_t dmg = 1;
    Point p = {-1, -1};
    Meta();
    Meta(int ID, int Health, int AP, int Dmg, int X, int Y) : id(ID),
                                                              hp(Health),
                                                              ap(AP),
                                                              dmg(Dmg),
                                                              p(Point(X,Y)){}

    // Copy constructor
    Meta(const Meta &m2) {id = m2.id;
                          hp = m2.hp;
                          ap = m2.ap;
                          dmg = m2.dmg;
                          p = m2.p;} 
};

int16_t calcDist(const Point &a, const Point &b);

#endif