#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include "groundElement.h"
#include "position.h"

//CLASS REPRESENTANT UN PERSONNAGE DU TERRAIN ( monstres ou aventurier )


class character : public groundElement
{
    public:
        character(const position &p);
        virtual ~character()= default;
        virtual void attack()=0;
        virtual void receiveAttack()=0;
        virtual void moveAt(const position&p)=0;
        int forcePoints() const;
        int lifePoints() const;
    
    private:
        int d_forcePoints;
        int d_lifePoints;

};




#endif