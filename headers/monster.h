#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED
#include "character.h"
#include "groundElement.h"
//#include "viewManager.h"
class viewManager;

class monster : public character
{
    public:
        virtual ~monster()=default;
        monster(const position &pos);
        void attack() override;
        void receiveAttack() override;
        void display(const viewManager& view) const override;
        double getHability() const;
    private:
        double d_hability;
   
};

#endif