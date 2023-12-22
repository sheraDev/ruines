#ifndef GROUND_H_INCLUDED
#define GROUND_H_INCLUDED
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>

/*
#include "groundElement.h"
#include "monster.h"
#include "amulet.h"
#include "adventurer.h"
#include "smartMonster.h"
#include "blindMonster.h"
#include "wall.h"*/

#include "groundElement.h"
#include "istream"
#include <iostream>
#include <istream>
//class groundElement;
class monster;
class amulet;
class smartMonster;
class blindMonster;
class wall;
class position;
class adventurer;
class character;
class viewManager;



using std::string;


// TERRAIN DE JEU

class ground
{
    public:
        ground(); //pas de test
        ground(int nbl,int nbc); //test ok
        void buildGround();
        void importGround(std::istream &ist);
        void exportGround();


        //test ok
        void addElementToGround(std::unique_ptr<groundElement> element); 
        
        //test ok
        void removeElement(int indice); 
        
        //test ok
        void setSize(int length,int width);  
        
        //pas de test
        const std::vector<std::unique_ptr<groundElement>> & getElementsTable() const;
        
        //pas de test
        void display(std::unique_ptr<viewManager> &view);


        //renvoie les indice de tt les elmt a pos donnée
        std::vector<int> getIndicePos(const position &p) const;  //test ok


        //seulement qd on est sur qu'il ya un seul element a la position p
        int indicePos(const position &p) const;  //test ok
                                                

        //test ok
        int nbElmtsPos(const position &p) const;
        
        //test ok
        int getIndiceElmt(const position &p,char type) const; //indice de lelmt de type et position donnee = 1 seule possiblilité

        
        //test ok
        position getAdventurerPosition() const; //position de laventurier 

        //test ok
        char typeOf(int indice) const; //type de la case indice
        
        //test ok
        position posOf(int indice) const; //position de lelmt case indice

        //test ok
        int getIndiceAdventurer() const; //indice de laventurier
       
        int getNbColumns() const; //test ok
        int getNbLines() const;   //test ok
        int getNbTotalElmts() const; //test ok

        int aleatNumber(int n1,int n2);
        double aleatDouble() const;

    private:
        int d_nbLines; 
        int d_nbColumns; 

      std::vector<std::unique_ptr<groundElement>> d_groundElementsTab;

};




#endif //GROUND_H_INCLUDED