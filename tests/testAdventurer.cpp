#ifndef TESTADVENTURER_H
#define TESTADVENTURER_H


#include "doctest.h"
#include "adventurer.h"
#include "position.h"

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
}

#endif