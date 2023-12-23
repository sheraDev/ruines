#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED
#include "character.h"
#include "groundElement.h"
class viewManager;
class adventurer;
class ground;

class monster : public character
{
    public:
        virtual ~monster()=default;
        monster(const position &pos,int pf,int pv, double hability=0.8);
        void display(const viewManager& view) const override;
        double getHability() const;
        bool isAtOneCaseAdv(ground &g);
    private:
        double d_hability;
   
};

#endif