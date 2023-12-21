#include "blindMonsterMoveManager.h"
#include "blindMonster.h"
#include "ground.h"
#include <cmath>
#include <random>
#include <iostream>
#include "adventurerAttackManager.h"
#include "monsterAttackManager.h"
#include "blindMonsterMoveManager.h"
#include "adventurer.h"

//blindMonsterMoveManager::blindMonsterMoveManager(const position &p):movementManager{p}{}
blindMonsterMoveManager::blindMonsterMoveManager(const position&pos):movementManager{pos}{}








//UN MONSTRE AVEUGLE SE DEPLACE DANS 8 DIRECTIONS:
/*
1 2 3
4 * 6
7 8 9
*/
//ok
position blindMonsterMoveManager::directionPosition(int direction)
{
    position p{};
    switch (direction)
    {

    case 1 : //DIAGONALE HAUT GAUCHE = ligne d en haut colonne de gauche
        p={getPos().getLine()-1,getPos().getColumn()-1};

    case 2 :  // VERS LE HAUT = ligne d'en haut meme colonne
        p = {getPos().getLine()-1,getPos().getColumn()};
        break;

    case 3 : //DIAGONALE HAUT DROITE = ligne d en haut colonne de droite
        p = {getPos().getLine()-1, getPos().getColumn()+1};

    case 4 : // VERS LA GAUCHE = meme ligne colonne de gauche
        p = {getPos().getLine(),getPos().getColumn()-1};
        break;  
    
    case 6 : // VERS LA DROITE = meme ligne colonne de droite
        p = {getPos().getLine(),getPos().getColumn()+1};
        break;

    case 7 : //DIAGONALE BAS GAUCHE = ligne den bas colonne de gauche
        p = {getPos().getLine()+1, getPos().getColumn()-1};
    
    case 8 : // VERS LE BAS = ligne d'en bas meme colonne
        p = {getPos().getLine()+1,getPos().getColumn()};
        break;
    
    case 9 : // DIAGONALE BAS DROITE = ligne den bas colonne de droite
        p= {getPos().getLine()+1, getPos().getColumn()+1};
    
    default:
        break;
    }

    return p;
}

//ok
position blindMonsterMoveManager::possiblePosition(ground &g)
{
    /* SE DEPLACE ALEATOIREMENT DANS UNE DES 9 DIRECTIONS
    1 2 3
    4 * 6
    7 8 9
    */
   position posAdv = g.getAdventurerPosition();

    if((posAdv.getLine()== getPos().getLine() && posAdv.getColumn()==getPos().getColumn()))
    {
        //std::cout<<" dans bm mv manager, je suis sur l'adv! \n";
        position pos{getPos()};
        return pos;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> directionsTab = {1, 2, 3, 4, 6, 7, 8, 9};
    std::uniform_int_distribution<> distrib(0, directionsTab.size() - 1);
    int i = distrib(gen);
    int direction= directionsTab[i];

    //std::cout<<" La direction aleatoire choisie est "<<direction<<"\n";
    return directionPosition(direction);

}

//ok
void blindMonsterMoveManager::move(ground &g, int direction)
{
    position nouvPos{possiblePosition(g)};
    
    
    if((nouvPos.getColumn()<g.getNbColumns() && nouvPos.getColumn()>=0 && nouvPos.getLine()<g.getNbLines()&& nouvPos.getLine()>=0)) 
    {
            

            //if(nbelmt<2) //1 SEULE PERSONNE DANS LA CASE
            //{
                position anciennePos{getPos()};
                //std::cout<<"ancienne pos : "<<getPos().getLine()<<","<<getPos().getColumn()<<"\n";

                int indice = g.getIndiceElmt(anciennePos,'B');
               // std::cout<<"indice du monstre : "<<indice<<"\n";

                auto monster = dynamic_cast<blindMonster*>(g.getElementsTable()[indice].get());
                int indiceNouv = g.indicePos(nouvPos);  //peut etre pb ici
                
                //juste au cas ou
                if(g.nbElmtsPos(nouvPos)==2)
                {
                    std::vector<int> tabIndices = g.getIndicePos(nouvPos);
                    for(int i=0;i<tabIndices.size();i++)
                    {
                        if(tabIndices[i]!=indice)
                        {
                            indiceNouv =tabIndices[i];
                        }
                    }
                }
                
                char t=g.typeOf(indiceNouv);

                if(t=='E') // CASE VIDE => LE MONSTRE Y VA
                {
                    monster->changePosition(nouvPos);
                }
                else if((t=='P' && g.nbElmtsPos(nouvPos)<2 )||(nouvPos.getLine()== getPos().getLine() && nouvPos.getColumn()==getPos().getColumn())) //AVENTURIER => LE MONSTRE y va + L ATTAQUE
                {
                    std::cout<<"dans le bM move manager jv attaquer\n";
                    monster->changePosition(nouvPos);
                    //APPELER LE GESTIONNAIRE D ATTAQUE

                    int indiceAdv = g.getIndiceAdventurer();
                    auto adv = dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get()) ;
                
                    //AFFICHAGES DE DEBUGGAGE
                    //std::cout<<" LANCEMENT DE L ATTAQUE du monstre\n";
                   // std::cout<<"PV ARMURE adv AVANT ATTAQUE : "<< adv->getArmor().getSolidity()<<"\n";
                    //std::cout<<"PV ADVENTURER AVANR ATTAQUE : "<<adv->lifePoints()<<"\n";


                    //LE MONSTRE LANCE UNE ATTAQUE
                    monsterAttackManager mnstrAttackManager;//{adv}; //arg inutile
                    double force = monster->attack(mnstrAttackManager);

                    // L'ADV RECOIT L ATTAQUE
                    adventurerAttackManager advAttackManager;//{monster};
                    bool mort = adv->receiveAttack(advAttackManager,force);

                    //std::cout<<"c bon jai attaque ladv et il a recu \n";

                    /*if(mort) //Si l'aventurier succombe à l'attaque
                    {
                       // g.removeElement(g.getIndiceAdventurer());
                        //Fin partie
                    }*/



                    //AFFICHAGES DE DEBUGGAGE
                   /* std::cout<<" APRES  L ATTAQUE par le bm \n";
                        if(!mort){
                            std::cout<<"PV ARMURE adv après ATTAQUE : "<< adv->getArmor().getSolidity()<<"\n";
                            std::cout<<"PV ADVENTURER apres ATTAQUE : "<<adv->lifePoints()<<"\n";
                            std::cout<<"PF DE L ATTAQUE : "<<force<<"\n";}
                        else
                        {
                            std::cout<<"L'adv est mort \n";
                        }*/



                }
                //SINON => amulet ou autre monstre ou mur=> reste à sa place

            //}

            
        }
        /*else{
            std::cout<<"le monstre ne peut pas bouger \n";
            }*/
        //SINON = position en dehors du terrain=> le monstre reste à sa place
}