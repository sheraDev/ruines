#ifndef OUTSIDE_H_INCLUDED
#define OUTSIDE_H_INCLUDED
#include "groundElement.h"
class viewManager;

class outside : public groundElement
{
    public:
        outside(const position &p);
        void display(const viewManager& view) const override;

};


#endif