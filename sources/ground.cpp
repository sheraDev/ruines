#include <iostream>
#include <random>

#include "ground.h"
#include "position.h"
#include "groundElement.h"
#include "character.h"
#include "monster.h"
#include "smartMonster.h"
#include "blindMonster.h"
#include "adventurer.h"
#include "wall.h"
#include "amulet.h"
#include "outside.h"
#include "door.h"
#include "money.h"

#include "viewManager.h"
#include <fstream>



using std::cout;
using std::cin;
using std::ifstream;


ground::ground(){}

ground::ground(int nbl,int nbc):d_nbLines{nbl},d_nbColumns{nbc}{}


int ground::getNbColumns() const
{
    return d_nbColumns;
}
int ground::getNbLines() const
{
    return d_nbLines;
}

const std::vector<std::unique_ptr<groundElement>> &ground::getElementsTable() const
{
    return d_groundElementsTab;
}

int ground::getNbTotalElmts() const
{
    return d_groundElementsTab.size();
}

int ground::aleatNumber(int n1,int n2)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(n1,n2);

    int rdm = distrib(gen);
    return rdm;
}


char  ground::typeOf(int indice) const
{
   
    auto e= d_groundElementsTab[indice].get();
    char t;

    if(indice==-1)  
    {
        t= 'E';
    }
    else if(dynamic_cast<blindMonster*>(e))
    {
        t= 'B';
    }
    else if(dynamic_cast<amulet*>(e))
    {
        t= 'A';
    }
    else if(dynamic_cast<adventurer*>(e))
    {
        t= 'P';
    }
    else if(dynamic_cast<smartMonster*>(e))
    {
        t= 'S';
    }
    else if(dynamic_cast<wall*>(e))
    {
        t= 'W';
    }
    else if(dynamic_cast<door*>(e))
    {
        t='D';
    }
    else if(dynamic_cast<outside*>(e))
    {
        t='O';
    }
    else if(dynamic_cast<money*>(e))
    {
        t='M';
    }
    return t;

}

position ground::posOf(int indice) const
{
    auto e= d_groundElementsTab[indice].get();
    return e->getPosition();
}


position  ground::getAdventurerPosition() const  
{
    for(int i=0;i<d_groundElementsTab.size();i++)
    {
        groundElement* element = d_groundElementsTab[i].get();
        adventurer* adv = dynamic_cast<adventurer*>(element);

         if (adv) {
            position padv{ adv->getPosition()};
            return padv;
         }
    }

    return {-1,-1};
}


int ground::getIndiceAdventurer() const
{
    for(int i=0;i<d_groundElementsTab.size();i++)
    {
        if(typeOf(i)=='P')
        {
            return i;
        }
    }
    return -1;
}

int ground::getIndiceElmt(const position &p,char type) const
{
    for(int i=0;i<d_groundElementsTab.size();i++)
    {
        if(typeOf(i)==type && posOf(i).getColumn()==p.getColumn() && posOf(i).getLine()==p.getLine())
        {
            return i;
        }
    }
    return 0;
}




void ground::setSize(int length,int width) 
{
    d_nbColumns = length;  
    d_nbLines = width;     
} 


void ground::addElementToGround(std::unique_ptr<groundElement> element)
{
    d_groundElementsTab.push_back(std::move(element));
}



void ground::removeElement(int indice)
{
    d_groundElementsTab.erase(d_groundElementsTab.begin() + indice);
}

double ground::aleatDouble() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distrib(0.0, 10.0);
    double nombre = distrib(gen) / 10.0;
    return round(nombre * 10.0) / 10.0;
}





void ground::buildGround()   //creer un terrain manuellement
{
  cout<<"\n +------------------------- GENERATION MANUELLE DE TERRAIN -----------------------+\n";


    int c,li;
    do{
        cout<<"Enter a number of columns : \n"; cin>>c;  
        cout<<"Enter a numer of lines : "; cin>>li;  
    }
    while(c<=0 || li<=0);

    d_nbColumns=c;
    d_nbLines=li;

    char l;
    setSize(d_nbColumns,d_nbLines);
    
    cout<<"\n Code :\nS= a smart monster \nB = a blind monster \nW= a wall\nM=money \nE= empty case\nA= Amulet\nD = door\nO = Outside\nP=Player\n";

    for(int i=0; i<d_nbLines;i++) 
    {
        for(int j=0;j<d_nbColumns;j++) 
        {
            do{
                cout<<"Enter a caracter for the position "<<i<<","<<j<<":";
                cin >>l;
            }while (!(l=='S' || l=='B' || l=='W'|| l=='E'||l=='A'|| l=='P' || l=='D'||l=='O' || l=='M'));

            position pos{i,j};

            if(l=='S') //Smart monster
            {
                //tirer ses pv, pf et habilité aleatoirement
                int pf = aleatNumber(100,200);
                int pv = aleatNumber(700,1800);
                double hab = aleatDouble();
                auto p = std::make_unique<smartMonster>(pos,pf,pv,hab);
                addElementToGround(std::move(p));
            }
            else if(l=='B') //Blind monster
            {
                int pf = aleatNumber(80,300);
                int pv = aleatNumber(500,1000);
                double hab = aleatDouble();
                auto p = std::make_unique<blindMonster>(pos,pf,pv,hab);
                addElementToGround(std::move(p));
            }
            else if(l=='W') //Mur 
            {
                auto p = std::make_unique<wall>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='A') //Amulette 
            {
                auto p = std::make_unique<amulet>(pos);
                addElementToGround(std::move(p));            
            }
            else if(l=='P') //Personnage
            {
                auto p = std::make_unique<adventurer>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='D') //Porte
            {
                auto p = std::make_unique<door>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='O') //Case en dehors
            {
                auto p = std::make_unique<outside>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='M') //Tas de pièces
            {
                int val = aleatNumber(1,20);
                auto p = std::make_unique<money>(pos,val);
                addElementToGround(std::move(p));
            }
        }
    }
}

