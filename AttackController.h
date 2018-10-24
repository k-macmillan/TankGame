#ifndef __ATTACKCONTROLLER_H__
#define __ATTACKCONTROLLER_H__
#include "projectx/src/PositionData.h"
#include "common.h"


class AttackController
{
public:
    AttackController(const int &Width,
                     const int &Height,
                     const std::vector<bool> &obstacleMap) : width(Width),
                                                             height(Height),
                                                             o_map(obstacleMap){}

    bearing attack(const std::vector<int> &map, const PositionData &status);

private:

    const uint16_t width;
    const uint16_t height;
    const std::vector<bool> o_map;


};

#endif