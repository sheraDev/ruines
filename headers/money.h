#ifndef MONEY_H_INCLUDED
#define MONEY_H_INCLUDED
#include "groundElement.h"
class viewManager;

class money : public groundElement
{
    public:
        money(const position &p,int value=10);
        void display(const viewManager& view) const override;
        int getValue() const;

    private:
        int d_value;

};


#endif