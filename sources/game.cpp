#include "game.h"
#include "ground.h"
#include "groundElement.h"
#include "CLIView.h"
#include "emotView.h"
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
#include <cstdio>
#include <limits>
#include <iomanip>



game::game(){}



int game::choixView()
{
   int choix;
   do
   {
    std::cout<<" Quel type d'interface voulez vous ?\n 1- Affichage texte\n 2- Affichage coloré\n\n > ";
    std::cin>>choix;
    
   } while (!(choix==1 || choix==2));
   
    
    return choix;
}

std::unique_ptr<viewManager> game::createView(int choix)
{
    
    if(choix==1)
    {
        auto v=std::make_unique<CLIView>();
        return v;
    }
    else if(choix==2)
    {
        auto v=std::make_unique<emotView>();
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
        std::cout<<" Comment voulez-vous construire le terrain ? \n 1- Construire manuellement\n 2- Importer depuis un fichier\n\n > ";
        std::cin>>choix;
    }
    while(!(choix==1||choix==2));

    switch (choix)
    {
    case 1:
        g.buildGround();

        char rep;
        do{
            std::cout<<" Voulez vous sauvegarder le terrain dans un fichier ? O/N :";
            std::cin>>rep;
        }while(!(rep=='O'||rep=='N'));
        if(rep=='O')
        {
            g.exportGround();
            std::cout<<" Fichier sauvegardé avec succès \n";
        }
        break;
    
    case 2:
    std::ifstream fic;
        do{
            std::cout<<" Entrer le nom du fichier : "; std::cin>>nomFic;
            fic.open(nomFic.c_str()); 
        } while (!fic.is_open()); 
        g.importGround(fic);
        break;
    }


}


void game::startDisplay()
{
    std::cout<<" +-+-+-+-+-+-+-+-+-+-+ BIENVENUE DANS DUNGEON II +-+-+-+-+-+-+-+-+-+-+\n\n";
    std::cout<<" Ressortez en vie du donjon avec l'amulette  ! \n\n";

}
void game::clear() 
{
    system("clear || cls");
}

void game::rules()
{
    std::cout<<"\n +-+-+-+-+-+-+-+-+-+-+-+-+-+ REGLES DU JEU +-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n";
    std::cout<<"\n Vous devez récupérer l'amulette et réussir à atteindre la sortie en vie. \n Vous croiserez des monstres sur votre chemin que vous devrez combattre avec \n votre épée. Vous trouverez des tas de pièces qui vous permettront de réparer \n votre équipement. Vous pouvez vous déplacer dans les 9 directions ou rester \n à votre place. \n Les smart monster se dirigeront vers vous tandis que les blind monster se\n déplacent au hasard. \n\n NB:\n -Vous ne pouvez pas vous déplacer dans un mur ni dans une case extérieure,\n et vous ne pouvez pas sortir sans l'amulette.\n -Lors d'une bataille, vous pouvez continuer à vous battre en restant à la \n meme case ou fuir. \n\n A vous de jouer !\n\n";}

