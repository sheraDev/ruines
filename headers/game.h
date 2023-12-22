#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <string>
#include <memory>
class ground;
class monster;
#include "viewManager.h"
#include <vector>
#include "monster.h"


class game
{   
    public:
     game();
     void play();
     //void deplacement()
     void afficherInfosMonstres(const monster *m,char type) ;
     void chargerGround(ground &g);
     int choixView();
     std::unique_ptr<viewManager> createView(int choix);

     void useBourse(adventurer *adv);

     void afficherInfosAdv(const adventurer*adv);
     void afficherInfosMonstresProches(const std::vector<monster*> &tabMonstres) ;
     std::vector<monster*> deplacerMonstres(ground&g);

};




#endif