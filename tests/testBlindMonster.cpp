#ifndef TESTBLINDMONSTER_H
#define TESTBLINDMONSTER_H

#include "doctest.h"
#include "position.h"
#include "blindMonster.h"

TEST_CASE("Test de la classe smart monster")
{

    SUBCASE("Test constructeur")
    {
        position pos{0,1};
        blindMonster b{pos};

        REQUIRE_EQ(b.getPosition().getLine(),0);
        REQUIRE_EQ(b.getPosition().getColumn(),1);

    }
    
}


#endif