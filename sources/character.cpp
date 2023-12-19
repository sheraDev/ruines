#include "character.h"
#include "attackManager.h"
#include "movementManager.h"

character::character(const position &p):groundElement{p}{}



int character::forcePoints() const
{
    return d_forcePoints;
}

int character::lifePoints() const
{
    return d_lifePoints;
}

void character::setForcePoints(double nouvForce)
{
    d_forcePoints = nouvForce;
}
        
        
void character::setLifePoints(double nouvLife)
{
    d_lifePoints = nouvLife;
}

double character::attack(attackManager &attackManag)
{
    double force = attackManag.attack(this);
    return force;
}

bool character::receiveAttack(attackManager &attackManag,double force)
{
    bool mort = attackManag.receiveAttack(this,force);
    return mort;
}

void character::move(movementManager &movManager,ground &g,int direction)
{
    movManager.move(g,direction);
}