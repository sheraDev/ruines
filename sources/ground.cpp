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
#include "outside.h"
#include "door.h"

#include "viewManager.h"
#include <fstream>



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

const std::vector<std::unique_ptr<groundElement>> &ground::getElementsTable() const
{
    return d_groundElementsTab;
}

//B= monstre aveugle, A= amulet, P=adventurer, S = monstre voyant , W= mur, E=empty

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
    return t;

}

position ground::posOf(int indice) const
{
    auto e= d_groundElementsTab[indice].get();
    return e->getPosition();
}



//RECHERCHE LA POSITION DE L AVENTURIER  
//UPDATED OK
position  ground::getAdventurerPosition() const  
{
   //UPDATE
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


//OK
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

//OK
//indice de l'element : pk pas lui passer lelement direct a voir
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



//OK
void ground::setSize(int length,int width) 
{
    d_nbColumns = length;  //longueur
    d_nbLines = width;   //largeur   
} 




//updated ok
void ground::addElementToGround(std::unique_ptr<groundElement> element)
{
    d_groundElementsTab.push_back(std::move(element));
}


//update ok

void ground::removeElement(int indice)
{
    d_groundElementsTab.erase(d_groundElementsTab.begin() + indice);

  //SUPPRIMER L ELEMENT A LA POSITION P DU TERRAIN

    /*if(d_groundElementsTab[p.getLine()][p.getColumn()].get() !=nullptr)
    {
        d_groundElementsTab[p.getLine()][p.getColumn()].reset();
    }*/

    //UPDATE

    //Recherche de l element correspondant à la pos ET au type (un seul possible)
    /*
    for(int i=0;i<d_groundElementsTab.size();i++)
    {
        char typeElmt = typeOf(i);
        if( typeElmt==type) // MTNT ON SAIS QUE LE TYPE DE LA CASE EST EGAL A TYPE
        {            
            groundElement* element = d_groundElementsTab[i].get();
            position pos;

            if(type=='B')
            {
                blindMonster* bm = dynamic_cast<blindMonster*>(element);
                pos= {bm->getPosition()};
            }
            else if(type=='A')
            {
                amulet* am = dynamic_cast<amulet*>(element);
                pos= {am->getPosition()};
            }
            else if(type=='P')
            {
                adventurer* adv = dynamic_cast<adventurer*>(element);
                pos= {adv->getPosition()};
                
            }
            else if(type=='S')
            {
                smartMonster* s = dynamic_cast<smartMonster*>(element);
                pos= {s->getPosition()};

            }
            else if(type=='W')
            {
                wall* w = dynamic_cast<wall*>(element);
                pos= {w->getPosition()};
            }
            
            //jai mtnt la pos

            if(pos.getColumn()==p.getColumn() && pos.getLine()==pos.getLine())
            {
                //supression de l element indice i = degager du tableau
                d_groundElementsTab.erase(d_groundElementsTab.begin() + i);

                // rien a fair avc les *
            }

            
            
        }
    }*/
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
    
    cout<<"\n Code :\nS= a smart monster \nB = a blind monster \nW= a wall \nE= empty case\nA= Amulet\nD = door\nO = Outside\nP=Player\n";

    for(int i=0; i<d_nbLines;i++) 
    {
        for(int j=0;j<d_nbColumns;j++) 
        {
            do{
                cout<<"Enter a caracter for the position "<<i<<","<<j<<":";
                cin >>l;
            }while (!(l=='S' || l=='B' || l=='W'|| l=='E'||l=='A'|| l=='P' || l=='D'||l=='O'));

            position pos{i,j};

            if(l=='S') //Monstre voyant a la case [i][j]
            {
                auto p = std::make_unique<smartMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='B') //Monstre aveugle à la case [i][j]
            {
                auto p = std::make_unique<blindMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='W') //Mur a la case [i][j]
            {
                auto p = std::make_unique<wall>(pos);
                addElementToGround(std::move(p));
            }
            else if(l=='A') //Amulette à la case [i][j]
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
            else if(l=='O')
            {
                auto p = std::make_unique<outside>(pos);
                addElementToGround(std::move(p));
            }
        }
    }
}

void ground::importGround(std::istream &ist)  //importer un terrain
{
    
    int nbcol, nbl;
    char elem;

    ist>>nbl>>nbcol;
    

        int cptl=0; 
        int cptc=0;
        setSize(nbl,nbcol);

        while(!ist.eof() && cptl<d_nbLines && cptc<d_nbColumns)
        {
            position pos{cptl,cptc};
            ist>>elem;

            if(elem=='S') //Monstre voyant a la case [i][j]
            {
                auto p = std::make_unique<smartMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(elem=='B') //Monstre aveugle à la case [i][j]
            {
                auto p = std::make_unique<blindMonster>(pos);
                addElementToGround(std::move(p));
            }
            else if(elem=='W') //Mur a la case [i][j]
            {
                auto p = std::make_unique<wall>(pos);
                addElementToGround(std::move(p));
            }
            else if(elem=='A') //Amulette à la case [i][j]
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
        std::ofstream fichier("Terrain");
        fichier<<d_nbLines<<" "<<d_nbColumns<<"\n";

        for(int i=0;i<d_nbLines;i++)
        {
            for(int j=0; j<d_nbColumns;j++)
            {
                p={i,j};
                indice = indicePos(p);
                //auto elem = getElementsTable()[indice].get();
                t = typeOf(indice);

                fichier<<t<<" ";

                /*if(t=='E')
                {
                    fichier<<'E';
    
                }
                else if(t=='P')
                {
                    fichier<<'P';
                }
                else if(t=='A')
                {
                    fichier<<'A';

                }
                else if(t=='B')
                {
                    fichier<<'B';
                }
                else if(t=='S')
                {
                    fichier<<'S';

                }
                else if(t=='W')
                {
                    fichier<<'W';

                }
                else if(t=='O')
                {
                    fichier<<'O';

                }
                else if(t=='D')
                {

                }*/


            }
            fichier<<"\n";

                
        
        }
    }
    





//update nouv fonction
//1 elme stocke sa pos, donc on me passe un elem et son type et je renvois
// sa pos d_pos
/*
position ground::getPositionElementType(char type,const std::unique_ptr<groundElement> &e) const
{
     position pos;

    if(type=='B')
    {
        blindMonster* bm = dynamic_cast<blindMonster*>(e.get());
        pos= {bm->getPosition()};
    }
    else if(type=='A')
    {
        amulet* am = dynamic_cast<amulet*>(e.get());
        pos= {am->getPosition()};
    }
    else if(type=='P')
    {
        adventurer* adv = dynamic_cast<adventurer*>(e.get());
        pos= {adv->getPosition()};
        
    }
    else if(type=='S')
    {
        smartMonster* s = dynamic_cast<smartMonster*>(e.get());
        pos= {s->getPosition()};

    }
    else if(type=='W')
    {
        wall* w = dynamic_cast<wall*>(e.get());
        pos= {w->getPosition()};
    }
    return pos;
}*/


//tab d'indices des elemts qui ont la position p
std::vector<int> ground::getIndicePos(const position &p) const
{
    int indice=0;
    position pos;
    std::vector<int>T;
    //T.reserve(d_groundElementsTab.size());

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

//A UTILISER SEULEMENT SI ON EST SUR QU'IL YA AU PLUS UN SEUL ELMT A LA POS P
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
    return -1; //Si personne dans le tableau nest a cette pos

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




