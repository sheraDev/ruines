#include <iostream>
#include "game.h"
#include "menu.h"
#include "ground.h"
#include "viewManager.h"
#include "CLIView.h"
#include <random>
#include <memory>
#include "adventurer.h"
#include "movementManager.h"
#include "smartMonsterMoveManager.h"
#include "blindMonsterMoveManager.h"
#include "adventurerMoveManager.h"

using std::cout;

int main()
{
    
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

    

}