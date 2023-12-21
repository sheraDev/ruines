#include "game.h"
#include "ground.h"
#include "groundElement.h"
#include "CLIView.h"
#include "adventurerMoveManager.h"
#include "character.h"
#include "smartMonster.h"
#include "blindMonster.h"
#include "adventurer.h"
#include "smartMonsterMoveManager.h"
#include "blindMonsterMoveManager.h"
#include <memory>

#include <iostream>
#include <istream>
#include <fstream>
#include <cstdlib>




game::game(){}

void game::afficherInfosMonstres(const monster *m,char type) 
{
    std::cout<<"Infos du monstre à la case "<<m->getPosition().getLine()<<","<<m->getPosition().getColumn() <<":\n";
    std::cout<<"Type :";type=='S'?std::cout<<"Smart Monster\n":std::cout<<"Monstre aveugle\n";

    std::cout<<"Points de vie : "<<m->lifePoints()<<"\n";
    std::cout<<"Points de force : "<<m->forcePoints()<<"\n";
    std::cout<<"Pourcentage d'habilité : "<<m->getHability()<<"\n";
    std::cout<<"\n";
}



int game::choixView()
{
   int choix;
   do
   {
    std::cout<<"Quel type d'interface voulez vous ?\n1-Ligne de commandes\n";
    std::cin>>choix;
    
   } while (!(choix==1));
   
    
    return choix;
}

std::unique_ptr<viewManager> game::createView(int choix)
{
    
    if(choix==1)
    {
        auto v=std::make_unique<CLIView>();
        return v;
    }
    else
    {
        return 0;
    }
}



void game::chargerGround(ground &g)
{
    int choix;
    std::string nomFic;
    do
    {
        std::cout<<"Comment voulez-vous construire le terrain ? \n1-Construire manuellement\n2-Importer depuis un fichier\n";
        std::cin>>choix;
    }
    while(!(choix==1||choix==2));

    switch (choix)
    {
    case 1:
        g.buildGround();
        std::cout<<"Voulez vous sauvegarder le terrain dans un fichier ? O/N :";
        char rep;std::cin>>rep;
        if(rep=='O')
        {
            g.exportGround();
            std::cout<<"Fichier sauvegardé avec succès \n";
        }
        break;
    
    case 2:
        std::cout<<"Entrer le nom du fichier :"; std::cin>>nomFic;
        std::ifstream fic(nomFic);
        if(fic)
        {
            g.importGround(fic);
        }
        else
        {
            std::cout<<"Erreur de nom \n";
            return;
        }

        break;
    }


}





