#ifndef BLINDMONSTER_H_INCLUDED
#define BLINDMONSTER_H_INCLUDED
#include "monster.h"

class blindMonster : public monster
{
    public:
        blindMonster(const position & pos);
        void moveAt(const position & pos) override;
};


#endif