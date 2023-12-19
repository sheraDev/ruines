#include <iostream>
#include "game.h"
#include "menu.h"
#include "ground.h"
#include "viewManager.h"
#include "CLIView.h"
#include <random>
#include <memory>
#include "adventurer.h"
#include "blindMonster.h"
#include "movementManager.h"
#include "smartMonsterMoveManager.h"
#include "blindMonsterMoveManager.h"
#include "adventurerMoveManager.h"

using std::cout;
using std::make_unique;

#include <fstream>


/*
void ancientest(){
         ground g{};
    g.buildGround();
    CLIView v{};
    cout<<"Terrain:\n";
    g.display(v);
   
   /* cout<<"type de la 1ere case :"<<g.typeOf({0,0});

    cout<<"suppression 1ere case \n";
    g.removeElement({0,0});

    cout<<"Réaffichage terrain : \n";
    g.display(v);

    cout<<"Deplacement de la 2eme case dans la 1 ere : \n";
    g.putElement({0,0},{0,1});
    g.display(v);*/

    /*
    cout<<"\n Tests déplacement monstre voyant :  ";
    smartMonsterMoveManager m{{4,1}};

    m.move(g);
    cout<<"\n Réaffichage du terrain : \n";
    g.display(v); */


    /*
    cout<<"\n Tests déplacement monstre aveugle : ";
    blindMonsterMoveManager m{{0,0}};

    m.move(g);

    cout<<"Position aleatoire choisie : ("<<m.possiblePosition(g).getLine()<<","<<m.possiblePosition(g).getColumn()<<")\n";
    cout<<"Re affichage du terrain : \n";

    g.display(v); */



/*
   
    cout<<"\n Test déplacement joueur : \n";
    adventurerMoveManager m{{1,1},2};

    position posAv {g.getAdventurerPosition()};
    auto p=dynamic_cast<adventurer*>(g.getElementsTable()[posAv.getLine()][posAv.getColumn()].get());
    cout<<"AVANT MOVE : amulet ";
    p->hasAmulet()?cout<<"OUI\n":cout<<"NON\n";

    m.move(g);

    cout<<"Re affichage du terrain : \n";

    g.display(v);
    p->hasAmulet()?cout<<"OUI\n":cout<<"NON\n";

    


    }*/

int main()
{
    //std::ofstream f("testfichier");

    game g{};
    g.play();

    /*
    ground g{};
    g.buildGround();
    CLIView v{};
    cout<<"Terrain:\n";
    
    g.display(v);
*/
    
    //TEST DE DEPLACEMENT DU PERSONNAGE : OK
    /*
    
    
    position p{0,0};
    adventurerMoveManager m{p,8}; //aller une case en bas
    m.move(g);

    cout<<"perso en 0 0 se deplace une case en bas, reaffichage : \n";
    g.display(v);
*/
    //TEST DE DEPLACEMENT DU SMART MONSTER : OK
    /*
    position pm{0,0};
    smartMonsterMoveManager m{pm};
    cout<<"SMoNSTER en 0 0 se deplace vers P, reaffichage : \n";
    
    m.move(g);
    g.display(v); */

    /*cout<<"\n affichage du tab d'elem : \n";

    int i=0;
    for(const auto &e:g.getElementsTable())
    {   cout<<g.typeOf(i);
        cout<<e->getPosition().getLine()<<","<<e->getPosition().getColumn()<<"\n";
        i++;
    }*/

    //TEST DE DEPLACEMENT DU MONSTRE AVEUGLE
    /*position pmm{1,1};
    blindMonsterMoveManager mo{pmm};
    cout<<"BMoNSTER en 1 1 se deplace aleatoirement, reaffichage : \n";
    
    mo.move(g);
    g.display(v);*/

    

    


}