#ifndef __MOVECONTROLLER_H__
#define __MOVECONTROLLER_H__
#include "common.h"


class MoveController
{
public:
    MoveController(const int &Width,
                   const int &Height,
                   const std::vector<bool> &obstacleMap) : width(Width),
                                                           height(Height),
                                                           o_map(obstacleMap){}

    bearing move(const std::vector<int> &map, const Meta &meta);

    void printMap(const std::vector<int> &map);

private:

    const uint16_t width;
    const uint16_t height;
    const std::vector<bool> o_map;


};

#endif