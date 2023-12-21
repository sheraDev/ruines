#ifndef TESTOUTSIDE_H
#define TESTOUTSIDE_H

#include "doctest.h"
#include "position.h"
#include "outside.h"

TEST_CASE("Test de la classe outside")
{

    SUBCASE("Test constructeur")
    {
        position pos{4,2};
        outside o{pos};

        REQUIRE_EQ(o.getPosition().getLine(),4);
        REQUIRE_EQ(o.getPosition().getColumn(),2);

    }
    
}


#endif