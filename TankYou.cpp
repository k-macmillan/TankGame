// g++ -shared -o TankYou.so -fPIC TankYou.cpp MoveController.cpp common.cpp -std=c++11 -DDYNAMIC

#include "TankYou.h"
#include <iostream>

TankYou::TankYou() {
    name = "Kung Fury";    
}
TankYou::~TankYou() {
    std::cout << "Cleaning up controllers..." << std::endl;
    if (init){
        delete mc;
        delete ac;
    }
}

void TankYou::initializeControllers(const MapData &map, const PositionData &status){
    // Transfered to each instead of centralized to reduce conversions
    mc = new MoveController(map.width, map.height, map.obstacleMap);
    ac = new AttackController(map.width, map.height, map.obstacleMap);
    init = true;
}


// Move command
direction TankYou::move(MapData map, PositionData status)
{    
    return direction(mc->move(map.map, status));    
}


// Attack command
direction TankYou::attack(MapData map, PositionData status)
{
    return direction(ac->attack(map.map, status));
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
        initializeControllers(map, status);
    }

    return 1;




    if (move(map, status) == STAY && attack(map,status) != STAY) //If there is nowhere to move, attack
        return 2;
    
    if (attack(map, status) == STAY && move(map,status) != STAY) //If there is nowhere to attack, move
        return 1;

    if (attack(map,status) == STAY && move(map,status) == STAY) //If there is nothing to do, end your turn
        return 3;
    
    return (status.ap > 1) ? 1 : 2;
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
