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
        //void importGround(const string &filename);
        void addElementToGround(const position &p,std::unique_ptr<groundElement> element);
        void removeElement(const position &p);
        void setSize(int length,int width); 
        const std::vector<std::vector<std::unique_ptr<groundElement>>> & getElementsTable() const;
        void display(const viewManager& view) const; 
        void putElement(const position &oldPos,const position&newPos);



        char typeOf(const position &pos) const;
        position getAdventurerPosition() const;
        int getNbColumns() const;
        int getNbLines() const;

    private:
        int d_nbLines; 
        int d_nbColumns; 
        std::vector<std::vector<std::unique_ptr<groundElement>>> d_groundElementsTab;

};




#endif //FIELD_H_INCLUDED