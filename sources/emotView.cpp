#include "emotView.h"
#include "adventurer.h"
#include "amulet.h"
#include "wall.h"
#include "monster.h"
#include "ground.h"
#include "outside.h"
#include "termcolor.h"
using std::cout;

emotView::emotView(){}

void emotView::displayAdventurer(const adventurer &adv) const
{
    cout<<termcolor::on_color<78, 88, 65> <<" $ ";
}


void emotView::displayWall(const wall &w) const
{
    cout << termcolor::on_color<70, 64, 9> << "   " << termcolor::reset;
}

void emotView::displayAmulet(const amulet &a) const
{
    cout<<termcolor::color<185, 63, 215><<termcolor::on_color<78, 88, 65> <<" * "<< termcolor::reset;// 🗝 ";
}

void emotView::displayMonster(const monster &m) const
{
    cout<<termcolor::color<21, 8, 75><<termcolor::on_color<78, 88, 65> <<" M "<< termcolor::reset; //♟
}

void emotView::displayDoor(const door &d) const
{
    cout<<termcolor::color<240, 230, 140><<termcolor::on_color<78, 88, 65> <<" ^ "<< termcolor::reset;
}

void emotView::displayOutside(const outside &o) const 
{
    cout<<termcolor::on_color<125, 27, 27> <<"   "<< termcolor::reset;
}

void emotView::displayMoney(const money &m) const
{
    cout<<termcolor::green<<termcolor::on_color<78, 88, 65> <<" € "<< termcolor::reset;
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
                cout<<termcolor::on_color<78, 88, 65> <<"   "<< termcolor::reset;
            }
            else if(nbElmt==1)
            {
                indice = g.indicePos(p);
                auto elem = g.getElementsTable()[indice].get();
                elem->display(*this);
            }
            else if(nbElmt==2) // l'aventurier et un monstre sur la meme case
            {
                cout<<termcolor::on_color<78, 88, 65><<" ⚔️ ";
            }
    
        }
        cout<<"\n";
    }
    cout<<
    "\n Code :\n " << 
    termcolor::on_color<78, 88, 65> 
    << " $ " 
    << termcolor::reset 
    << ": vous | " 
    << termcolor::on_color<78, 88, 65> 
    << termcolor::color<21, 8, 75>
    << " M " 
    << termcolor::reset 
    << ": monster  | "
    << termcolor::on_color<78, 88, 65>
    << termcolor::color<185, 63, 215>
    << " * " 
    << termcolor::reset 
    << ": amulette | "
    << termcolor::on_color<78, 88, 65>
    << "  "
    << termcolor::reset 
    << ": vide | "
    << termcolor::on_color<78, 88, 65>
    << termcolor::green
    << " € " 
    << termcolor::reset 
    << ": tas de pièces\n " 
    << termcolor::on_color<70, 64, 9>
    << "   " 
    << termcolor::reset 
    << ": mur | "
    << termcolor::on_color<125, 27, 27>
    << "  "
    << termcolor::reset 
    << ": extérieur | "    
    << termcolor::on_color<78, 88, 65>
    << " ⚔️ " 
    << termcolor::reset 
    << ": bataille en cours | "
    << termcolor::on_color<78, 88, 65>
    << termcolor::color<240, 230, 140>
    << " ^ " 
    << termcolor::reset
    << " : sortie \n\n";
}

