#include "emotView.h"
#include "adventurer.h"
#include "amulet.h"
#include "wall.h"
#include "monster.h"
#include "ground.h"
#include "outside.h"
using std::cout;

emotView::emotView(){}

void emotView::displayAdventurer(const adventurer &adv) const
{
    cout<<" 💈 ";
}


void emotView::displayWall(const wall &w) const
{
    cout<<" 🪵 ";
}

void emotView::displayAmulet(const amulet &a) const
{
    cout<<" 🗝 ";// 🗝 ";
}

void emotView::displayMonster(const monster &m) const
{
    cout<<" ♟ "; //♟
}

void emotView::displayDoor(const door &d) const
{
    cout<<" 🚪 ";
}

void emotView::displayOutside(const outside &o) const 
{
    cout<<" 🪦 ";
}

void emotView::displayMoney(const money &m) const
{
    cout<<" ⌛️ ";//💰";
}



void emotView::displayGround(const ground &g) const
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
                cout<<" ⚱️ " ;             // d🚨 ";
            }
            else if(nbElmt==1)
            {
                indice = g.indicePos(p);
                auto elem = g.getElementsTable()[indice].get();
                elem->display(*this);
            }
            else if(nbElmt==2) // l'aventurier et un monstre sur la meme case
            {
                cout<<" ⚔️ ";
            }
    
        }
        cout<<"\n";
    }
    cout<<"\n Code :\n $ : vous | Ⓜ️ : monster  | 🗝 : amulette | . : vide | 💰 : tas de pièces\n - : mur | ~ : extérieur | 💣 : bataille en cours | ^ : sortie \n\n";
}

