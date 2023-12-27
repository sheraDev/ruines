#include "adventurerMoveManager.h"
#include "adventurerAttackManager.h"
#include "monsterAttackManager.h"
#include "ground.h"
#include "adventurer.h"
#include "monster.h"
#include "money.h"
#include <iostream>
#include <memory>



adventurerMoveManager::adventurerMoveManager(const position&pos):movementManager{pos}{}

//nouvelle position après deplacement
position adventurerMoveManager::directionPosition(int direction)
{
    position p{};
    switch (direction)
    {

    case 1 : //DIAGONALE HAUT GAUCHE = ligne d en haut colonne de gauche
        p={getPos().getLine()-1,getPos().getColumn()-1};
        break;

    case 2 :  // VERS LE HAUT = ligne d'en haut meme colonne
        p = {getPos().getLine()-1,getPos().getColumn()};
        break;

    case 3 : //DIAGONALE HAUT DROITE = ligne d en haut colonne de droite
        p = {getPos().getLine()-1, getPos().getColumn()+1};
        break;

    case 4 : // VERS LA GAUCHE = meme ligne colonne de gauche
        p = {getPos().getLine(),getPos().getColumn()-1};
        break;  
    
    case 5 : //RESTER SUR PLACE
        p = {getPos()};
        break;

    case 6 : // VERS LA DROITE = meme ligne colonne de droite
        p = {getPos().getLine(),getPos().getColumn()+1};
        break;

    case 7 : //DIAGONALE BAS GAUCHE = ligne den bas colonne de gauche
        p = {getPos().getLine()+1, getPos().getColumn()-1};
        break;
    
    case 8 : // VERS LE BAS = ligne d'en bas meme colonne
        p = {getPos().getLine()+1,getPos().getColumn()};
        break;
    
    case 9 : // DIAGONALE BAS DROITE = ligne den bas colonne de droite
        p= {getPos().getLine()+1, getPos().getColumn()+1};
        break;
    
    default:
        break;
    }

    return p;
}



void adventurerMoveManager::move(ground&g,int direction)
{  
    position nouvPos{directionPosition(direction)};


    int indiceAdv{g.getIndiceAdventurer()};
    char type;
    auto adv=dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get());

    if(nouvPos.getColumn()<g.getNbColumns()&& nouvPos.getColumn()>=0 && nouvPos.getLine()<g.getNbLines() && nouvPos.getLine()>=0)
    {   
        int indice = g.indicePos(nouvPos);

        type=g.typeOf(indice);  
        
        //SI il ya 2 elmts : forcément l'adv + le monstre 
        if(g.nbElmtsPos(nouvPos)==2)
        {
           std::vector<int> tabElmt = g.getIndicePos(nouvPos);
           for(int i=0; i<tabElmt.size();i++)
           {
                if(g.typeOf(tabElmt[i])!='P')
                {
                    type = g.typeOf(tabElmt[i]);
                }
           }
        }

        
        if(type=='E') //vide => laventurier y va
        {
            adv->changePosition(nouvPos);
        }
        else if(type=='S' || type=='B') //MONSTRE => L'AVENTURIER y va + L ATTAQUE
        {
            adv->changePosition(nouvPos);
            int indiceMonstre = g.getIndiceElmt(nouvPos,type);
            auto monstreptr =  dynamic_cast<monster*>(g.getElementsTable()[indiceMonstre].get());
       
            adventurerAttackManager advAttackManager;
            double force = adv->attack(advAttackManager);

            //LE MONSTRE RECOIT UNE ATTAQUE
            monsterAttackManager mnstrAttackManager;
            bool mort=monstreptr->receiveAttack(mnstrAttackManager,force);

            if(mort) //SI LE MONSTRE SUCCOMBE A L ATTAQUE
            {
                //LAVENTURIER RECUPERE LES PF DU MONSTRE
                double pfmonstre = monstreptr->forcePoints();
                double quart = 0.25 * pfmonstre;
                double reste = pfmonstre - quart;

                adv->setForcePoints(adv->forcePoints()+quart);
                adv->setLifePoints(adv->lifePoints()+reste);

                g.removeElement(indiceMonstre);
            }
        }
        else if(type=='A') //AMULETTE :il y va il la ramasse
        {
           g.removeElement(indice); //supprimer lamulette de la case
           adv->changePosition(nouvPos);
           adv->setAmuletTrue();
 
        }
        else if(type=='D') //case de sortie
        {
            if(adv->hasAmulet())
            { 
                adv->setIsOutTrue();
            }
                
        }
        else if(type=='M') //tas de pièces
        {
            int indiceMoney = g.getIndiceElmt(nouvPos,type);
            auto moneyPtr =  dynamic_cast<money*>(g.getElementsTable()[indiceMoney].get());

            int val = moneyPtr->getValue();

           g.removeElement(indice); //supprimer le tas de pièces de la case
           adv->changePosition(nouvPos);
           adv->addToBourse(val);            

        }
   
    }


}