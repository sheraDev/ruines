#ifndef TESTGROUND_H
#define TESTGROUND_H

#include "doctest.h"
#include "position.h"
#include "ground.h"
#include "amulet.h"
#include <iostream>
#include <memory>
#include <groundElement.h>
#include "adventurer.h"
#include "wall.h"

TEST_CASE("Test de la classe ground")
{
    int nbl=10;
    int nbc=4;
    ground g{nbl,nbc};

    SUBCASE("Test constructeur")
    {
        REQUIRE_EQ(g.getNbLines(),nbl);
        REQUIRE_EQ(g.getNbColumns(),nbc);
    }
    SUBCASE("Test getNbLine")
    {
        REQUIRE_EQ(g.getNbLines(),nbl);
    }
    SUBCASE("Test getNbCol")
    {
        REQUIRE_EQ(g.getNbColumns(),nbc);
    }
    SUBCASE("Test get nombre total d'éléments du ground")
    {
        REQUIRE_EQ(g.getNbTotalElmts(),0);
    }
    SUBCASE("Test setSize")
    {
        ground g;
        int nbl=10;
        int nbc=3;
        g.setSize(10,3);

        REQUIRE_EQ(g.getNbLines(),10);
        REQUIRE_EQ(g.getNbColumns(),3);

    }
    SUBCASE("Test ajouter élément au ground")
    {
        SUBCASE("Ajouter un seul élément ")
        {
            position p{1,1};
            auto a = std::make_unique<amulet>(p);  //Créer un élément
            g.addElementToGround(std::move(a));   //l'ajouter

            bool t= dynamic_cast<amulet*>(g.getElementsTable()[0].get());
            REQUIRE_EQ(t,true);
        }
        SUBCASE("Ajouter 2 éléments ")
        {
            position p1{1,1};
            position p2{1,2};


            auto adv = std::make_unique<adventurer>(p1); //Créer un élément
            g.addElementToGround(std::move(adv));   //l'ajouter
            
            auto w = std::make_unique<wall>(p2); 
            g.addElementToGround(std::move(w));   

            bool t1= dynamic_cast<adventurer*>(g.getElementsTable()[0].get());
            bool t2= dynamic_cast<wall*>(g.getElementsTable()[1].get());

            REQUIRE_EQ(t1,true);
            REQUIRE_EQ(t2,true);

        }     
    }
    SUBCASE("Test enlever élément du ground")
    {
        position p{1,1};

        auto adv = std::make_unique<adventurer>(p); //Créer un élément
        g.addElementToGround(std::move(adv));   //l'ajouter

        g.removeElement(0); //l'enlever

        REQUIRE_EQ(g.getNbTotalElmts(),0);

    }
    SUBCASE("Test position aventurier")
    {
        position p{1,1};

        auto adv = std::make_unique<adventurer>(p);
        g.addElementToGround(std::move(adv));

        REQUIRE_EQ(g.getAdventurerPosition().getLine(),p.getLine());
        REQUIRE_EQ(g.getAdventurerPosition().getColumn(),p.getColumn());
    }
    SUBCASE("Test type de la case")
    {
        position p{1,1};

        auto adv = std::make_unique<adventurer>(p);
        g.addElementToGround(std::move(adv));
        char t=g.typeOf(0);
        REQUIRE_EQ(t,'P');

    }
    SUBCASE("Test position de l'element")
    {
        position p{1,1};
        auto w = std::make_unique<wall>(p); 
        g.addElementToGround(std::move(w));   

        REQUIRE_EQ(g.posOf(0).getLine(),p.getLine());
        REQUIRE_EQ(g.posOf(0).getColumn(),p.getColumn());

    }
    SUBCASE("Test get indice aventurier")
    {
        position p1{1,1};
        position p2{1,2};

        auto w = std::make_unique<wall>(p2); 
        auto adv = std::make_unique<adventurer>(p1); 

        g.addElementToGround(std::move(w));   
        g.addElementToGround(std::move(adv));

        REQUIRE_EQ(g.getIndiceAdventurer(),1);
    }
    SUBCASE("Test nombre d'éléments à une position")
    {
        position posRecherchee{2,2}; 


        SUBCASE(" Test 0 elements")
        {
            position pos{2,3};
            auto w = std::make_unique<wall>(pos);
            g.addElementToGround(std::move(w));  

            REQUIRE_EQ(g.nbElmtsPos(posRecherchee),0);
        }
        SUBCASE("Test 1 element")
        {
            auto w = std::make_unique<wall>(posRecherchee); 
            g.addElementToGround(std::move(w));   

            REQUIRE_EQ(g.nbElmtsPos(posRecherchee),1);
        }
        SUBCASE("Test 2 elements")
        {
               
            auto w = std::make_unique<wall>(posRecherchee); 
            auto adv = std::make_unique<adventurer>(posRecherchee); 

            g.addElementToGround(std::move(w));   
            g.addElementToGround(std::move(adv));

            REQUIRE_EQ(g.nbElmtsPos(posRecherchee),2);
        }
        

    }
    SUBCASE("Test indice élément en fonction de sa position et son type")
    {
        position p{1,1};


        auto adv = std::make_unique<adventurer>(p);  //indice 0
        auto w = std::make_unique<wall>(p);          //indice 1

        g.addElementToGround(std::move(adv));    
        g.addElementToGround(std::move(w)); 

        int indiceAdv = 0;
        int indiceWall = 1;

        REQUIRE_EQ(g.getIndiceElmt(p,'W'),indiceWall);

    }
    SUBCASE("Test indice element en fonction de sa position")
    {
        position p{1,1};
        position p1{0,3};


        auto adv = std::make_unique<adventurer>(p);  //indice 0
        auto w = std::make_unique<wall>(p1);          //indice 1

        g.addElementToGround(std::move(adv));    
        g.addElementToGround(std::move(w));

        int indiceAdv = 0;
        int indiceWall = 1;
 

        REQUIRE_EQ(g.indicePos(p),indiceAdv);
    }
    SUBCASE("Test récupération indices de tous les elements à une position donnée")
    {
        position posRecherchee{2,2}; 
        position autrePos{1,2};
       
        auto w1 = std::make_unique<wall>(posRecherchee); 
        auto adv = std::make_unique<adventurer>(autrePos);
        auto w2 = std::make_unique<wall>(posRecherchee); 
 

        g.addElementToGround(std::move(w1));   
        g.addElementToGround(std::move(adv));
        g.addElementToGround(std::move(w2));   

        int indiceW1=0;
        int indiceAdv=1;
        int indiceW2=2;

        //tableau qui contient les indices de tous les éléments à la pos posRecherchee
        std::vector<int> tabIndices = g.getIndicePos(posRecherchee);

        REQUIRE_EQ(tabIndices[0],indiceW1);
        REQUIRE_EQ(tabIndices[1],indiceW2);


    }
    
}


#endif