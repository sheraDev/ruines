#ifndef SMARTMONSTERMOVEMANAGER_H_INCLUDED
#define SMARTMONSTERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;

class smartMonsterMoveManager : public movementManager
{
    public:
        smartMonsterMoveManager(const position& p);
        void move(ground &g, int direction=0)override;

        position directionPosition(int direction) override;
        position possiblePosition(ground &g) ;
        position aleatoirePosition();
        int choixDirection(int d1,int d2,const ground &g) ;

        bool isNearAdventurer(ground &g) const;

};



#endif