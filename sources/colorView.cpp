#include "colorView.h"
#include "adventurer.h"
#include "amulet.h"
#include "wall.h"
#include "monster.h"
#include "ground.h"
#include "outside.h"
#include "termcolor.h"
using std::cout;

colorView::colorView(){}

void colorView::displayAdventurer(const adventurer &adv) const
{
    cout<< termcolor::bold << termcolor::blink << termcolor::on_color<78, 88, 65> <<" $ " << termcolor::reset;
}


void colorView::displayWall(const wall &w) const
{
    cout<< termcolor::on_color<70, 64, 9> << "   " << termcolor::reset;
}

void colorView::displayAmulet(const amulet &a) const
{
    cout<< termcolor::bold << termcolor::color<185, 63, 215> << termcolor::on_color<78, 88, 65> << " * " << termcolor::reset;// 🗝 ";
}

void colorView::displayMonster(const monster &m) const
{
    cout<< termcolor::bold << termcolor::color<21, 8, 75><<termcolor::on_color<78, 88, 65> <<" M "<< termcolor::reset; //♟
}

void colorView::displayDoor(const door &d) const
{
    cout<<termcolor::bold << termcolor::color<240, 230, 140><<termcolor::on_color<78, 88, 65> <<" ^ "<< termcolor::reset;
}

void colorView::displayOutside(const outside &o) const 
{
    cout<<termcolor::on_color<125, 27, 27> <<"   "<< termcolor::reset;
}

void colorView::displayMoney(const money &m) const
{
    cout<<termcolor::bold << termcolor::green<<termcolor::on_color<78, 88, 65> <<" € "<< termcolor::reset;
}


void colorView::displayGround(const ground &g) const
{

    position p;
    int nbElmt,indice;
    char t;

    for(int i=0;i<g.getNbLines();i++)
    {
        cout << " ";
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
                cout<< termcolor::blink << termcolor::on_color<78, 88, 65><<" ⚔️ " << termcolor::reset;
            }
    
        }
        cout<<"\n";
    }

    cout << termcolor::bold << "\n Code :\n " << termcolor::reset 
         << termcolor::bold << termcolor::on_color<78, 88, 65> << " $ " << termcolor::reset << ": vous | " 
         << termcolor::bold << termcolor::on_color<78, 88, 65> << termcolor::color<21, 8, 75> << " M " << termcolor::reset << ": monster   | "
         << termcolor::bold << termcolor::on_color<78, 88, 65><< termcolor::color<185, 63, 215> << " * " << termcolor::reset << ": amulette | "
         << termcolor::on_color<78, 88, 65> << "   " << termcolor::reset << ": vide | "
         << termcolor::bold << termcolor::on_color<78, 88, 65> << termcolor::green << " € " << termcolor::reset << ": tas de pièces\n " 
         << termcolor::on_color<70, 64, 9> << "   " << termcolor::reset << ": mur  | "
         << termcolor::on_color<125, 27, 27> << "   " << termcolor::reset  << ": extérieur | "    
         << termcolor::on_color<78, 88, 65> << " ⚔️ " << termcolor::reset  << ": bataille en cours    | "
         << termcolor::bold << termcolor::on_color<78, 88, 65> << termcolor::color<240, 230, 140> << " ^ " << termcolor::reset << ": sortie \n\n";
}

