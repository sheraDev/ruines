#ifndef ADVENTURERMOVEMANAGER_H_INCLUDED
#define ADVENTURERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;

class adventurerMoveManager : public movementManager
{
    public:
        adventurerMoveManager(const position& p, int direction);
        void move(ground &g) override;
        position directionPosition(int direction) override;



};


#endif