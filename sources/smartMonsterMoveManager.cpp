#include "smartMonsterMoveManager.h"
#include "ground.h"
#include "smartMonster.h"
#include <cmath>
#include <random>
#include <iostream>
#include "attackManager.h" 
#include "monsterAttackManager.h"
#include "adventurer.h"
#include "adventurerAttackManager.h"
smartMonsterMoveManager::smartMonsterMoveManager(const position& p):movementManager{p}{}


//UN MONSTRE INTELLIGENT SE DEPLACE DANS 4 DIRECTIONS: 2 4 6 ou 8
/*
  2 
4 $ 6
  8 
*/


position smartMonsterMoveManager::directionPosition(int direction)
{
    position p{};
    switch (direction)
    {
    case 2:  // VERS LE HAUT = ligne d'en haut meme colonne
        p = {getPos().getLine()-1,getPos().getColumn()};
        break;
    case 8: // VERS LE BAS = ligne d'en bas meme colonne
        p = {getPos().getLine()+1,getPos().getColumn()};
        break;
    case 4: // VERS LA GAUCHE = meme ligne colonne de gauche
        p = {getPos().getLine(),getPos().getColumn()-1};
        break;
    case 6: // VERS LA DROITE = meme ligne colonne de droite
        p = {getPos().getLine(),getPos().getColumn()+1};
        break;
    default:
        break;
    }

    return p;
}

//VRAI SI LE MONSTRE EST A - DE 8 CASES DE L AVENTURIER
bool smartMonsterMoveManager::isNearAdventurer(ground &g) const
{   
    int lineAdv = g.getAdventurerPosition().getLine();
    int colAdv = g.getAdventurerPosition().getColumn();
    int lineMonster = getPos().getLine();
    int colMonster = getPos().getColumn();

    int difLine=std::abs(lineMonster-lineAdv);
    int difCol =std::abs(colMonster-colAdv);
   
    return difLine<8 && difCol<8;
}





int smartMonsterMoveManager::choixDirection(int d1,int d2,const ground &g) 
{
   int direction;

   position p1{directionPosition(d1)};
   position p2{directionPosition(d2)};

   int nbElem1 = g.nbElmtsPos(p1);
   int nbElem2 = g.nbElmtsPos(p2);

    if(nbElem1>1) //plus qu'une personne en d1 => il ny va pas
    {
        direction = d2;
    }
    else if(nbElem2>1) //plus qu'une personne en d2 => il ny va pas
    {
        direction = d1;
    }
    else if(nbElem1<2 && nbElem2<2) // => choix en fonction du type
    {
        int i1=g.indicePos(p1); 
        int i2=g.indicePos(p2);

        char t1=g.typeOf(i1); 
        char t2=g.typeOf(i2);

        if(t1=='W'|| t1=='B' ||t1=='S')  //1 ERE POS PAS LIBRE
        {    
            direction = d2;
        }
        else //1 ERE POS LIBRE
        {
            direction = d1;
        }
    }
  
    return direction;
}



