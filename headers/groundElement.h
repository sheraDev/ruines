#ifndef GROUNDELEMENT_H_INCLUDED
#define GROUNDELEMENT_H_INCLUDED
#include "position.h"
class viewManager;


class groundElement
{
    public:
        virtual ~groundElement()=default;
        groundElement(const position &pos);
        void changePosition(const position& pos);
        position getPosition() const;
        virtual void display(const viewManager& view) const =0;
    private:
        position d_position;

};





#endif