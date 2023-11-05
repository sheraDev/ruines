#ifndef MOVEMENTMANAGER_H_INCLUDED
#define MOVEMENTMANAGER_H_INCLUDED
#include "position.h"
#include "vector"
class ground;

class movementManager 
{
    public:
        movementManager(const position&pos, int direction=0); //direction inutile dans le monsterMover
        virtual ~movementManager()=default;
        position getPos() const;
        int getDirection() const;

        virtual position directionPosition(int direction)=0;
        virtual void move(ground &g)=0;



    private:
        position d_position;
        int d_direction;

};

#endif