#ifndef TESTWALL_H
#define TESTWALL_H

#include "doctest.h"
#include "position.h"
#include "wall.h"

TEST_CASE("Test de la classe wall")
{
    int i=1,j=2;
    position p{i,j};
    wall w{p};

    SUBCASE("Test constructeur")
    {
        REQUIRE_EQ(w.getPosition().getLine(),i);
        REQUIRE_EQ(w.getPosition().getColumn(),j);
    }
}


#endif
