#ifndef TESTSMARTMONSTERMOVEMANAGER_H
#define TESTSMARTMONSTERMOVEMANAGER_H

#include "doctest.h"
#include "position.h"
#include "smartMonsterMoveManager.h"

#include "groundElement.h"
#include "character.h"
#include "monster.h"
#include "smartMonster.h"
#include "blindMonster.h"
#include "adventurer.h"
#include "wall.h"
#include "amulet.h"
#include "outside.h"
#include "door.h"
#include "money.h"

TEST_CASE("Test de la classe smart monster move manager")
{
    position p{1,1};
    smartMonsterMoveManager m{p};


    SUBCASE("Test constructeur")
    {
        REQUIRE_EQ(m.getPos().getLine(),p.getLine());
        REQUIRE_EQ(m.getPos().getColumn(),p.getColumn());
    }
    SUBCASE("Test de la méthode renvoyant la position suivant une direction")
    {   
        SUBCASE("Test direction 1 (diagonale en haut gauche)")
        {
            position posDir = m.directionPosition(1);
            position posAttendue = {p.getLine()-1,p.getColumn()-1};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 2 (en haut)")
        {
            position posDir = m.directionPosition(2);
            position posAttendue = {p.getLine()-1,p.getColumn()};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 4 (gauche)")
        {
            position posDir = m.directionPosition(4);
            position posAttendue = {p.getLine(),p.getColumn()-1};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 6 (droite)")
        {
            position posDir = m.directionPosition(6);
            position posAttendue = {p.getLine(),p.getColumn()+1};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 8 (en bas)")
        {
            position posDir = m.directionPosition(8);
            position posAttendue = {p.getLine()+1, p.getColumn()};
            REQUIRE_EQ(posDir,posAttendue);
        }

    }
    SUBCASE("Test de la méthode vérifiant si le monstre est proche de l'aventurier")
    {
        SUBCASE("Test aventurier proche")
        {

            //construction d'un terrain 3x3
        
            ground g{3,3}; 


            /*  E | E  | E 
               ---|----|---
                E | P  | S
               ---|----|---
                E | E  | E
            */

            // ajout de l'aventurier à la case 1,1
            position pAdv{1,1};
            auto p = std::make_unique<adventurer>( pAdv);
            g.addElementToGround(std::move(p));

            //ajout d'un smart monster à la case 1,2
            position pMonstre{1,2};
            auto s = std::make_unique<smartMonster>(pMonstre);
            g.addElementToGround(std::move(s));

            
            smartMonsterMoveManager smrtMv{pMonstre};
            REQUIRE_EQ(smrtMv.isNearAdventurer(g),true);
        }
        SUBCASE("L'aventurier est loin")
        {
            //construction d'un terrain 10x10
        
            ground g{10,10}; 

            // ajout de l'aventurier à la case 0,0
            position pAdv{0,0};
            auto p = std::make_unique<adventurer>(pAdv);
            g.addElementToGround(std::move(p));

            //ajout d'un smart monster à la case 9,9
            position pMonstre{9,9};
            auto s = std::make_unique<smartMonster>(pMonstre);
            g.addElementToGround(std::move(s));

            
            smartMonsterMoveManager smrtMv{pMonstre};
            REQUIRE_EQ(smrtMv.isNearAdventurer(g),false);
        }
        
    }
}


#endif