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
    g.display(v);



    

    while( partie && !win )
    {
        std::cout<<"-------------- Tour n°"<<tour<<"------------------\n";

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
                    afficherInfosMonstres(monster,'S');
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
                    afficherInfosMonstres(monster,'B');

                }
            }
            
        }

        
            std::cout<<"\nTous les monstres se sont déplacés, réaffichage du terrain : \n";
            g.display(v);


            //AFFICHAGE DES POINTS DE L'ADV

            


            if(adv->lifePoints()>0)
            {
                std::cout<<"----------Fin du tour "<<tour<<"----------\n";
                std::cout<<"Voici vos informations : \n";
                std::cout<<"Points de vie :"<<  adv->lifePoints() <<"\n";
                std::cout<<"Points de solidité de l'épée :"<<adv->getSword().getSolidity()<<"\n";
                std::cout<<"Points de solidité de l'armure :"<<adv->getArmor().getSolidity()<<"\n";
                std::cout<<"Montant présent dans la bourse :"<<adv->getBourse()<<"\n";
                std::cout<<"Présence de l'amulet : "; adv->hasAmulet()?std::cout<<"Oui\n":std::cout<<"Non\n";

                tour++;
            }
            else
            {
                std::cout<<"Vous etes mort.Fin de la partie \n";
                partie= false;
            }
    }

}



