#ifndef GROUND_H_INCLUDED
#define GROUND_H_INCLUDED
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>


#include "groundElement.h"
#include "istream"
#include <iostream>
#include <istream>
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
    
        //CONSTRUCTEURS
        ground(); 
        ground(int nbl,int nbc); 
        
        //GESTION TERRAIN
        void buildGround();
        void importGround(std::istream &ist);
        void exportGround();
        void setSize(int length,int width);
        void display(std::unique_ptr<viewManager> &view);
  

        //GESTION ELEMENTS TERRAIN
        void addElementToGround(std::unique_ptr<groundElement> element); 
        void removeElement(int indice); 
        const std::vector<std::unique_ptr<groundElement>> & getElementsTable() const;
        std::vector<int> getIndicePos(const position &p) const;  
        int indicePos(const position &p) const;  
        int nbElmtsPos(const position &p) const;
        int getIndiceElmt(const position &p,char type) const; 
        position getAdventurerPosition() const;  
        char typeOf(int indice) const; 
        position posOf(int indice) const; 

        //GETTERS
        int getIndiceAdventurer() const; 
        int getNbColumns() const; 
        int getNbLines() const;   
        int getNbTotalElmts() const;

        //ALEATOIRES
        int aleatNumber(int n1,int n2); 
        double aleatDouble() const;

    private:
    
        int d_nbLines; 
        int d_nbColumns; 
        std::vector<std::unique_ptr<groundElement>> d_groundElementsTab;

};




#endif //GROUND_H_INCLUDED