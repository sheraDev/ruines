#ifndef EMOTVIEW_H_INCLUDED
#define EMOTVIEW_H_INCLUDED
#include <iostream>
#include "viewManager.h"


class emotView : public viewManager
{
    public:
        emotView();
        void displayAdventurer(const adventurer &adv) const override;
        void displayGround(const ground &g) const override;
        void displayWall(const wall &w) const override;
        void displayAmulet(const amulet &a) const override;
        void displayMonster(const monster &m) const override;
        void displayDoor(const door &d) const override;
        void displayOutside(const outside &o) const override;
        void displayMoney(const money &m) const override;


};



#endif