#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED
#include "groundElement.h"
class viewManager;

class wall : public groundElement
{
    public:
        wall(const position &p);
        void display(const viewManager& view) const override;
};


#endif