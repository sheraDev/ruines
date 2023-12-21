#ifndef TESTADVENTURERMOVEMANAGER_H
#define TESTADVENTURERMOVEMANAGER_H

#include "doctest.h"
#include "position.h"
#include "adventurerMoveManager.h"

TEST_CASE("Test de la classe adventurer move manager")
{
    position p{1,1};
    adventurerMoveManager m{p};


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
        SUBCASE("Test direction 3 (diagonale en haut droite)")
        {
            position posDir = m.directionPosition(3);
            position posAttendue = {p.getLine()-1, p.getColumn()+1};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 4 (gauche)")
        {
            position posDir = m.directionPosition(4);
            position posAttendue = {p.getLine(),p.getColumn()-1};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 5 (reste à sa place)")
        {
            position posDir = m.directionPosition(5);
            position posAttendue = p;
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 6 (droite)")
        {
            position posDir = m.directionPosition(6);
            position posAttendue = {p.getLine(),p.getColumn()+1};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 7 (diagonale en bas gauche)")
        {
            position posDir = m.directionPosition(7);
            position posAttendue = {p.getLine()+1, p.getColumn()-1};
            REQUIRE_EQ(posDir,posAttendue);
        }
        SUBCASE("Test direction 8 (diagonale en bas droite)")
        {
            position posDir = m.directionPosition(8);
            position posAttendue = {p.getLine()+1, p.getColumn()+1};
            REQUIRE_EQ(posDir,posAttendue);
        }

    }
    
}


#endif