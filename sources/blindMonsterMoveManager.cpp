#include "blindMonsterMoveManager.h"
#include "ground.h"
#include <cmath>
#include <random>
#include <iostream>
blindMonsterMoveManager::blindMonsterMoveManager(const position &p):movementManager{p}{}

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


position blindMonsterMoveManager::possiblePosition(ground &g)
{
    /* SE DEPLACE ALEATOIREMENT DANS UNE DES 9 DIRECTIONS
    1 2 3
    4 * 6
    7 8 9
    */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> directionsTab = {1, 2, 3, 4, 6, 7, 8, 9};
    std::uniform_int_distribution<> distrib(0, directionsTab.size() - 1);
    int i = distrib(gen);
    int direction= directionsTab[i];

    return directionPosition(direction);

}

void blindMonsterMoveManager::move(ground &g)
{
    position p{possiblePosition(g)};

    if((p.getColumn()<g.getNbColumns() && p.getLine()<g.getNbLines())) 
        {
            char t=g.typeOf(p);

            if(t=='E') // CASE VIDE => LE MONSTRE Y VA
            {
                g.putElement(p,getPos());
            }
            else if(t=='P') //AVENTURIER => LE MONSTRE L ATTAQUE
            {
                //APPELER LE GESTIONNAIRE D ATTAQUE
            }
            //SINON => amulet ou autre monstre ou mur=> reste à sa place

        }
        //SINON = position en dehors du terrain=> le monstre reste à sa place
}