void ground::importGround(std::istream &ist)  
{
    
    int nbcol, nbl;
    char elem;

    ist>>nbl>>nbcol;


    int cptl=0; 
    int cptc=0;
    setSize(nbcol,nbl);

    while(!ist.eof() && cptl<d_nbLines && cptc<d_nbColumns)
    {
        position pos{cptl,cptc};
        ist>>elem;

        if(elem=='S') //Smart monster
        {
            int pf = aleatNumber(50,120);
            int pv = aleatNumber(500,1000);
            double hab = aleatDouble();
            auto p = std::make_unique<smartMonster>(pos,pf,pv,hab);
            addElementToGround(std::move(p));
        }
        else if(elem=='B') //Blind Monster
        {
            int pf = aleatNumber(50,120);
            int pv = aleatNumber(500,1000);
            double hab = aleatDouble();
            auto p = std::make_unique<blindMonster>(pos,pf,pv,hab);
            addElementToGround(std::move(p));
        }
        else if(elem=='W') //Mur 
        {
            auto p = std::make_unique<wall>(pos);
            addElementToGround(std::move(p));
        }
        else if(elem=='A') //Amulette 
        {
            auto p = std::make_unique<amulet>(pos);
            addElementToGround(std::move(p));  
        
        }
        else if(elem=='P') //Personnage
        {
            auto p = std::make_unique<adventurer>(pos);
            addElementToGround(std::move(p));

        }
        else if(elem=='D') //Porte
        {
            auto p = std::make_unique<door>(pos);
            addElementToGround(std::move(p));
        }
        else if(elem=='O') //Dehors
        {
            auto p = std::make_unique<outside>(pos);
            addElementToGround(std::move(p));
        }
        else if(elem=='M') //Pieces
        {
            int val = aleatNumber(1,20);
            auto p = std::make_unique<money>(pos,val);
            addElementToGround(std::move(p));
        }

        cptc++;

        if(cptc==nbcol)
        {
            cptc=0;
            cptl++;
        }

    }


}

void ground::exportGround()
{
    position p;
    int nbElmt,indice;
    char t;
    std::ofstream fichier("Terrain.txt");
    fichier<<d_nbLines<<" "<<d_nbColumns<<"\n";

    for(int i=0;i<d_nbLines;i++)
    {
        for(int j=0; j<d_nbColumns;j++)
        {
            p={i,j};
            indice = indicePos(p);
            t = typeOf(indice);

            fichier<<t<<" ";



        }
        fichier<<"\n";
    }
}
    



//tab d'indices des elemts qui ont la position p
std::vector<int> ground::getIndicePos(const position &p) const
{
    int indice=0;
    position pos;
    std::vector<int>T;

    for(const auto &elem : d_groundElementsTab)
    {
        pos = elem->getPosition();

        if( (pos.getColumn()==p.getColumn()) && (pos.getLine()==p.getLine()))
        {
            T.push_back(indice);
        }

        indice++;
    }
    
    return T;
}

int ground::indicePos(const position &p) const
{
    int indice=0;
    position pos;
   
    for(const auto &elem : d_groundElementsTab)
    {
        pos = elem->getPosition();

        if( pos.getColumn()==p.getColumn() && pos.getLine()==p.getLine())
        {
            return indice;
        }

        indice++;
    }
    return -1; //Si personne dans le tableau n'est a cette pos

}


int ground::nbElmtsPos(const position &p) const
{
    std::vector<int>elm= getIndicePos(p);
    return elm.size();
}


void ground::display(std::unique_ptr<viewManager> &view) 
{
    view->displayGround(*this);
}




