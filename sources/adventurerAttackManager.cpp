#include <iostream>
#include "adventurerAttackManager.h"
#include "ground.h"
#include "adventurer.h"
#include "monster.h"
#include "weapon.h"
#include "attackManager.h"
#include "memory"

adventurerAttackManager::adventurerAttackManager(){}


double adventurerAttackManager::attack(groundElement *elem)
{   
    //std::cout<<"attaque ! \n";
    
    auto adv=dynamic_cast<adventurer*>(elem);
   
    sword s = adv->getSword();
    double swordSolidity = s.getSolidity();
    double force;


    if(swordSolidity<=0)
    {
        force =0;
       // std::cout<<"mince alors jveux attaquer mais jai plus de force dans lepee! \n";
    }
    else
    {
       // std::cout<<"c carré jv attaquer et lepee est ok \n";
        force =adv->forcePoints() + swordSolidity;
        double randomnb = pickRandom();

        if(randomnb>0.8)
        {
            force *= 0.9;
        }

        adv->setSwordSolidity(swordSolidity-1);
    }

    return force;
}


bool adventurerAttackManager::receiveAttack(groundElement *elem,double force)
{

   // std::cout<<" je suis l'adv je Recoit attaque ! \n";

    auto adv=dynamic_cast<adventurer*>(elem);
    double reste;
    bool mort = false;
    double pfAbsorbesArmure = 0.75 * force;
    double armorSolidity = adv->getArmor().getSolidity();
    
    if(armorSolidity > (0.5)*pfAbsorbesArmure) //amure peut abs 3/4 pf
    {

        double nouvsol = armorSolidity - (0.5)*pfAbsorbesArmure;

        //std::cout<<"je peux absj, je dois mtnt avoir ;"<<armorSolidity<<"-"<<(0.5)*pfAbsorbesArmure<<"="<<nouvsol<<"\n";


        adv->setArmorSolidity(nouvsol);
       // std::cout<<"après abs, jai : "<<adv->getArmor().getSolidity()<<"\n";
        reste = 0.25*force;
       
    }
    else
    {
       // std::cout<<"je peux pas abs \n";
        adv->setArmorSolidity(0);
        reste =  force - (2*armorSolidity);
    }

    if(reste >= adv->lifePoints())
    {
        adv->setLifePoints(0);
        mort = true;
       // std::cout<<"mince alors je suis mort (adv)\n";
    }
    else
    {   double lp = adv->lifePoints();
        adv->setLifePoints(lp - reste);
       // std::cout<<"jai perdu des pv!! \n";
    }

    return mort;
}