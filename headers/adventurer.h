#ifndef ADVENTURER_H_INCLUDED
#define ADVENTURER_H_INCLUDED
#include "character.h"
#include "sword.h"
#include "armory.h"
class viewManager;

class adventurer : public character
{
    public:
        adventurer(const position & pos,int pf=200,int pv=1000,double swordSolidity=100.0,double armorySolidity=100.0,bool hasAmulet=false,bool isOut=false, int bourse=0);
     
        bool hasAmulet() const;
        void setAmuletTrue();
        bool isOutWithAmulet() const ;
        sword getSword() const;
        armory getArmor() const;
        void display(const viewManager& view) const override;
        void setSwordSolidity(double sol);
        void setArmorSolidity(double sol);
       
        void addToArmorSolidity(double f);
        void addToSwordSolidity(double f);

       
        void setIsOutTrue();

        int getBourse() const;
        void addToBourse(int amount);
        void removeFromBourse(int amount);
        void setBourse(int val) ;

    private:
        sword d_sword;
        armory d_armor;
        bool d_hasAmulet;
        bool d_isOut;
        int d_bourse;


};
//testcommit

#endif