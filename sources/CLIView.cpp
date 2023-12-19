#include "CLIView.h"
#include "adventurer.h"
#include "amulet.h"
#include "wall.h"
#include "monster.h"
#include "ground.h"
#include "outside.h"
using std::cout;

CLIView::CLIView(){}

void CLIView::displayAdventurer(const adventurer &adv) const
{
    cout<<" $ ";
}


void CLIView::displayWall(const wall &w) const
{
    cout<<" - ";
}

void CLIView::displayAmulet(const amulet &a) const
{
    cout<<" * ";
}

void CLIView::displayMonster(const monster &m) const
{
    cout<<" M ";
}

void CLIView::displayDoor(const door &d) const
{
    cout<<" ^ ";
}

void CLIView::displayOutside(const outside &o) const 
{
    cout<<" ~ ";
}





void CLIView::displayGround(const ground &g) const
{


    
    position p;
    int nbElmt,indice;
    char t;

    for(int i=0;i<g.getNbLines();i++)
    {
        for(int j=0; j<g.getNbColumns();j++)
        {
            p={i,j};
            nbElmt = g.nbElmtsPos(p);
            if(nbElmt==0) // AUCUN ELEMENT
            {
                cout<<" . ";
            }
            else if(nbElmt==1)
            {
                indice = g.indicePos(p);
                auto elem = g.getElementsTable()[indice].get();
                elem->display(*this);
            }
            else if(nbElmt==2) // l'aventurier et un monstre sur la meme case
            {
                cout<<" 💣 ";
            }
    
        }
        cout<<"\n";
    }




    /*for(int i=0;i<g.getNbLines();i++)
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
    }*/
}
