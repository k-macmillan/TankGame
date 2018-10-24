// g++ -shared -o TankYou.so -fPIC TankYou.cpp MoveController.cpp AttackController.cpp common.cpp -std=c++11 -DDYNAMIC

#include "TankYou.h"


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


void TankYou::updateStatus(const PositionData &status){
    metadata.id = status.id;
    metadata.hp = status.health;
    metadata.ap = status.ap;
    metadata.p = Point(status.game_x, status.game_y);
}

void TankYou::printStatus(){
    std::cout << std::setw(7) << std::right << "ID: " << metadata.id << std::endl;
    std::cout << std::setw(7) << std::right << "HP: " << metadata.id << std::endl;
    std::cout << std::setw(7) << std::right << "AP: " << metadata.id << std::endl;
    std::cout << std::setw(7) << std::right << "loc: " << "(" << metadata.p.x << ", " << metadata.p.y << ")" << std::endl;
}

// Move command
// NEVER CALLED
direction TankYou::move(MapData map, PositionData status)
{    
    return direction(mc->move(map.map, metadata));    
}


// Attack command
// NEVER CALLED
direction TankYou::attack(MapData map, PositionData status)
{
    return direction(ac->attack(map.map, metadata));
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
    updateStatus(status);
    // printStatus();

    direction mv = direction(mc->move(map.map, metadata));
    direction atk = direction(ac->attack(map.map, metadata));

    if (mv == STAY && atk != STAY) //If there is nowhere to move, attack
        return 2;
    
    if (atk == STAY && mv != STAY){ //If there is nowhere to attack, move
        return 1;        
    }
    
    if (atk == STAY && mv == STAY){ //If there is nothing to do, end your turn
        return 3;
    }
    
    return (metadata.ap > 1) ? 1 : 2;
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
