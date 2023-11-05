#ifndef ARMORY_H_INCLUDED
#define ARMORY_H_INCLUDED
#include "weapon.h"

class armory : public weapon
{
    public:
        armory();
        void use() override;
};


#endif