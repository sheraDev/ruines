#ifndef TESTARMORY_H
#define TESTARMORY_H

#include "doctest.h"
#include "position.h"
#include "armory.h"

TEST_CASE("Test de la classe armory")
{

    SUBCASE("Test constructeur")
    {
        int sol = 10;
        armory a{sol};

        REQUIRE_EQ(a.getSolidity(),sol);
    }
    
}


#endif