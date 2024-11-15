#ifndef BLINDMONSTERMOVEMANAGER_H_INCLUDED
#define BLINDMONSTERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;


class blindMonsterMoveManager : public movementManager
{
    public:
        blindMonsterMoveManager(const position &p);
        position directionPosition(int direction) override;
        position possiblePosition(ground &g);
        void move(ground &g,int direction=0) override;
        int directionAleatoire() const;

};


#endif