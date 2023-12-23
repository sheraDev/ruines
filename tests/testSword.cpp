#ifndef TESTSWORD_H
#define TESTSWORD_H

#include "doctest.h"
#include "position.h"
#include "sword.h"

TEST_CASE("Test de la classe sword")
{

    SUBCASE("Test constructeur")
    {
        double sol=10.0;
        sword s{sol};

        REQUIRE_EQ(s.getSolidity(),10);
    }
    
}


#endif