position smartMonsterMoveManager::possiblePosition(ground&g) 
{
    //ON CHERCHE DANS QUELLE DIRECTION LE MONSTRE DOIT ALLER PR ALLER VERS AVENTURIER

    int lineAdv = g.getAdventurerPosition().getLine();
    int colAdv = g.getAdventurerPosition().getColumn();
    int lineMonster = getPos().getLine();
    int colMonster = getPos().getColumn();
    position pos{};

    /*
      2 
    4 $ 6
      8 
    */
  
    //Le monstre est sur l'adv
    if(lineAdv==lineMonster && colMonster==colAdv)
    {
        pos ={getPos().getLine(),getPos().getColumn()};
        return pos;
    }
    

    if(lineMonster>lineAdv) // LE MONSTRE EST AU DESSUS DE LAVENTURIER
    {
        if(colMonster<colAdv)  //AU DESSUS A GAUCHE : aller en 2 ou 6
        {
           int direction = choixDirection(2,6,g);
           pos = directionPosition(direction);
        }
        else if(colMonster>colAdv)  //AU DESSUS A DROITE : aller en 4 ou 2
        {
           int direction = choixDirection(4,2,g);
           pos = directionPosition(direction);
           
        }
        else{ // AU DESSUS SUR LA MEME COLONNE 1 DIRECTIONS POSSIBLE : 2
            position ps = directionPosition(2);
            if(g.nbElmtsPos(ps)<2) //pas de bataille en cours sur la case
            {
                pos = ps;
            }
            else{
                pos={-1,-1};
            }

        }
    }
    else if(lineMonster<lineAdv) // LE MONSTRE EST EN DESSOUS DE LAVENTURIER
    {
        if(colMonster<colAdv) // EN DESSOUS A GAUCHE: aller en 8 ou 6
        {
            int direction = choixDirection(8,6,g);
            pos = directionPosition(direction);
        }
        else if(colMonster>colAdv) // EN DESSOUS A DROITE: 8 ou 4
        {
           int direction = choixDirection(8,4,g);
           pos = directionPosition(direction);
         
        }
        else{ // EN DESSOUS SUR LA MEME COLONNE 1 DIRECTION POSSIBLE : 8
        
            position ps = directionPosition(8);
            if(g.nbElmtsPos(ps)<2) //pas de bataille en cours sur la case
            {
                pos = ps;
            }
            else{
                pos={-1,-1};
            } 
        }
    }
    else if (lineMonster==lineAdv) // LE MONSTRE EST SUR LA MEME LIGNE 
    {
        if(colMonster<colAdv){ // A GAUCHE : 1 DIRECTION POSSIBLE : 6 
            position ps = directionPosition(6);
            if(g.nbElmtsPos(ps)<2) //pas de bataille en cours sur la case
            {
                pos = ps;
            }
            else{
                pos={-1,-1};
            } 
        }
        else{ // A DROITE : 1 DIRECTION POSSIBLE : 4 

            position ps = directionPosition(4);
            if(g.nbElmtsPos(ps)<2) //pas de bataille en cours sur la case
            {
                pos = ps;
            }
            else{
                pos={-1,-1};
            } 
        }
    }
    else if(colMonster==colAdv) // LE MONSTRE EST SUR LA MEME COLONNE
    {
        if(lineMonster>lineAdv){ // AU DESSUS 1 DIRECTION POSSIBLE : 2 
        
            position ps = directionPosition(2);
            if(g.nbElmtsPos(ps)<2) //pas de bataille en cours sur la case
            {
                pos = ps;
            }
            else{
                pos={-1,-1};
            } 
        }
        else{ // EN DESSOUS: 1 DIRECTION POSSIBLE : 8
        
            position ps = directionPosition(8);
            if(g.nbElmtsPos(ps)<2) //pas de bataille en cours sur la case
            {
                pos = ps;
            }
            else{
                pos={-1,-1};
            } 
        }
    }

    return pos;
}


position smartMonsterMoveManager::aleatoirePosition() //ground &g)
{
    /* 
      2 
    4 $ 6
      8 
    */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> directionsTab = {2, 4, 6, 8};
    std::uniform_int_distribution<> distrib(0, directionsTab.size() - 1);
    int i = distrib(gen);
    
    int directionAleat = directionsTab[i];
    return directionPosition(directionAleat);
}




void smartMonsterMoveManager::move(ground &g,int direction)
{
    
    if(isNearAdventurer(g)) // SI MONSTRE = -8 CASES AVENTURIER
    {
        position p{possiblePosition(g)};

        if(p.getColumn()!=-1 && p.getLine()!=-1 && p.getColumn()<g.getNbColumns() && p.getLine()<g.getNbLines()) 
        {   
            int indiceMonstre = g.getIndiceElmt(getPos(),'S');
            int indice = g.indicePos(p);   

            if(g.nbElmtsPos(p)==2)
            {
                std::vector<int> tabIndices = g.getIndicePos(p);
                for(int i=0;i<tabIndices.size();i++)
                {
                    if(tabIndices[i]!=indiceMonstre)
                    {
                        indice =tabIndices[i];
                    }
                }
            }
            
            
            char t = g.typeOf(indice);
            auto monster = dynamic_cast<smartMonster*>(g.getElementsTable()[indiceMonstre].get());
        

            if(t=='E') //case vide
            {
                monster->changePosition(p);
            }  
            else if((t=='P' &&g.nbElmtsPos(p)<2 )||( p.getLine()== getPos().getLine() && p.getColumn()==getPos().getColumn()))
            {   
                int indiceAdv = g.getIndiceAdventurer();

                monster->changePosition(p);
                auto adv = dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get()) ;
                

                //LE MONSTRE LANCE UNE ATTAQUE
                monsterAttackManager mnstrAttackManager;

                double force = monster->attack(mnstrAttackManager);

                // L'ADV RECOIT L ATTAQUE
                adventurerAttackManager advAttackManager;
                bool mort = adv->receiveAttack(advAttackManager,force);

                
            }
        }
    }
    else{ //LE MONSTRE = + DE 8 CASES = déplacement aléatoire


        position p{aleatoirePosition()};
        int nbElm= g.nbElmtsPos(p); 
        
        if(nbElm<2 && p.getColumn()<g.getNbColumns()&& p.getColumn()>=0 && p.getLine()<g.getNbLines() && p.getLine()>=0) 
        {

            int indice = g.indicePos(p); 
            char t = g.typeOf(indice);

            int indiceMonstre = g.getIndiceElmt(getPos(),'S');
            auto monster = g.getElementsTable()[indiceMonstre].get(); 

            

            if(t=='E') // CASE VIDE => LE MONSTRE Y VA
            {
                monster->changePosition(p);
            }
            
        }
        
        

    }
    

}


