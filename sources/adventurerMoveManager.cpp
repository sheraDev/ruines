#include "adventurerMoveManager.h"
#include "ground.h"
#include "adventurer.h"
#include <iostream>


adventurerMoveManager::adventurerMoveManager(const position& p, int direction):movementManager{p,direction}{}


position adventurerMoveManager::directionPosition(int direction)
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
    
    case 5 : //RESTER SUR PLACE
        p = {getPos()};
    
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


void adventurerMoveManager::move(ground &g)
{
    position p{directionPosition(getDirection())};

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


}