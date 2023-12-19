#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include "groundElement.h"
#include "position.h"
#include "movementManager.h"
class attackManager;
class ground;

//CLASS REPRESENTANT UN PERSONNAGE DU TERRAIN ( monstres ou aventurier )


class character : public groundElement
{
    public:
        character(const position &p);
        virtual ~character()= default;
        double attack(attackManager &attackManag);
        bool receiveAttack(attackManager &attackManag,double force);
        void move(movementManager &movManager,ground &g,int direction=0);
        
        //GETTERS
        int forcePoints() const;
        int lifePoints() const;

        //SETTERS
        void setForcePoints(double nouvForce);
        void setLifePoints(double nouvLife);

    
    private:
        int d_forcePoints=100;
        int d_lifePoints=1000;

};




#endif