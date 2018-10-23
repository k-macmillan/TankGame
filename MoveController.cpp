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

bearing MoveController::move(const std::vector<int> &map, const PositionData &status){
    int min_dist = width * height + 1;
    bearing ret = bearing::STAY;
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            //If an enemy is encountered closer than previously encountered
            if ( map[x + y*width] > 0 &&
                 map[x + y*width] != status.id &&
                 calcDist(status.game_x, status.game_y, x, y) < min_dist &&
                 calcDist(status.game_x, status.game_y, x, y) > 1)
            {
                min_dist = calcDist(status.game_x, status.game_y, x, y);

                if (std::abs(status.game_x - x) > std::abs(status.game_y - y)) //more horizontal distance
                {
                    if (status.game_x > x)
                    {
                        if(!o_map[status.game_x - 1 + status.game_y * width]) //check for obstacle
                        {
                            ret = bearing::LEFT;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_y > y) ? bearing::UP : bearing::DOWN; //avoid it up or down
                        }
                    }
                    else
                    {
                        if(!o_map[status.game_x + 1 + status.game_y * width]) //check for obstacle
                        {
                            ret = bearing::RIGHT;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_y > y) ? bearing::UP : bearing::DOWN; //avoid it up or down
                        }
                    }

                }
                else
                {
                    if (status.game_y > y)
                    {
                        if(!o_map[status.game_x + (status.game_y - 1)*width]) //check for obstacle
                        {
                            ret = bearing::UP;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_x > x) ? bearing::LEFT : bearing::RIGHT; //avoid it left or right
                        }
                    }
                    else
                    {
                        if(!o_map[status.game_x + (status.game_y + 1)*width]) //check for obstacle
                        {
                            ret = bearing::DOWN;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_x > x) ? bearing::LEFT : bearing::RIGHT; //avoid it left or right
                        }
                    }
                }
            }
        }
    }
    // return bearing::LEFT;
    return ret;
}


/**
 * @author David Donahue
 * @par Description: 
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] x1 - starting point x coordinate
 * @param[in] y1 - starting point y coordinate
 * @param[in] x2 - end point x coordinate
 * @param[in] y2 - end point y coordinate
 * @return distance to the target
 */
int MoveController::calcDist(const int &x1, const int &y1, const int &x2, const int &y2)
{
    return (std::abs(x1 - x2) + std::abs(y1 - y2));
}