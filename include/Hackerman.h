#ifndef __HACKERMAN_H__
#define __HACKERMAN_H__
#include "../projectx/src/direction.h"
#include "../projectx/src/MapData.h"
#include "../projectx/src/PositionData.h"
#include "common.h"
#include "MoveController.h"
#include "AttackController.h"
#include <cstdlib>      // std::div_t


class Hackerman{
public:
    Hackerman(const MapData &map, const PositionData &status);
    ~Hackerman();


    void printStatus(const Meta &m);

    int determineAction(const std::vector<int> &map, const PositionData &meta);

    direction getMove();
    direction getAttack();


private:
    void updateKungFury(const PositionData &status);
    void updateStatus(const std::vector<int> &map, const PositionData &status);
    void enemyUpdate(const std::vector<int> &map);

    // uint16_t enemyCount(const std::vector<int> &map);

    Meta KungFury = Meta(0, 2, 2, 1, 0, 0);
    std::vector<Meta> Hitlers;
    direction mv = STAY;
    direction atk = STAY;
    uint16_t enemy_count = 0;
    uint16_t rounds = 0;

    const uint16_t width;
    const uint16_t height;
    const std::vector<bool> o_map;
    const uint8_t max_ap;
    MoveController * const mc;
    AttackController * const ac;
};

#endif
