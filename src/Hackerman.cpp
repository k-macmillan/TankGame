#include "Hackerman.h"

Hackerman::Hackerman(const MapData &map, const PositionData &status) : max_ap(status.ap),
                                                                       mc(new MoveController(map.width, map.height, map.obstacleMap)),
                                                                       ac(new AttackController(map.width, map.height, map.obstacleMap)){
}

Hackerman::~Hackerman(){
    std::cout << "Cleaning up controllers..." << std::endl;
    delete mc;
    delete ac;
}


void Hackerman::updateStatus(const std::vector<int> &map, const PositionData &status){
    metadata.id = status.id;
    metadata.hp = status.health;
    metadata.ap = status.ap;
    metadata.p = Point(status.game_x, status.game_y);

    // Calculate enemies once per round
    if (rounds % max_ap == 0){
        enemy_count = enemyCount(map);
#ifdef DEBUG
        printStatus();
#endif
    }
    ++rounds;
}


void Hackerman::printStatus(){
    std::cout << std::setw(7) << std::right << "ID: " << metadata.id << std::endl;
    std::cout << std::setw(7) << std::right << "HP: " << metadata.hp << std::endl;
    std::cout << std::setw(7) << std::right << "AP: " << metadata.ap << std::endl;
    std::cout << std::setw(7) << std::right << "loc: " << "(" << metadata.p.x << ", " << metadata.p.y << ")" << std::endl;
    std::cout << "Enemies: " << enemy_count << std::endl << std::endl;
}



uint16_t Hackerman::enemyCount(const std::vector<int> &map){
    uint16_t count = 0;
    for (uint16_t i = 0; i < map.size(); ++i){
        // Account for tanks and ammo
        if (map.at(i) != 0 && map.at(i) > 0){
            ++count;
        }
    }
    return --count;
}

int Hackerman::determineAction(const std::vector<int> &map, const PositionData &status){
    updateStatus(map, status);

    mv = direction(mc->move(map, metadata));
    atk = direction(ac->attack(map, metadata));

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





//////////////////// GETTERS ////////////////////
direction Hackerman::getMove(){
#ifdef DEBUG
    std::cout << "Move: " << mv << std::endl;
#endif
    return mv;
}

direction Hackerman::getAttack(){
#ifdef DEBUG
    std::cout << "Attack: " << atk << std::endl;
#endif
    return atk;
}