#ifndef ADVENTURERATTACKMANAGER_H_INCLUDED
#define ADVENTURERATTACKMANAGER_H_INCLUDED
#include "attackManager.h"
#include "ground.h"


class adventurerAttackManager : public attackManager
{
    public :
        adventurerAttackManager(); 
        double attack(groundElement *elem) override; 
        bool receiveAttack(groundElement *elem,double force) override;

};

#endif