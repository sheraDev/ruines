#ifndef TESTADVENTURER_H
#define TESTADVENTURER_H


#include "doctest.h"
#include "adventurer.h"
#include "position.h"
#include "armory.h"
#include "sword.h"

TEST_CASE("Test de la classe adventurer")
{
    int i=1,j=2;
    position p{i,j};
    adventurer a{p};

    SUBCASE("Test constructeur")
    {
        REQUIRE_EQ(a.getPosition().getLine(),i);
        REQUIRE_EQ(a.getPosition().getColumn(),j);
    }
    SUBCASE("Test possession amulette")
    {
        a.setAmuletTrue();
        REQUIRE_EQ(a.hasAmulet(),true);
    }
    SUBCASE("Test set épée")
    {
        a.setSwordSolidity(10);
        REQUIRE_EQ(a.getSword().getSolidity(),10);
    }
    SUBCASE("Test set armure")
    {
        a.setArmorSolidity(10);
        REQUIRE_EQ(a.getArmor().getSolidity(),10);
    }
    SUBCASE("Test is out")
    {
        a.setIsOutTrue();
        REQUIRE_EQ(a.isOutWithAmulet(),true);
    }
    SUBCASE("Test ajouter à la bourse")
    {
        a.addToBourse(10);
        REQUIRE_EQ(a.getBourse(),10);
    }
    SUBCASE("Enlever à la bourse")
    {
        a.addToBourse(10);
        a.removeFromBourse(10);
        REQUIRE_EQ(a.getBourse(),0);
    }
    SUBCASE("Ajouter à la solidité de l'armure")
    {
        int ancienneSol = a.getArmor().getSolidity();
        a.addToArmorSolidity(10);
        int nouvSol = ancienneSol+10;
        REQUIRE_EQ(a.getArmor().getSolidity(),nouvSol);
    }
    SUBCASE("Ajouter à la solidité de l'épée")
    {
        int ancienneSol = a.getSword().getSolidity();
        a.addToSwordSolidity(10);
        int nouvSol = ancienneSol+10;
        REQUIRE_EQ(a.getSword().getSolidity(),nouvSol);
    }
}

#endif