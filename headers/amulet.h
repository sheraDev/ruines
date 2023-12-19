#ifndef AMULET_H_INCLUDED
#define AMULET_H_INCLUDED
#include "groundElement.h"
class viewManager;

class amulet : public groundElement
{
    public:
        amulet(const position &p);
        void display(const viewManager& view) const override;
};





#endif