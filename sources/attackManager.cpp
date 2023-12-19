#include "attackManager.h"
#include <random>
#include "ground.h"

double attackManager::pickRandom() const
{
    //tirer un double aléatoire
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double randomNumber = distribution(gen);
    return randomNumber;
}
