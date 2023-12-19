#ifndef TESTPOSITION_H
#define TESTPOSITION_H

#include "doctest.h"
#include "position.h"

TEST_CASE("Test de la classe Position")
{
    int i=1,j=2;
    position p{i,j};
    SUBCASE("Test constructeur par défaut")
    {
        position p{};
        REQUIRE_EQ(p.getLine(),0);
        REQUIRE_EQ(p.getColumn(),0);
    }
    SUBCASE("Test constructeur")
    {
        position p{23,10};
        REQUIRE_EQ(p.getLine(),23);
        REQUIRE_EQ(p.getColumn(),10);
    }
    SUBCASE("Test getLine")
    {
        REQUIRE_EQ(p.getLine(),i);
    }
    SUBCASE("Test getColonne")
    {
        REQUIRE_EQ(p.getColumn(),j);
    }
    SUBCASE("Test opérateur d'affectation")
    {
        position p1{0,3};
        position p2 = p1;
        REQUIRE_EQ(p1.getLine(),p2.getLine());
        REQUIRE_EQ(p1.getColumn(),p2.getColumn());
    }
    SUBCASE("Test opérateur d'égalité")
    {
        position p1{0,3};
        position p2{0,3};
        REQUIRE_EQ(p1==p2,true);
    }
}


#endif