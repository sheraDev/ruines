#include "monsterAttackManager.h"
#include <iostream>
#include "weapon.h"
#include "attackManager.h"
#include "memory"
#include "adventurer.h"
#include "monster.h"

monsterAttackManager::monsterAttackManager(){}


bool monsterAttackManager::receiveAttack(groundElement *elem,double force)
{
    auto mnstr=dynamic_cast<monster*>(elem);
    double pvmonstre = mnstr->lifePoints();

    if(force > pvmonstre)
    {
        return true;        
    }
    else{
        mnstr->setLifePoints(pvmonstre - force);
        return false;
    }
}

double monsterAttackManager::attack(groundElement *elem) 
{
    auto mnstr=dynamic_cast<monster*>(elem);

    double force = mnstr->forcePoints();
    double randomnb = pickRandom();

    if(randomnb > mnstr->getHability())
    {
        force*=0.9;
    }
    return force;
    
        
}