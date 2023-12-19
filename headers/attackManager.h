#ifndef ATTACKMANAGER_H_INCLUDED
#define ATTACKMANAGER_H_INCLUDED
class groundElement;
//class ground;
#include <memory>
#include <iostream>

class attackManager
{
    public:
    virtual ~attackManager() = default;
    virtual double attack(groundElement *elem) =0;//std::unique_ptr<groundElement> element) =0;
    //true si mort
    virtual bool receiveAttack(groundElement *elem,double force)=0;

    double pickRandom() const;
    
};


#endif