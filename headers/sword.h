#ifndef SWORD_H_INCLUDED
#define SWORD_H_INCLUDED
#include "weapon.h"

class sword : public weapon
{
    public:
        sword();
        void use() override;

};



#endif