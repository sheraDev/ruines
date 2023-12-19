#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED
#include "character.h"
#include "groundElement.h"
//#include "viewManager.h"
class viewManager;
class adventurer;
class ground;

class monster : public character
{
    public:
        virtual ~monster()=default;
        monster(const position &pos, double hability=0.8);
        //void attack() override;
       // double attack(attackManager &attackManag) override;
       // bool receiveAttack(attackManager &attackManag,double force) override;
        void display(const viewManager& view) const override;
        double getHability() const;
        bool isAtOneCaseAdv(ground &g);
    private:
        double d_hability;
   
};

#endif