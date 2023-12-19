#ifndef BLINDMONSTERMOVEMANAGER_H_INCLUDED
#define BLINDMONSTERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;


//UN MONSTRE AVEUGLE SE DEPLACE ALEATOIREMENT

class blindMonsterMoveManager : public movementManager
{
    public:
        blindMonsterMoveManager(const position &p);
        position directionPosition(int direction) override;
        position possiblePosition(ground &g);
        void move(ground &g,int direction=0) override;//ground &g) override;


};

//maj position après move ?

#endif