#ifndef MONSTERMOVEMANAGER_H_INCLUDED
#define MONSTERMOVEMANAGER_H_INCLUDED
#include "movementManager.h"
class ground;


//GESTIONNAIRE DE DEPLACEMENTS DE MONSTRES 

class monsterMoveManager : public movementManager
{
    public:
        monsterMoveManager(const position &p);

};



#endif