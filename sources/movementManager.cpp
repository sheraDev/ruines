#include "movementManager.h"
#include "ground.h"

movementManager::movementManager(const position&pos):d_position{pos}{}


position movementManager::getPos() const
{
    return d_position;
}

