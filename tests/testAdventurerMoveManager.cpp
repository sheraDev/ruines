#ifndef TESTADVENTURERMOVEMANAGER_H
#define TESTADVENTURERMOVEMANAGER_H

#include "doctest.h"
#include "position.h"
#include "adventurerMoveManager.h"
#include "ground.h"

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
    SUBCASE("Test du déplacement de l'aventurier")
    {
        //construction d'un terrain 3x3
        
        ground g{3,3}; 


        /*    W | A  | M 
             ---|----|---
              O | P  | S
             ---|----|---
              B | D  | E
        */

        //ajout d'un mur à la case 0,0
        position p0{0,0};
        auto m = std::make_unique<wall>(p0);
        addElementToGround(std::move(m));

        //ajout d'une amulette à la case 0,1
        position p1{0,1};
        auto a = std::make_unique<amulet>(p1);
        addElementToGround(std::move(a));    

        //ajout d'un tas de pièce (valeur =10 par défaut) à la case 0,2    
        position p2{0,1};
        auto t = std::make_unique<money>(p2);
        addElementToGround(std::move(p2));

        //ajout d'une case inaccesible à la case 1,0
        position p3{1,0};
        auto o = std::make_unique<outside>(p3);
        addElementToGround(std::move(o));

        // ajout de l'aventurier à la case 1,1
        position p4{1,1};
        auto p = std::make_unique<adventurer>(p4);
        addElementToGround(std::move(p));

        //ajout d'un smart monster à la case 1,2
        position p5{1,2};
        auto s = std::make_unique<smartMonster>(p5);
        addElementToGround(std::move(s));

        //ajout d'un blind monster à la case 2,0
        position p6{2,0};
        auto s = std::make_unique<smartMonster>(p6);
        addElementToGround(std::move(s));

        //ajout d'une sortie à la case 2,1
        position p7{2,1};
        auto d = std::make_unique<door>(p7);
        addElementToGround(std::move(d));

        //la case 2,2 est vide

        SUBCASE("Test rester à sa place")
        {
            int direction = 5;
            position anciennePosAdv = g.getAdventurerPosition();
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(anciennePosAdv,nouvPosAdv);
        }
        SUBCASE("Test aller dans un mur") //doit rester à sa place
        {
            int direction = 1;
            position anciennePosAdv = g.getAdventurerPosition();
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(anciennePosAdv,nouvPosAdv);
        }
        SUBCASE("Test aller sur une case inaccesible") //doit rester à sa place
        {
            int direction = 4;
            position anciennePosAdv = g.getAdventurerPosition();
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(anciennePosAdv,nouvPosAdv);
        }
        SUBCASE("Test aller à la case de sortie sans avoir l'amulette") //doit rester à sa place
        {
            int direction = 8;
            position anciennePosAdv = g.getAdventurerPosition();
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(anciennePosAdv,nouvPosAdv);
        }
        SUBCASE("Test aller sur la case de l'amulette") //doit aller en 0,1
        {
            int direction = 2;
            position anciennePosAdv = g.getAdventurerPosition();
            position posAttendue{0,1};
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(posAttendue,nouvPosAdv);

            //Vérifier que l'aventurier a récupéré l'amulette
            int indiceAdv{g.getIndiceAdventurer()};
            auto adv=dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get());
            REQUIRE_EQ(adv->hasAmulet(),true);

            //retourner au milieu du terrain
            adventurerMoveManager advMvv{nouvPosAdv};
            adv.move(g,8);
        }
        SUBCASE("Test aller sur un smart monster") //doit aller en 1,2
        {
            int direction = 6;
            position anciennePosAdv = g.getAdventurerPosition();
            position posAttendue{1,2};
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(posAttendue,nouvPosAdv);

            //retourner au milieu du terrain
            adventurerMoveManager advMvv{nouvPosAdv};
            adv.move(g,4);
        }
        SUBCASE("Test aller sur un blind monster") //doit aller en 2,0
        {
            int direction = 7;
            position anciennePosAdv = g.getAdventurerPosition();
            position posAttendue{2,0};
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(posAttendue,nouvPosAdv);

            //retourner au milieu du terrain
            adventurerMoveManager advMvv{nouvPosAdv};
            adv.move(g,3);
        }
        SUBCASE("Test aller sur une case vide") //doit aller en 2,2
        {
            int direction = 9;
            position anciennePosAdv = g.getAdventurerPosition();
            position posAttendue{2,2};
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(posAttendue,nouvPosAdv);

            //retourner au milieu du terrain
            adventurerMoveManager advMvv{nouvPosAdv};
            adv.move(g,1);
        }
        SUBCASE("Test aller sur un tas de pièce") //doit aller en 0,2
        {
            int direction = 3;
            position anciennePosAdv = g.getAdventurerPosition();
            position posAttendue{0,2};
            adventurerMoveManager advMv{anciennePosAdv};
            advMv.move(g,direction);
            position nouvPosAdv = g.getAdventurerPosition();

            REQUIRE_EQ(posAttendue,nouvPosAdv);

            //vérifier que le montant a été récupéré
            int indiceAdv{g.getIndiceAdventurer()};
            auto adv=dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get());
            int montantBourse = adv->getBourse();

            REQUIRE_EQ(montantBourse,10);

            //retourner au milieu du terrain
            adventurerMoveManager advMvv{nouvPosAdv};
            adv.move(g,7);
        }




    }
    
}


#endif