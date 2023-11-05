#include "smartMonsterMoveManager.h"
#include "ground.h"
#include <cmath>
#include <random>

smartMonsterMoveManager::smartMonsterMoveManager(const position& p):movementManager{p}{}
        


//UN MONSTRE INTELLIGENT SE DEPLACE DANS 4 DIRECTIONS: 2 4 6 ou 8
/*
  2 
4 $ 6
  8 
*/

//RETURN LA NOUVELLE POSITION SELON LA DIRECTION
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


//FONCTION UTILISEE SI L AVENTURIER EST A MOINS DE 8 CASES 
//POUR SAVOIR OU IL DOIT SE DEPLACER
position smartMonsterMoveManager::possiblePosition(ground&g) 
{
    //ON CHERCHE DANS QUELLE DIRECTION LE MONSTRE DOIT ALLER PR ALLER VERS AVENTURIER

    int lineAdv = g.getAdventurerPosition().getLine();
    int colAdv = g.getAdventurerPosition().getColumn();
    int lineMonster = getPos().getLine();
    int colMonster = getPos().getColumn();
    std::vector<position>tPos;
    tPos.reserve(2);
    position pos{};
    position p1{}, p2{};

    /* 
      2 
    4 $ 6
      8 
    */

    if(lineMonster>lineAdv) // LE MONSTRE EST AU DESSUS DE LAVENTURIER
    {
        if(colMonster<colAdv){  //AU DESSUS A GAUCHE
        
            p1=directionPosition(2);
            p2=directionPosition(6);
            char t=g.typeOf(p1);

            if(t=='W'|| t=='B' ||t=='S') // SI LA 1ERE POS NEST PAS LIBRE ON PREND LA 2EME
            {                    
                pos = p2;
            }
            else pos=p1;


        }
        else if(colMonster>colAdv){  //AU DESSUS A DROITE
        // 2 DIRECTIONS POSSIBLES : 4 OU 2
    
            p1=directionPosition(4);
            p2=directionPosition(2);
            char t=g.typeOf(p1);

            if(t=='W'|| t=='B' ||t=='S') // SI LA 1ERE POS NEST PAS LIBRE ON PREND LA 2EME
            {                    
                pos = p2;
            }
            else pos=p1;

        }
        else{ // AU DESSUS SUR LA MEME COLONNE
            // 1 DIRECTIONS POSSIBLE : 2
            pos=directionPosition(2);

        }
    }
    else if(lineMonster<lineAdv) // LE MONSTRE EST EN DESSOUS DE LAVENTURIER
    {
        if(colMonster<colAdv){ // EN DESSOUS A GAUCHE
            // 2 DIRECTIONS POSSIBLES : 8 ou 6
            p1=directionPosition(8);
            p2=directionPosition(6);

            char t=g.typeOf(p1);

            if(t=='W'|| t=='B' ||t=='S') // SI LA 1ERE POS NEST PAS LIBRE ON PREND LA 2EME
            {                    
                pos = p2;
            }
            else pos=p1;


        }
        else if(colMonster>colAdv){ // EN DESSOUS A DROITE
            // 2 DIRECTIONS POSSIBLES : 8 ou 4
        
            p1=directionPosition(8);
            p2=directionPosition(4);

            char t=g.typeOf(p1);

            if(t=='W'|| t=='B' ||t=='S') // SI LA 1ERE POS NEST PAS LIBRE ON PREND LA 2EME
            {                    
                pos = p2;
            }
            else pos=p1;
        }
        else{ // EN DESSOUS SUR LA MEME COLONNE
            // 1 DIRECTION POSSIBLE : 8
            pos=directionPosition(8);

        }
    }
    else if (lineMonster==lineAdv) // LE MONSTRE EST SUR LA MEME LIGNE 
    {
        if(colMonster<colAdv){ // A GAUCHE
        //1 DIRECTION POSSIBLE : 6 
            pos=directionPosition(6);
        }
        else{ // A DROITE
        // 1 DIRECTION POSSIBLE : 4 
            pos=directionPosition(4);
        }
    }
    else if(colMonster==colAdv) // LE MONSTRE EST SUR LA MEME COLONNE
    {
        if(lineMonster>lineAdv){ // AU DESSUS
        // 1 DIRECTION POSSIBLE : 2 
            pos=directionPosition(2);
        }
        else{ // EN DESSOUS
        // 1 DIRECTION POSSIBLE : 8
            pos=directionPosition(8);
        }
    }

    return pos;
}


position smartMonsterMoveManager::aleatoirePosition(ground &g)
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





void smartMonsterMoveManager::move(ground &g)
{
    if(isNearAdventurer(g)) // SI MONSTRE = -8 CASES AVENTURIER
    {
        position p{possiblePosition(g)};
        char t=g.typeOf(p);

        if(t=='E') // CASE VIDE => LE MONSTRE Y VA
        {
            g.putElement(p,getPos());
        }
        else if(t=='P') //AVENTURIER => LE MONSTRE L ATTAQUE
        {
            //APPELER LE GESTIONNAIRE D ATTAQUE
        }
        
        // TT LES AUTRES CAS (mur,autre monstre,amulet) = RESTE A SA PLACE
        //(on ne fait rien)
    }
    else{ //LE MONSTRE = + DE 8 CASES = déplacement aléatoire

        position p{aleatoirePosition(g)};

        if((p.getColumn()<g.getNbColumns() && p.getLine()<g.getNbLines())) 
        {
            char t=g.typeOf(p);

            if(t=='E') // CASE VIDE => LE MONSTRE Y VA
            {
                g.putElement(p,getPos());
            }
            else if(t=='A') //AVENTURIER => LE MONSTRE L ATTAQUE
            {
                //APPELER LE GESTIONNAIRE D ATTAQUE
            }
            //SINON => amulet ou autre monstre ou mur=> reste à sa place

        }
        //SINON = position en dehors du terrain=> le monstre reste à sa place
        
        

    }
    

}


