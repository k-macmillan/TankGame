#ifndef __TANKYOU_H__
#define __TANKYOU_H__

#include "projectx/src/Actor.h"
#include "projectx/src/direction.h"
#include "MoveController.h"
#include <cmath>

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
    /**
     * calculates how many moves it will take to reach a given coordinate
     * @param[in] x1 - starting point x coordinate
     * @param[in] y1 - starting point y coordinate
     * @param[in] x2 - end point x coordinate
     * @param[in] y2 - end point y coordinate
     * @return distance to the target
     */

    TankYou();
    ~TankYou();

    // void printMap(const MapData &map);
private:
    MoveController *mc = nullptr;

};

#endif
