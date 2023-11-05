#include <iostream>

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

#include "viewManager.h"


using std::cout;
using std::cin;
using std::ifstream;


ground::ground(){}

int ground::getNbColumns() const
{
    return d_nbColumns;
}
int ground::getNbLines() const
{
    return d_nbLines;
}

const std::vector<std::vector<std::unique_ptr<groundElement>>> &ground::getElementsTable() const
{
    return d_groundElementsTab;
}

//B= monstre aveugle, A= amulet, P=adventurer, S = monstre voyant , W= mur, E=empty
char  ground::typeOf(const position &pos) const
{
   
    auto e= d_groundElementsTab[pos.getLine()][pos.getColumn()].get();
    char t;

    if(dynamic_cast<blindMonster*>(e))
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
    else if(e==nullptr)
    {
        t= 'E';
    }
    return t;

}


//RECHERCHE LA POSITION DE L AVENTURIER
position  ground::getAdventurerPosition() const
{
    for(int i=0;i<getNbLines();i++)
    {
        for(int j=0;j<getNbColumns();j++)
        {
            if(d_groundElementsTab[i][j].get()!=nullptr && dynamic_cast<adventurer*>(d_groundElementsTab[i][j].get()))
            {
                return position{i,j};
            }
        }
    }
    return {-1,-1};
}




void ground::setSize(int length,int width) 
{
    d_nbColumns = length;  //longueur
    d_nbLines = width;   //largeur   

    d_groundElementsTab.resize(width);
    for(int i=0;i<d_nbLines;i++)
    {
        d_groundElementsTab[i].resize(d_nbColumns);
    }

} 


//MET DANS OLD POS CE QUE CONTIENT NEW POS
void ground::putElement(const position &oldPos,const position&newPos)
{
    int oldLine = oldPos.getLine(),oldCol = oldPos.getColumn();
    int newLine = newPos.getLine() , newCol = newPos.getColumn();
    
    d_groundElementsTab[oldLine][oldCol] = std::move( d_groundElementsTab[newLine][newCol]);
}



void ground::addElementToGround(const position &p,std::unique_ptr<groundElement> element)
{
    //AJOUTER L ELEMENT PASSE EN PARAMETRE AU TERRAIN A LA POSITION P
    d_groundElementsTab[p.getLine()][p.getColumn()] = std::move(element); 
}

void ground::removeElement(const position &p)
{
    //SUPPRIMER L ELEMENT A LA POSITION P DU TERRAIN

    if(d_groundElementsTab[p.getLine()][p.getColumn()].get() !=nullptr)
    {
        d_groundElementsTab[p.getLine()][p.getColumn()].reset();
    }
}




void ground::buildGround()   //creer un terrain manuellement
{
    cout<<"\n ----- MANUALLY GENERATION FIELD -------\n";

    int c,li;
    do{
        cout<<"Enter a number of columns : \n"; cin>>c;  //longueur
        cout<<"Enter a numer of lines : "; cin>>li;  //largeur
    }
    while(c<=0 || li<=0);

    d_nbColumns=c;
    d_nbLines=li;

    char l;
    setSize(d_nbColumns,d_nbLines);
    
    cout<<"\n Code :\nS= a smart monster \nB = a blind monster \nW= a wall \nE= empty case\nA= Amulet \nP=Player\n";

    for(int i=0; i<d_nbLines;i++) 
    {
        for(int j=0;j<d_nbColumns;j++) 
        {
            do{
                cout<<"Enter a caracter for the position "<<i<<","<<j<<":";
                cin >>l;
            }while (!(l=='S' || l=='B' || l=='W'|| l=='E'||l=='A'|| l=='P'));

            position pos{i,j};
            
            if(l=='S') //Monstre voyant a la case [i][j]
            {
                auto p = std::make_unique<smartMonster>(pos);
                addElementToGround(pos,std::move(p));
            }
            else if(l=='B') //Monstre aveugle à la case [i][j]
            {
                auto p = std::make_unique<blindMonster>(pos);
                addElementToGround(pos,std::move(p));
            }
            else if(l=='W') //Mur a la case [i][j]
            {
                auto p = std::make_unique<wall>(pos);
                addElementToGround(pos,std::move(p));
            }
            else if(l=='A') //Amulette à la case [i][j]
            {
                auto p = std::make_unique<amulet>(pos);
                addElementToGround(pos,std::move(p));            
            }
            else if(l=='P') //Personnage
            {
                auto p = std::make_unique<adventurer>(pos);
                addElementToGround(pos,std::move(p));
            }
        }
    }
}

/*void ground::importGround(const string &filename)  //importer un terrain
{
    std::ifstream ifs(filename);
    if (!ifs.is_open()) 
    {
       cout << "A problem has occurred.\n";
       return;
    }
}*/


void ground::display(const viewManager& view) const
{
    view.displayGround(*this);
}





