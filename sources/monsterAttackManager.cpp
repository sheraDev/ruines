#include "monsterAttackManager.h"
#include <iostream>
#include "weapon.h"
#include "attackManager.h"
#include "memory"
#include "adventurer.h"
#include "monster.h"

monsterAttackManager::monsterAttackManager(){}//(groundElement *adv):
//d_adv{adv}{}

// a aucun moment on a besoin de ladv

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
    //std::cout<<"attaque ! \n";
    auto mnstr=dynamic_cast<monster*>(elem);

    double force = mnstr->forcePoints();
    double randomnb = pickRandom();

    if(randomnb > mnstr->getHability())
    {
        force*=0.9;
    }
    return force;
    /*quand un monstre attaque quelqu’un, la
    personne reçoit une attaque du nombre de points de force du monstre multiplié 
    par 0,9 avec une probabilité de 100% -le pourcentage d’habilité du monstre.*/
        
}