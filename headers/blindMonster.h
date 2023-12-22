#ifndef BLINDMONSTER_H_INCLUDED
#define BLINDMONSTER_H_INCLUDED
#include "monster.h"

class blindMonster : public monster
{
    public:
        blindMonster(const position & pos,int pf=100,int pv=700,double hability=0.6);
};


#endif