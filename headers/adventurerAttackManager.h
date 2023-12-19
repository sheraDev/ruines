#ifndef ADVENTURERATTACKMANAGER_H_INCLUDED
#define ADVENTURERATTACKMANAGER_H_INCLUDED
#include "attackManager.h"
#include "ground.h"


class adventurerAttackManager : public attackManager
{
    public :
        adventurerAttackManager(); //groundElement *monster);//std::unique_ptr<groundElement> monsterptr);
        double attack(groundElement *elem) override; //std::unique_ptr<groundElement>element) override;
        bool receiveAttack(groundElement *elem,double force) override;

    private:
        
      //std::unique_ptr<groundElement> d_monster;
      //ground *d_g;
      //groundElement *d_monster;


};

#endif