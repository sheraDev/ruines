#ifndef SMARTMONSTER_H_INCLUDED
#define SMARTMONSTER_H_INCLUDED
#include "monster.h"

class smartMonster : public monster
{
    public:
        smartMonster(const position& pos,int pf=100,int pv=700,double hability=0.7);

};




#endif