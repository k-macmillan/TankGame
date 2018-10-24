#include "AttackController.h"

bearing AttackController::attack(const std::vector<int> &map, const Meta &meta){
    bearing ret = bearing::STAY;
    int16_t min_dist = width * height + 1; //Guaranteed to be greater than any real distance
    for (int16_t x = 0; x < width; ++x)
    {
        for (int16_t y = 0; y < height; ++y)
        {
            Point p = Point(x, y);
            //If an enemy is encountered closer than previously encountered
            if ( map[x + y*width] && //if there is an actor at X, Y
                 map[x + y*width] != meta.id && //And it is not you
                 map[x + y*width] != -meta.id && //And it is not your projectile
                 calcDist(meta.p, p) < min_dist) //And it is the closest one
            {
                if (x == meta.p.x || y == meta.p.y ||(
                        std::abs(x - meta.p.x) == std::abs(meta.p.y - y)))
                {
                    min_dist = calcDist(meta.p, p);
                    if (meta.p.x == x)
                    {
                        ret = (y > meta.p.y) ? bearing::DOWN : bearing::UP;
                    }
                    else if (meta.p.y == y)
                    {
                        ret = (x > meta.p.x) ? bearing::RIGHT : bearing::LEFT;
                    }
                    else if (meta.p.x > x) //to the upright or downright
                    {
                        ret = (y > meta.p.y) ? bearing::DOWNLEFT : bearing::UPLEFT;
                    }
                    else
                    {
                        ret = (y > meta.p.y) ? bearing::DOWNRIGHT : bearing::UPRIGHT;
                    }
                }
            
            }
        }
    }
    return ret;
}