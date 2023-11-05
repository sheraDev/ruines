#include "CLIView.h"
#include "adventurer.h"
#include "amulet.h"
#include "wall.h"
#include "monster.h"
#include "ground.h"
using std::cout;

CLIView::CLIView(){}

void CLIView::displayAdventurer(const adventurer &adv) const
{
    cout<<"$";
}


void CLIView::displayWall(const wall &w) const
{
    cout<<"-";
}

void CLIView::displayAmulet(const amulet &a) const
{
    cout<<"*";
}

void CLIView::displayMonster(const monster &m) const
{
    cout<<"M";
}

void CLIView::displayGround(const ground &g) const
{
    for(int i=0;i<g.getNbLines();i++)
    {
        for(int j=0; j<g.getNbColumns();j++)
        {
            if(g.getElementsTable()[i][j].get()==nullptr)
            {
                cout<<".";
            }
            else{
               g.getElementsTable()[i][j]->display(*this);

            }

        }
        cout<<std::endl;
    }
}