void game::play() 
{
    bool partie = true;
    bool win = false;
    int direction;
    int tour=1;

    int choixInterface = choixView();
    auto v = move(createView(choixInterface));

    ground g;
    this->chargerGround(g);
    //g.display(v);
    system("clear");



    

    while( partie && !win )
    {
       // std::cout<<"\033[H\033[J"<<std::flush;

       //   system("clear");

        std::vector<std::vector<int>> tabInfosMonster;

        //0 : position . d_x
        //1 position.d_y
        //1 : info
        //2 : type
        //3 PV
        //4 pf
        //5 pourcentage dhabilité
    

        std::cout<<"-------------- Tour n°"<<tour<<"------------------\n";

        g.display(v);
        int indiceAdv = g.getIndiceAdventurer();
        auto adv= dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get());

        int rep;
        
       
            /*do
            {
                std::cout<<"Que voulez vous faire ? 1)Utiliser la bourse 2)Me déplacer :"; std::cin>>rep;
            } while (!(rep==1)||(rep==2));

            if(rep==1) //utiliser la bourse
            {
                int montantVoulu;
                int montantBourse = adv->getBourse();
                int choixRep;
                do
                {
                    std::cout<<"Vous avez : "<<montantBourse<<" pieces.Entrer le montant que vous voulez utiliser : ";
                    std::cin>>montantVoulu;
                }while(montantVoulu<=0 || montantVoulu>montantBourse);

                do
                {
                    std::cout<<"Que voulez vous réparer ? 1)Armure 2)Epee :";
                    std::cin>>choixRep;
                } while (!(choixRep==1 || choixRep==2));

                if(choixRep==1) //Réparer armure
                {
                    adv->addToArmorSolidity(montantVoulu);
                    adv->removeFromBourse(montantVoulu);
                    std::cout<<"Votre armure a maintenant : "<<adv->getArmor().getSolidity()<<" points.\n";
                }
                else if(choixRep==2)
                {
                    adv->addToSwordSolidity(montantVoulu);
                    adv->removeFromBourse(montantVoulu);
                    std::cout<<"Votre épee a maintenant : "<<adv->getSword().getSolidity()<<" points.\n";
                }
                

            }*/
          
        
        

        
        
        //L AVENTURIER SE DEPLACE
        do
        {   std::cout<<"Entrer la direction où vous souhaitez aller: \n";
            std::cout<<"1 2 3\n4 ⑤ 6\n7 8 9\n ";
            std::cin >>direction;
        }
        while(!(direction==1 || direction==2 || direction==3 || direction==4||direction==5||direction==6||direction==7 ||direction==8 ||direction==9));
        
        position posAdv = g.getAdventurerPosition();
        adventurerMoveManager advMover{posAdv};
        advMover.move(g,direction);

        

        if(adv->isOutWithAmulet())
        {
            win = true;
        }
        if(!win)
        {
            std::cout<<"L'aventurier s'est déplacé :\n";
            g.display(v);
        }
        else
        {
            std::cout<< "Vous avez gagné ! \n";
            break;
        }

        

        system("clear");

        //LES MONSTRES SE DEPLACENT
        for(int i=0;i<g.getElementsTable().size();i++)
        {   

            if(g.typeOf(i)=='S') //SMART MONSTER
            {
                //std::cout<<" Au tour du S ! (dans game) \n";
                auto monster = dynamic_cast<smartMonster*>(g.getElementsTable()[i].get());
                position posMonster = monster->getPosition();
                smartMonsterMoveManager monsterMover{posMonster};

                
                monsterMover.move(g);
                /*std::cout<<"Déplacement d'un monstre : \n";
                g.display(v);*/
                if(monster->isAtOneCaseAdv(g))
                {   
                    //Infos du monstre
                    std::vector<int>tabInfo;
                    tabInfo.reserve(6);
                    tabInfo.push_back(monster->getPosition().getLine());
                    tabInfo.push_back(monster->getPosition().getColumn());
                    tabInfo.push_back('S');
                    tabInfo.push_back(monster->lifePoints());
                    tabInfo.push_back(monster->forcePoints());
                    tabInfo.push_back(monster->getHability());

                    //Rajouter dans le tab des monstres
                    tabInfosMonster.push_back(tabInfo);
                }
    
            }
            else if(g.typeOf(i)=='B') //MONSTRE AVEUGLE
            {
                //std::cout<<" Au tour du B ! (dans game) \n";

                auto monster = dynamic_cast<blindMonster*>(g.getElementsTable()[i].get());
                position posMonster =monster->getPosition();
                blindMonsterMoveManager monsterMover{posMonster};
                monsterMover.move(g);

                //AFFICHAGE DE TESTS
                /*std::cout<<"Déplacement d'un monstre : \n";
                g.display(v);*/
                if(monster->isAtOneCaseAdv(g))
                {
                    //afficherInfosMonstres(monster,'B');
                    //Infos du monstre
                    std::vector<int>tabInfo;
                    tabInfo.reserve(6);
                    tabInfo.push_back(monster->getPosition().getLine());
                    tabInfo.push_back(monster->getPosition().getColumn());
                    tabInfo.push_back('B');
                    tabInfo.push_back(monster->lifePoints());
                    tabInfo.push_back(monster->forcePoints());
                    tabInfo.push_back(monster->getHability());

                    //Rajouter dans le tab des monstres
                    tabInfosMonster.push_back(tabInfo);

                }
            }
            
        }

        
            std::cout<<"\nTous les monstres se sont déplacés, réaffichage du terrain : \n";
            g.display(v);


            
            if(adv->lifePoints()>0)
            {


                std::cout<<"----------Fin du tour "<<tour<<"----------\n\n";

                //AFFICHAGE DES INFOS DES MONSTRES
                std::cout<<"Infos des monstres  : \n";

                std::cout<<" +--------------------------------------------------------------------------+\n";
                std::cout<<" | Ligne  |  Colonne   |    Type     |   PV       |     PF       | Hability |\n";
                std::cout<<" +--------------------------------------------------------------------------+\n";

                for(int i=0;i<tabInfosMonster.size();i++) //parcours des monstres
                {
                    std::cout<<" |    ";
                    for(int j=0;j<tabInfosMonster[i].size();j++)
                    {
                        if(j==2)
                        {
                            std::cout<<(char)tabInfosMonster[i][j]<<"         ";
                        }
                        else 
                            std::cout<<tabInfosMonster[i][j]<<"           ";
                    }
                    std::cout<<"\b\b\b\b\b|\n";
                }
                std::cout<<" +--------------------------------------------------------------------------+\n";



            //AFFICHAGE DES POINTS DE L'ADV

                std::cout<<"Infos de l'aventurier  : \n";

                std::cout<<" +----------------------------------------------------------------------------+\n";
                std::cout<<" | PV  |  Points épée   |    Points armure     |     Bourse      |    Amulet  |\n";
                std::cout<<" +----------------------------------------------------------------------------+\n";
               
                std::cout<<" | ";
                std::cout<< adv->lifePoints() <<"        ";
                std::cout<<adv->getSword().getSolidity()<<"                 ";
                std::cout<<adv->getArmor().getSolidity()<<"                    ";
                std::cout<<adv->getBourse()<<"         ";
                adv->hasAmulet()?std::cout<<"     Oui    |":std::cout<<"     Non    |";
                std::cout<<"\n +----------------------------------------------------------------------------+\n";

                std::cout<<"\n";


                tour++;
            }
            else
            {
                std::cout<<"Vous etes mort.Fin de la partie \n";
                partie= false;
            }


    }


}



