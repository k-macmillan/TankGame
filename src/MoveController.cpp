#include "MoveController.h"

void MoveController::printMap(const std::vector<int> &map){
    for (size_t i = 0; i < map.size(); ++i){            
        if(i % width == 0){
            std::cout << std::endl;
        }
        std::cout << std::setw(3) << std::right << map.at(i);
    }
    std::cout << std::endl << std::endl;
}

bearing MoveController::move(const std::vector<int> &map, const Meta &meta){
#ifdef DEBUG
    printMap(map);
#endif
    int16_t min_dist = width * height + 1;
    bearing ret = bearing::STAY;
    for (int16_t x = 0; x < width; ++x)
    {
        for (int16_t y = 0; y < height; ++y)
        {
            Point p = Point(x, y);
            //If an enemy is encountered closer than previously encountered
            if ( map[x + y * width] > 0 &&
                 map[x + y * width] != meta.id &&
                 calcDist(meta.p, p) < min_dist &&
                 calcDist(meta.p, p) > 1)
            {
                min_dist = calcDist(meta.p, p);

                if (std::abs(meta.p.x - x) > std::abs(meta.p.y - y)) //more horizontal distance
                {
                    if (meta.p.x > x)
                    {
                        if(!o_map[meta.p.x - 1 + meta.p.y * width]) //check for obstacle
                        {
                            ret = bearing::LEFT;
                        }
                        else //obstacle in the way
                        {
                            ret = (meta.p.y > y) ? bearing::UP : bearing::DOWN; //avoid it up or down
                        }
                    }
                    else
                    {
                        if(!o_map[meta.p.x + 1 + meta.p.y * width]) //check for obstacle
                        {
                            ret = bearing::RIGHT;
                        }
                        else //obstacle in the way
                        {
                            ret = (meta.p.y > y) ? bearing::UP : bearing::DOWN; //avoid it up or down
                        }
                    }

                }
                else
                {
                    if (meta.p.y > p.y)
                    {
                        if(!o_map[meta.p.x + (meta.p.y - 1)*width]) //check for obstacle
                        {
                            ret = bearing::UP;
                        }
                        else //obstacle in the way
                        {
                            ret = (meta.p.x > x) ? bearing::LEFT : bearing::RIGHT; //avoid it left or right
                        }
                    }
                    else
                    {
                        if(!o_map[meta.p.x + (meta.p.y + 1)*width]) //check for obstacle
                        {
                            ret = bearing::DOWN;
                        }
                        else //obstacle in the way
                        {
                            ret = (meta.p.x > x) ? bearing::LEFT : bearing::RIGHT; //avoid it left or right
                        }
                    }
                }
            }
        }
    }
    return ret;
}


