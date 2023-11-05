#include "movementManager.h"
#include "ground.h"

movementManager::movementManager(const position&pos, int direction):d_position{pos},d_direction{direction}{}

position movementManager::getPos() const
{
    return d_position;
}
        
int movementManager::getDirection() const
{
    return d_direction;
}
