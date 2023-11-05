#ifndef BLINDMONSTERMOVEMANAGER_H_INCLUDED
#define BLINDMONSTERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;


//UN MONSTRE AVEUGLE SE DEPLACE ALEATOIREMENT

class blindMonsterMoveManager : public movementManager
{
    public:
        blindMonsterMoveManager(const position &p);
        void move(ground &g) override;
        position directionPosition(int direction) override;
        position possiblePosition(ground &g);

};

//maj position après move ?

#endif