#ifndef MONSTERATTACKMANAGER_H_INCLUDED
#define MONSTERATTACKMANAGER_H_INCLUDED
#include "attackManager.h"





class monsterAttackManager : public attackManager
{
    public:
      monsterAttackManager();//groundElement *adv);//std::unique_ptr<groundElement> monsterptr);
      double attack(groundElement *elem) override; //std::unique_ptr<groundElement>element) override;
      bool receiveAttack(groundElement *elem,double force) override;

    private:
        
      //std::unique_ptr<groundElement> d_monster;
      
      //groundElement *d_adv;

};


#endif