#include "Hackerman.h"

Hackerman::Hackerman(const MapData &map, const PositionData &status) : Hitlers(4, Meta{0, 2, 2, 1, -1, -1}),
                                                                       width(map.width),
                                                                       height(map.height),
                                                                       o_map(map.obstacleMap),
                                                                       max_ap(status.ap),
                                                                       mc(new MoveController(map.width, map.height, map.obstacleMap)),
                                                                       ac(new AttackController(map.width, map.height, map.obstacleMap)){
    for (int i = 0; i < 4; ++i){
        Hitlers.at(i).id = i;
    }
    updateStatus(map.map, status);
}

Hackerman::~Hackerman(){
    std::cout << "Cleaning up controllers..." << std::endl;
    delete mc;
    delete ac;
}

void Hackerman::updateKungFury(const PositionData &status){
    KungFury.id = status.id;
    KungFury.hp = status.health;
    KungFury.ap = status.ap;
    KungFury.p = Point(status.game_x, status.game_y);
}

void Hackerman::updateStatus(const std::vector<int> &map, const PositionData &status){
    updateKungFury(status);
    enemyUpdate(map);

#ifdef DEBUG
    for (auto item : Hitlers){
        if (item.p.x != -1){
            printStatus(item);
        }
    }
#endif
    ++rounds;
}


void Hackerman::printStatus(const Meta &m){
    std::cout << std::setw(7) << std::right << "ID: " << m.id << std::endl;
    std::cout << std::setw(7) << std::right << "HP: " << m.hp << std::endl;
    std::cout << std::setw(7) << std::right << "AP: " << m.ap << std::endl;
    std::cout << std::setw(7) << std::right << "loc: " << "(" << m.p.x << ", " << m.p.y << ")" << std::endl;
    std::cout << "Enemies: " << enemy_count << std::endl << std::endl;
}


void Hackerman::enemyUpdate(const std::vector<int> &map){
    enemy_count = 0;
    for (uint16_t i = 0; i < map.size(); ++i){
        // Account for tanks and ammo        
        if (map.at(i) != 0 && map.at(i) > 0){
            uint8_t idx = map.at(i);
            if (idx != KungFury.id){
                ++enemy_count;
                std::div_t loc{};
                loc = std::div(i, width);
                Hitlers.at(idx).id = idx;
                Hitlers.at(idx).p.x = loc.rem;
                Hitlers.at(idx).p.y = loc.quot;
            }
        }
    }
}


int Hackerman::determineAction(const std::vector<int> &map, const PositionData &status){
    updateStatus(map, status);

    mv = direction(mc->move(map, KungFury));
    atk = direction(ac->attack(map, KungFury));

    if (mv == STAY && atk != STAY) //If there is nowhere to move, attack
        return 2;
    
    if (atk == STAY && mv != STAY){ //If there is nowhere to attack, move
        return 1;        
    }
    if (atk == STAY && mv == STAY){ //If there is nothing to do, end your turn
        return 3;
    }
    
    return (KungFury.ap > 1) ? 1 : 2;
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