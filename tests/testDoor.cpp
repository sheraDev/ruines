#ifndef TESTDOOR_H
#define TESTDOOR_H

#include "doctest.h"
#include "position.h"
#include "door.h"

TEST_CASE("Test de la classe door")
{

    SUBCASE("Test constructeur")
    {
        position pos{9,3};
        door d{pos};

        REQUIRE_EQ(d.getPosition().getLine(),9);
        REQUIRE_EQ(d.getPosition().getColumn(),3);
    }
    
}


#endif