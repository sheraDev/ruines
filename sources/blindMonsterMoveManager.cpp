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

blindMonsterMoveManager::blindMonsterMoveManager(const position&pos):movementManager{pos}{}


//UN MONSTRE AVEUGLE SE DEPLACE DANS 8 DIRECTIONS:
/*
1 2 3
4 * 6
7 8 9
*/

position blindMonsterMoveManager::directionPosition(int direction)
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

int blindMonsterMoveManager::directionAleatoire() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> directionsTab = {1, 2, 3, 4, 6, 7, 8, 9};
    std::uniform_int_distribution<> distrib(0, directionsTab.size() - 1);
    int i = distrib(gen);
    int direction= directionsTab[i];

    return direction;
}


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
        position pos{getPos()};
        return pos;
    }
    
    int direction  = directionAleatoire();

    return directionPosition(direction);

}


void blindMonsterMoveManager::move(ground &g, int direction)
{
    position nouvPos{possiblePosition(g)};
   
    
    if((nouvPos.getColumn()<g.getNbColumns() && nouvPos.getColumn()>=0 && nouvPos.getLine()<g.getNbLines()&& nouvPos.getLine()>=0)) 
    {
        position anciennePos{getPos()};
        int indice = g.getIndiceElmt(anciennePos,'B');

        auto monster = dynamic_cast<blindMonster*>(g.getElementsTable()[indice].get());
        int indiceNouv = g.indicePos(nouvPos);  
        
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
            monster->changePosition(nouvPos);

            int indiceAdv = g.getIndiceAdventurer();
            auto adv = dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get()) ;
        
            //LE MONSTRE LANCE UNE ATTAQUE
            monsterAttackManager mnstrAttackManager;//{adv}; //arg inutile
            double force = monster->attack(mnstrAttackManager);

            // L'ADV RECOIT L ATTAQUE
            adventurerAttackManager advAttackManager;//{monster};
            bool mort = adv->receiveAttack(advAttackManager,force);
        }
        //SINON => reste à sa place

            

            
        }
        
}