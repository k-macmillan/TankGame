#include "common.h"

bearing AttackController::attack(const std::vector<int> &map, const PositionData &status){
    bearing ret = bearing::STAY;
    int min_dist = width * height + 1; //Guaranteed to be greater than any real distance
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            //If an enemy is encountered closer than previously encountered
            if ( map[x + y*width] && //if there is an actor at X, Y
                 map[x + y*width] != status.id && //And it is not you
                 map[x + y*width] != -status.id && //And it is not your projectile
                 calcDist(status.game_x, status.game_y, x, y) < min_dist) //And it is the closest one
            {
                if (x == status.game_x || y == status.game_y ||(
                        abs(x - status.game_x) == abs(status.game_y - y)))
                {
                    min_dist = calcDist(status.game_x, status.game_y, x, y);
                    if (status.game_x == x)
                    {
                        ret = (y > status.game_y) ? bearing::DOWN : bearing::UP;
                    }
                    else if (status.game_y == y)
                    {
                        ret = (x > status.game_x) ? bearing::RIGHT : bearing::LEFT;
                    }
                    else if (status.game_x > x) //to the upright or downright
                    {
                        ret = (y > status.game_y) ? bearing::DOWNLEFT : bearing::UPLEFT;
                    }
                    else
                    {
                        ret = (y > status.game_y) ? bearing::DOWNRIGHT : bearing::UPRIGHT;
                    }
                }
            
            }
        }
    }
    return ret;
}