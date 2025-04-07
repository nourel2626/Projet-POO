#include "Environment.hpp"
#include <Application.hpp>
#include "Animal/Animal.hpp"

Environment::Environment(){}

Environment::~Environment() {
    clean();
}

void Environment::addAnimal(Animal* animal){
    Animaux.push_back(animal);
}

void Environment::addTarget(const Vec2d& cible){
Cibles.push_back(cible);
}

void Environment::update(sf::Time dt) {
    //faire évoluer la faune ici
}

void Environment::draw(sf::RenderTarget& targetWindow) const {
    for (auto cible: Cibles){
    targetWindow.draw(buildCircle(cible,5,sf::Color(255,0,0)));
}

        // Dessiner tous les animaux
        for (auto& animal : Animaux) {
            animal->draw(targetWindow);
        }
    }



void Environment::clean () {
for (auto animal: Animaux) {
   delete animal;
   animal = nullptr;
}
Animaux.clear();
Cibles.clear();
}
std::list<Vec2d> Environment::getTargetsInSightForAnimal(Animal* animal){
    std::list<Vec2d> ciblesPotentielles;
    for (auto cible: Cibles){
        if(animal->isTargetInSight(cible)){
            ciblesPotentielles.push_back(cible);
        }
    }
    return ciblesPotentielles;
}
