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
#include "monster.h"

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
    std::ifstream fic;
        do{
            std::cout<<"Entrer le nom du fichier :"; std::cin>>nomFic;
            fic.open(nomFic.c_str()); 
        } while (!fic.is_open()); 
        g.importGround(fic);
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
   //   system("clear");

        std::vector<std::vector<int>> tabInfosMonster;

        std::vector<monster*> tabMonstres;

        std::cout<<"+-------------------------------------- Tour n°"<<tour<<"--------------------------------------+\n";

        g.display(v);
        int indiceAdv = g.getIndiceAdventurer();
        auto adv= dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get());

        int rep;
        
       
       
        //L AVENTURIER SE DEPLACE
        //do
        //{   
            int depl;

            if(adv->getBourse()>0)
            {

                do
                {
                    std::cout<<"Que voulez vous faire ? \n1)Utiliser la bourse \n2)Me déplacer :\n"; std::cin>>rep;
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
                        std::cout<<"Que voulez vous réparer ? \n1)Armure \n2)Epee :\n";
                        std::cin>>choixRep;
                    } while (!(choixRep==1 || choixRep==2));

                    if(choixRep==1) //Réparer armure
                    {
                        adv->addToArmorSolidity(montantVoulu);
                        adv->removeFromBourse(montantVoulu);
                        std::cout<<"Votre armure a maintenant : "<<adv->getArmor().getSolidity()<<" points.\n";
                    }
                    else if(choixRep==2) //Réparer épée
                    {
                        adv->addToSwordSolidity(montantVoulu);
                        adv->removeFromBourse(montantVoulu);
                        std::cout<<"Votre épee a maintenant : "<<adv->getSword().getSolidity()<<" points.\n";
                    }
                    

                }
                else{
                    depl=1;
                }
            }
            else
            {
                depl=1;
            }


            if(depl==1) //se deplacer
            {
                    do{
                        std::cout<<"Entrer la direction où vous souhaitez aller: \n";
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

                    

                   // system("clear");

                    //LES MONSTRES SE DEPLACENT
                    tabMonstres = deplacerMonstres(g);
                    
                    std::cout<<"\nTous les monstres se sont déplacés, réaffichage du terrain : \n";
                    g.display(v);


                    
                    if(adv->lifePoints()>0)
                    {


                        std::cout<<"+------------------------------------Fin du tour "<<tour<<"------------------------------------+\n\n";

                        //AFFICHAGE DES INFOS DES MONSTRES PROCHES

                        if(tabMonstres.size()>0)
                        {
                            afficherInfosMonstresProches(tabMonstres);
                        }
                        
                
                        //AFFICHAGE DES POINTS DE L'ADV
                        afficherInfosAdv(adv);
                        tour++;
                    }
                    else
                    {
                        std::cout<<"Vous etes mort.Fin de la partie \n";
                        partie= false;
                    }
            }
    }

        //}


    }






std::vector<monster*> game::deplacerMonstres(ground&g)
{
    std::vector<monster*> tabMonstres;
    for(int i=0;i<g.getElementsTable().size();i++)
    {   

        if(g.typeOf(i)=='S') //SMART MONSTER
        {
            auto monster = dynamic_cast<smartMonster*>(g.getElementsTable()[i].get());
            position posMonster = monster->getPosition();
            smartMonsterMoveManager monsterMover{posMonster};
            monsterMover.move(g);
            
            if(monster->isAtOneCaseAdv(g))
            {   
                tabMonstres.push_back(monster);
            }

        }
        else if(g.typeOf(i)=='B') //MONSTRE AVEUGLE
        {
            auto monster = dynamic_cast<blindMonster*>(g.getElementsTable()[i].get());
            position posMonster =monster->getPosition();
            blindMonsterMoveManager monsterMover{posMonster};
            monsterMover.move(g);

            if(monster->isAtOneCaseAdv(g))
            {
                tabMonstres.push_back(monster);
            }
        }
        
    }
    return tabMonstres;

}



void game::afficherInfosAdv(const adventurer*adv)
{
    std::cout<<"Infos de l'aventurier  : \n";

    std::cout<<" +--------------------------------------------------------------------------------+\n";
    std::cout<<" |    PV   |  Points épée   |    Points armure     |     Bourse      |    Amulet  |\n";
    std::cout<<" +--------------------------------------------------------------------------------+\n";

    std::cout<<" | ";
    std::cout<< adv->lifePoints() <<"        ";
    std::cout<<adv->getSword().getSolidity()<<"                 ";
    std::cout<<adv->getArmor().getSolidity()<<"                     ";
    std::cout<<adv->getBourse()<<"         ";
    adv->hasAmulet()?std::cout<<"        Oui    |":std::cout<<"        Non    |";
    std::cout<<" \n +--------------------------------------------------------------------------------+\n";

    std::cout<<"\n";

}

void game::afficherInfosMonstresProches(const std::vector<monster*> &tabMonstres) 
{
    std::cout<<"Infos des monstres proches  : \n";

    std::cout<<" +--------------------------------------------------------------------------------+\n";
    std::cout<<" | Ligne  |  Colonne   |       Type       |    PV       |     PF       | Hability |\n";
    std::cout<<" +--------------------------------------------------------------------------------+\n";

    
    for(int i=0;i<tabMonstres.size();i++)
    {
        std::cout<<" |    ";
        std::cout<<tabMonstres[i]->getPosition().getLine()<<"         ";
        std::cout<<tabMonstres[i]->getPosition().getColumn()<<"          ";

        //type
        if(dynamic_cast<blindMonster*>(tabMonstres[i]))
        {
            std::cout<<"Blind Monster"<<"      ";
        }
        else if(dynamic_cast<smartMonster*>(tabMonstres[i]))
        {
            std::cout<<"Smart Monster"<<"      ";
        }
        std::cout<<tabMonstres[i]->lifePoints()<<"            ";
        std::cout<<tabMonstres[i]->forcePoints()<<"           ";
        std::cout<<tabMonstres[i]->getHability()<<"   |\n";


    }
    std::cout<<" +--------------------------------------------------------------------------------+\n";
}



