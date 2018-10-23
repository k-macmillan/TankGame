// g++ -shared -o TankYou.so -fPIC TankYou.cpp -std=c++11 -DDYNAMIC

#include "TankYou.h"
#include <iostream>

TankYou::TankYou() {
    name = "Kung Fury";    
}
TankYou::~TankYou() {
    std::cout << "Cleaning up controllers..." << std::endl;
    if (mc != nullptr){
        delete mc;
    }
}

/**
 * @author David Donahue
 * @par Description:
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return direction to move
 */
direction TankYou::move(MapData map, PositionData status)
{
    if (mc == nullptr){
        mc = new MoveController(map.width, map.height, map.obstacleMap);
    }
    
    return direction(mc->move(map.map, status));
    
}

/**
 * @author David Donahue
 * @par Description: 
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return Location to attack and whether to attack
 */
direction TankYou::attack(MapData map, PositionData status)
{
    return LEFT;
    direction ret = STAY;
    int min_dist = map.width * map.height + 1; //Guaranteed to be greater than any real distance
    // for (int x = 0; x < map.width; ++x)
    // {
    //     for (int y = 0; y < map.height; ++y)
    //     {
    //         //If an enemy is encountered closer than previously encountered
    //         if ( map.map[x + y*map.width] && //if there is an actor at X, Y
    //              map.map[x + y*map.width] != status.id && //And it is not you
    //              map.map[x + y*map.width] != -status.id && //And it is not your projectile
    //              calcDist(status.game_x, status.game_y, x, y) < min_dist) //And it is the closest one
    //         {
    //             if (x == status.game_x || y == status.game_y ||(
    //                     abs(x - status.game_x) == abs(status.game_y - y)))
    //             {
    //                 min_dist = calcDist(status.game_x, status.game_y, x, y);
    //                 if (status.game_x == x)
    //                 {
    //                     ret = (y > status.game_y) ? DOWN : UP;
    //                 }
    //                 else if (status.game_y == y)
    //                 {
    //                     ret = (x > status.game_x) ? RIGHT : LEFT;
    //                 }
    //                 else if (status.game_x > x) //to the upright or downright
    //                 {
    //                     ret = (y > status.game_y) ? DOWNLEFT : UPLEFT;
    //                 }
    //                 else
    //                 {
    //                     ret = (y > status.game_y) ? DOWNRIGHT : UPRIGHT;
    //                 }
    //             }
            
    //         }
    //     }
    // }
    return ret;
}

/**
 * @author David Donahue
 * @par Description:
 * Returns the attributes for the tank
 * @param[in] pointsAvailable - available points for the distribution
 * @return attributes of the tank
 */
attributes TankYou::setAttribute(int pointsAvailable)
{
    std::cout << "Points available: " << pointsAvailable << std::endl;
    // int hp = 1;
    // int dmg = 0;
    // int range = 0;  
    // int shots = 0;  // Does this count against pointsAvailable?
    // pointsAvailable -= 1;
    // while (pointsAvailable > 0){
    //     ++range;
    //     --pointsAvailable;
    // }

    attributes tankAttributes;
    tankAttributes.tankHealth = 1;
    return tankAttributes;
}



int TankYou::spendAP(MapData map, PositionData status)
{
    if (mc != nullptr){
        mc->printMap(map.map);
    }

    // for (size_t i = 0; i < map.map.size(); ++i){
    //         if(i % map.width == 0){
    //             std::cout << std::endl;
    //         }
    //         std::cout << std::setw(3) << std::right << map.map.at(i);
    //     }
    //     std::cout << std::endl << std::endl;

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
