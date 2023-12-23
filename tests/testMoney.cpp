#ifndef TESTMONEY_H
#define TESTMONEY_H

#include "doctest.h"
#include "position.h"
#include "money.h"

TEST_CASE("Test de la classe money")
{
    position p{1,1};

    SUBCASE("Test constructeur")
    {
        int val=10;
        money m{p,val};

        REQUIRE_EQ(m.getValue(),10);
    }
    SUBCASE("Test get value")
    {
        money m{p,20};
        REQUIRE_EQ(m.getValue(),20);
    }

    
}


#endif