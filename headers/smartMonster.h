#ifndef SMARTMONSTER_H_INCLUDED
#define SMARTMONSTER_H_INCLUDED
#include "monster.h"

class smartMonster : public monster
{
    public:
        smartMonster(const position& pos);
        void moveAt(const position &pos) override;

};




#endif