#ifndef ADVENTURERMOVEMANAGER_H_INCLUDED
#define ADVENTURERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;

class adventurerMoveManager : public movementManager
{
    public:
        adventurerMoveManager(const position&pos);
        void move(ground &g,int direction) override;
        position directionPosition(int direction) override;
};


#endif