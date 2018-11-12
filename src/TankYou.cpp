
#include "TankYou.h"


TankYou::TankYou() {
    name = "Kung Fury";
}
TankYou::~TankYou() {
    if (init){
        delete hc;
    }
}

void TankYou::initializeHackerman(const MapData &map, const PositionData &status){
    hc = new Hackerman(map, status);
    init = true;
}



// Move command
direction TankYou::move(MapData map, PositionData status)
{    
    return hc->getMove();    
}


// Attack command
direction TankYou::attack(MapData map, PositionData status)
{
    return hc->getAttack();
}

// Set initial bonus attributes
attributes TankYou::setAttribute(int pointsAvailable)
{
    attributes tankAttributes;
    tankAttributes.tankHealth = 1;
    return tankAttributes;
}


// Primary operation function
int TankYou::spendAP(MapData map, PositionData status)
{
    if (!init){
        initializeHackerman(map, status);
    }

    return hc->determineAction(map.map, status);
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new TankYou;
    }
}
#endif
