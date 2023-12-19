#ifndef MONSTERATTACKMANAGER_H_INCLUDED
#define MONSTERATTACKMANAGER_H_INCLUDED
#include "attackManager.h"





class monsterAttackManager : public attackManager
{
    public:
      monsterAttackManager();
      double attack(groundElement *elem) override; 
      bool receiveAttack(groundElement *elem,double force) override;


};


#endif