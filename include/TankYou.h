#ifndef __TANKYOU_H__
#define __TANKYOU_H__

#include "../projectx/src/Actor.h"
#include "../projectx/src/direction.h"
#include "common.h"
#include "MoveController.h"
#include "AttackController.h"

class TankYou : public Actor
{
public:
    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(MapData map, PositionData status);

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual direction attack(MapData map, PositionData status);

    virtual attributes setAttribute(int pointsAvailable);

    virtual int spendAP(MapData map, PositionData status);

    void initializeControllers(const MapData &map, const PositionData &status);
    void updateStatus(const PositionData &status);
    void printStatus();

    TankYou();
    ~TankYou();

private:
    bool init = false;
    Meta metadata = Meta(0, 0, 0, 0, 0);

    MoveController *mc = nullptr;
    AttackController *ac = nullptr;
};

#endif
