#include "movementManager.h"
#include "ground.h"

movementManager::movementManager(const position&pos):d_position{pos}{}//,d_direction{direction}{}

//movementManager::movementManager(ground &g,const position&pos):d_ground{g},d_position{pos}{}

position movementManager::getPos() const
{
    return d_position;
}

/*
int movementManager::getDirection() const
{
    return d_direction;
}
*/