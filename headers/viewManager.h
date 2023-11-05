#ifndef VIEWMANAGER_H_INCLUDED
#define VIEWMANAGER_H_INCLUDED
/*#include "monster.h"
#include "wall.h"
#include "adventurer.h"
#include "ground.h"
#include "amulet.h"*/

class monster;
class wall;
class adventurer;
class ground;
class amulet;

//GESTIONNAIRE D AFFICHAGE DES DIFFERENTS ELEMENTS PRESENTS SUR LE TERRAIN


class viewManager
{
    public:
        virtual ~viewManager() = default;
        virtual void displayAdventurer(const adventurer &adv) const = 0;
        virtual void displayGround(const ground &g) const = 0;
        virtual void displayWall(const wall &w) const = 0;
        virtual void displayAmulet(const amulet &a) const = 0;
        virtual void displayMonster(const monster &m) const = 0;


};


#endif