#ifndef ADVENTURER_H_INCLUDED
#define ADVENTURER_H_INCLUDED
#include "character.h"
#include "sword.h"
#include "armory.h"
//#include "viewManager.h"
class viewManager;

class adventurer : public character
{
    public:
        adventurer(const position & pos);
        void attack() override;
        void receiveAttack() override;
        void moveAt(const position &pos);
        bool hasAmulet() const;
        void display(const viewManager& view) const override;
        void setAmuletTrue(bool haveAmulet);
    private:
        sword d_sword;
        armory d_armor;
        bool d_hasAmulet;


};
//testcommit

#endif