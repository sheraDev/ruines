#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <string>
#include <memory>
class ground;
class monster;
#include "viewManager.h"


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
};




#endif