void game::play() 
{
    bool partie = true;
    bool win = false;
    int direction;
    int tour=1;
    clear() ;                
    
    startDisplay();
    

    int choixInterface = choixView();
    clear() ;                
    auto v = move(createView(choixInterface));

    
    startDisplay();

    ground g;
    chargerGround(g);
    clear() ;                
    rules();
    std::cout<<" Appuyez sur entrée pour continuer ...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //vider le tampn
    std::cin.get();
    clear() ;                

    while( partie && !win )
    {

        std::vector<std::vector<int>> tabInfosMonster;

        std::vector<monster*> tabMonstres;

        std::cout<<" +----------------------------------- Tour n°"<<tour<<" -----------------------------------+\n\n";
                     


        g.display(v);
        int indiceAdv = g.getIndiceAdventurer();
        auto adv= dynamic_cast<adventurer*>(g.getElementsTable()[indiceAdv].get());

        //AJT
        int rep;
        int depl=0;

        if(adv->getBourse()>0) 
        {

            do
            {
                std::cout<<" Que voulez vous faire ? \n 1)Utiliser la bourse \n 2)Me déplacer \n"; std::cin>>rep;
            } 
            while (!(rep==1||rep==2));

            if(rep==1) //utiliser la bourse
            {
                useBourse(adv);
            }
            else if(rep==2){ //se deplacer
                depl=1;
            }
        }
        else //se deplacer
        {
            depl=1;
        }


            if(depl==1) //l'aventurier se déplace
            {
                    do{
                        std::cout<<"\n\n Entrer la direction où vous souhaitez aller: \n";
                        std::cout<<" 1 2 3\n 4 ⑤ 6\n 7 8 9\n\n> ";
                        std::cin >>direction;
                    }
                    while(!(direction==1 || direction==2 || direction==3 || direction==4||direction==5||direction==6||direction==7 ||direction==8 ||direction==9));

                    clear() ;                
            
                    position posAdv = g.getAdventurerPosition();
                    adventurerMoveManager advMover{posAdv};
                    advMover.move(g,direction);

                    

                    if(adv->isOutWithAmulet())
                    {
                        win = true;
                    }
                    if(!win)
                    {
                        std::cout<<" +----------------------------------- Tour n°"<<tour<<" -----------------------------------+\n\n";
                        g.display(v);
                    }
                    else
                    {
                        std::cout<< "Vous avez gagné ! \n";
                        break;
                    }
            }
                    

            std::cout<<"\n Les monstres se déplacent... Appuyez sur entrée pour continuer \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //vider le tampn
            std::cin.get();
            clear() ;                
            //LES MONSTRES SE DEPLACENT
            tabMonstres = deplacerMonstres(g);
            std::cout<<" +----------------------------------- Tour n°"<<tour<<" -----------------------------------+\n\n";


            g.display(v);

            if(adv->lifePoints()>0)
            {
                    std::cout<<"\n +------------------------------ Fin du tour n°"<<tour<<" ---------------------------------+\n\n";

                //AFFICHAGE DES INFOS DES MONSTRES PROCHES
                if(tabMonstres.size()>0)
                {
                    afficherInfosMonstresProches(tabMonstres);
                }
                //AFFICHAGE DES POINTS DE L'ADV
                afficherInfosAdv(adv);

                std::cout<<" Appuyez sur entrée pour continuer ...";
                std::cin.get();
                clear() ;                
                tour++;
            }
            else
            {
                std::cout<<"Vous etes mort.Fin de la partie \n";
                partie= false;
            }
            
    }

        


    }




void game::useBourse(adventurer *adv)
{
    int montantVoulu;
    int montantBourse = adv->getBourse();
    int choixRep;
    do
    {
        std::cout<<" Vous avez : "<<montantBourse<<" pieces.Entrer le montant que vous voulez utiliser : ";
        std::cin>>montantVoulu;
    }while(montantVoulu<=0 || montantVoulu>montantBourse);

    do
    {
        std::cout<<" Que voulez vous réparer ? \n 1)Armure \n 2)Epee \n";
        std::cin>>choixRep;
    } while (!(choixRep==1 || choixRep==2));

    if(choixRep==1) //Réparer armure
    {
        adv->addToArmorSolidity(montantVoulu);
        adv->removeFromBourse(montantVoulu);
        std::cout<<" Votre armure a maintenant : "<<adv->getArmor().getSolidity()<<" points.\n";
    }
    else if(choixRep==2) //Réparer épée
    {
        adv->addToSwordSolidity(montantVoulu);
        adv->removeFromBourse(montantVoulu);
        std::cout<<" Votre épee a maintenant : "<<adv->getSword().getSolidity()<<" points.\n";
    }

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
    std::cout<<"\n Infos de l'aventurier  : \n";

    std::cout<<" +--------------------------------------------------------------------------------+\n";
    std::cout<<" |    PV   |  Points épée   |    Points armure     |     Bourse      |    Amulet  |\n";
    std::cout<<" +--------------------------------------------------------------------------------+\n";

    std::cout<<" | ";
    std::cout<< adv->lifePoints() <<"        ";
    std::cout<<adv->getSword().getSolidity()<<"                 ";
    std::cout<<adv->getArmor().getSolidity()<<"                     ";
    std::cout<<adv->getBourse()<<"         ";
    adv->hasAmulet()?std::cout<<"        Oui    ":std::cout<<"        Non    ";
    std::cout<<" \n +--------------------------------------------------------------------------------+\n";

    std::cout<<"\n";

}

void game::afficherInfosMonstresProches(const std::vector<monster*> &tabMonstres) 
{
    std::cout<<"\n Infos des monstres proches  : \n";

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
        std::cout<<tabMonstres[i]->getHability()<<"   \n";


    }
    std::cout<<" +--------------------------------------------------------------------------------+\n";
}



