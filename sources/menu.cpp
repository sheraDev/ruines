#include "menu.h"
#include "game.h"
#include "ground.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*

ground menu::fieldChoice()
{
    cout<<"- - - - - WELCOME TO ANGBAND - - -  -"<<endl;
    int type;
    do{
        cout<<"Choose how do you want to create the field: \n";
        cout<<"1- Generate manually \n 2- Import from a file \n";
        cin>>type;
    }
    while(type!=1 || type !=2);

    ground g{}; //CREATION D UN TERRAIN

    if(type==1) // generer manuellement
    {
        f.buildField();
    }
    else{    //importer
        string fileName;
        cout<<"Enter the name of the file to import :";
        cin>>fileName;
        f.importField(fileName);

    }

    return f;  //RENVOIE LE TERRAIN

}*/