#include "adventurerMoveManager.h"
#include "adventurerAttackManager.h"
#include "monsterAttackManager.h"
#include "ground.h"
#include "adventurer.h"
#include "monster.h"
#include "money.h"
#include <iostream>
#include <memory>



//adventurerMoveManager::adventurerMoveManager(const position& p, int direction):movementManager{p,direction}{}
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



//UPDATE
//bouger l'aventurier= juste changer sa position SI C POSSIBLE
//s Il reste la ou il est dans le 
//ground qui est un tab1D

void adventurerMoveManager::move(ground&g,int direction)//(ground &g)
{  
    position nouvPos{directionPosition(direction)};//getDirection())};


    int indiceAdv{g.getIndiceAdventurer()};
    char type;

    //std::vector<std::unique_ptr<groundElement>> tabElmt{g.getElementsTable()};

    auto adv=dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get());

    //std::cout<<" nouv pos de l'adv dans son mover = "<<nouvPos.getColumn()<<";"<<nouvPos.getLine()<<std::endl;

    if(nouvPos.getColumn()<g.getNbColumns()&& nouvPos.getColumn()>=0 && nouvPos.getLine()<g.getNbLines() && nouvPos.getLine()>=0)
    {   
        int indice = g.indicePos(nouvPos);

        type=g.typeOf(indice);  //TYPE DE LA CASE OU ON VEUT ALLER
        
        //SI il ya 2 elmts : forcément l'adv + le monstre 
        if(g.nbElmtsPos(nouvPos)==2)
        {
            //std::cout<<"adv, forcage du type \n";
           std::vector<int> tabElmt = g.getIndicePos(nouvPos);
           for(int i=0; i<tabElmt.size();i++)
           {
           // std::cout<<"le type n"<<i<<" de la position "<<nouvPos.getLine()<<","<<nouvPos.getColumn()<<" est : "<< g.typeOf(tabElmt[i])<<"\n";
                if(g.typeOf(tabElmt[i])!='P')
                {
                    type = g.typeOf(tabElmt[i]);
                }
           }
        }

        //std::cout<<"adv je me prepare a bouger . je sais que le type ou jv est : "<<type<<"\n";

        
        if(type=='E') //vide => laventurier y va
        {
            adv->changePosition(nouvPos);
        }
        else if(type=='S' || type=='B') //MONSTRE => L'AVENTURIER y va + L ATTAQUE
        {
            adv->changePosition(nouvPos);
            int indiceMonstre = g.getIndiceElmt(nouvPos,type);
            //std::cout<<"L'indice du monstre que jattaque est : "<<indiceMonstre<<"\n";

            auto monstreptr =  dynamic_cast<monster*>(g.getElementsTable()[indiceMonstre].get());
            
          // std::cout<<" ATTAQUE LANCEE par ladv DEPUIS LE MOVE MANAGER \n";
          // std::cout<<" Adventurer : \n solidite de lepee avant attaque = "<<adv->getSword().getSolidity()<<std::endl;
           //std::cout<<" Monster : \n Pv avant l'attaque = "<<monstreptr->lifePoints()<<std::endl;
/*
            if(!monstreptr)
            {
                std::cout<<" le monstre n'existe plus \n";
            }
            else{
                std::cout<<"Le monstre existe tjr \n";
            }*/
            //L AVENTURIER LANCE UNE ATTAQUE
            adventurerAttackManager advAttackManager;//{monstreptr};
            double force = adv->attack(advAttackManager);

            //LE MONSTRE RECOIT UNE ATTAQUE
            monsterAttackManager mnstrAttackManager;//{adv};
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

            //AFFICHAGE PR VERIF
          //  std::cout<<" FIN DE L ATTAQUE \n";
          //  std::cout<<" Adventurer : \n solidite de lepee apres attaque = "<<adv->getSword().getSolidity()<<std::endl;
           /*if(!mort){
            std::cout<<" Monster : \n Pv après l'attaque = "<<monstreptr->lifePoints()<<std::endl;
           }else{
            std::cout<<"Le monstre est mort \n";
           }*/
        }
        else if(type=='A') //AMULETTE :il y va il la ramasse
        {
           g.removeElement(indice); //suppr lamulette de la case
           adv->changePosition(nouvPos);
           adv->setAmuletTrue();
 
        }
        else if(type=='D') //case de sortie
        {
            //std::cout<<" je tente de sortir ! \n";
            if(adv->hasAmulet())
            { 
                //std::cout<<"j'ai l'amulet ! \n";
                adv->setIsOutTrue();
            }
                
        }
        else if(type=='M') //argent
        {
            int indiceMoney = g.getIndiceElmt(nouvPos,type);
            auto moneyPtr =  dynamic_cast<money*>(g.getElementsTable()[indiceMoney].get());

            int val = moneyPtr->getValue();

            //AFFICHAGE DE TEST
            //std::cout<<"La valeur du tas de pieces est "<<val;
    
           g.removeElement(indice); //suppr lamulette de la case
           adv->changePosition(nouvPos);
           adv->addToBourse(val);            

        }
   
    }


    
    /*
    if((p.getColumn()<g.getNbColumns() && p.getLine()<g.getNbLines())) 
        {
            char t=g.typeOf(p);

            if(t=='E') // CASE VIDE => L AVENTURIER Y VA
            {
                g.putElement(p,getPos());
            }
            else if(t=='S' || t=='B') //MONSTRE => L'AVENTURIER L ATTAQUE
            {
                //APPELER LE GESTIONNAIRE D ATTAQUE
            }
            else if(t=='A') //AMULETTE : il la ramasse
            {
                g.removeElement(p); //suppr lamulette de la case
                g.putElement(p,getPos());

                // mettre lamulette a true sur laventurier
                position posAv {g.getAdventurerPosition()};
                auto p=dynamic_cast<adventurer*>(g.getElementsTable()[posAv.getLine()][posAv.getColumn()].get());
                p->setAmuletTrue(true);

            }
            //SINON => mur=> reste à sa place

        }
        //SINON = position en dehors du terrain=> le joueur reste à sa place
*/

}