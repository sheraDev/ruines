#ifndef ADVENTURERMOVEMANAGER_H_INCLUDED
#define ADVENTURERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;

class adventurerMoveManager : public movementManager
{
    public:
        adventurerMoveManager(const position&pos);//const position& p, int direction);
        void move(ground &g,int direction) override;
       //void move(int direction) override;
        position directionPosition(int direction) override;

    


};


#endif