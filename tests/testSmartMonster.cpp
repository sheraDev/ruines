#ifndef TESTSMARTMONSTER_H
#define TESTSMARTMONSTER_H

#include "doctest.h"
#include "position.h"
#include "smartMonster.h"

TEST_CASE("Test de la classe smart monster")
{

    SUBCASE("Test constructeur")
    {
        position pos{0,1};
        smartMonster s{pos};

        REQUIRE_EQ(s.getPosition().getLine(),0);
        REQUIRE_EQ(s.getPosition().getColumn(),1);

    }
    
}


#endif