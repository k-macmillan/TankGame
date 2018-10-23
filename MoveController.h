#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__
#include <stdint.h>     // Integer standards
#include <iostream>
#include <iomanip>
#include <vector>
#include "projectx/src/PositionData.h"

enum class bearing {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, STAY};

class MoveController
{
public:
    MoveController(const int &Width,
                   const int &Height,
                   const std::vector<bool> &obstacleMap) : width(Width),
                                                           height(Height),
                                                           o_map(obstacleMap){}

    // direction move(const std::vector<int> map, const PositionData &status);

    void printMap(const std::vector<int> &map);
    bearing move(const std::vector<int> &map, const PositionData &status);
private:
    int calcDist(const int &x1, const int &y1, const int &x2, const int &y2);

    const uint16_t width;
    const uint16_t height;
    const std::vector<bool> o_map;


};

#endif