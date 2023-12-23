#include <iostream>
#include "game.h"
#include "menu.h"
#include "ground.h"
#include "viewManager.h"
#include "CLIView.h"
#include <random>
#include <memory>
#include "adventurer.h"
#include "blindMonster.h"
#include "movementManager.h"
#include "smartMonsterMoveManager.h"
#include "blindMonsterMoveManager.h"
#include "adventurerMoveManager.h"

using std::cout;
using std::make_unique;

#include <fstream>


int main()
{
    game g{};
    g.play();
}