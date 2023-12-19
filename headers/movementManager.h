#ifndef MOVEMENTMANAGER_H_INCLUDED
#define MOVEMENTMANAGER_H_INCLUDED
#include "position.h"
#include "vector"
//class ground;
#include "ground.h"
class movementManager 
{
    public:
         movementManager(const position&pos); 
        virtual ~movementManager()=default;
        position getPos() const;

        virtual position directionPosition(int direction)=0;
        virtual void move(ground &g,int direction)=0;

  protected:
        position d_position;
       
};

#endif