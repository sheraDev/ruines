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
        ground();
        void buildGround();
        void importGround(std::istream &ist);
        void exportGround();

        void addElementToGround(std::unique_ptr<groundElement> element);
        void removeElement(int indice);
        void setSize(int length,int width); 
        const std::vector<std::unique_ptr<groundElement>> & getElementsTable() const;
        
        //void display(const viewManager& view) const; 
        void display(std::unique_ptr<viewManager> &view);


        //renvoie les indice de tt les elmt a pos donnée
        std::vector<int> getIndicePos(const position &p) const; 


        //seulement qd on est sur qu'il ya un seul element a la position p
        int indicePos(const position &p) const; 
                                                

        int nbElmtsPos(const position &p) const;
       
        //position getPositionIndice(int indice); //position de la case indice

        int getIndiceElmt(const position &p,char type) const; //indice de lelmt de type et position donnee = 1 seule possiblilité

        //position avec un type et un elmt : inutile ?
        //position getPositionElementType(char type,const std::unique_ptr<groundElement> &e) const;
        
        position getAdventurerPosition() const; //position de laventurier 

        char typeOf(int indice) const; //type de la case indice
        position posOf(int indice) const; //position de lelmt case indice

        int getIndiceAdventurer() const; //indice de laventurier

        int getNbColumns() const;
        int getNbLines() const;

    private:
        int d_nbLines; 
        int d_nbColumns; 

      std::vector<std::unique_ptr<groundElement>> d_groundElementsTab;

};




#endif //GROUND_H_INCLUDED