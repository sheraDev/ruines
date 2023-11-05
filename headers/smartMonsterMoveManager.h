#ifndef SMARTMONSTERMOVEMANAGER_H_INCLUDED
#define SMARTMONSTERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;

class smartMonsterMoveManager : public movementManager
{
    public:
        smartMonsterMoveManager(const position& p);
        void move(ground &g) override;
        position directionPosition(int direction) override;
        position possiblePosition(ground &g) ;
        position aleatoirePosition(ground &g);

        bool isNearAdventurer(ground &g) const;

};

//maj d_position après un move ??


#endif