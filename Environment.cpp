#include "Environment.hpp"
#include "Animal/Animal.hpp"
#include <Application.hpp>


Environment::Environment(){}

Environment::~Environment() {
    clean();
}

void Environment::addAnimal(Animal*& animal){
    Animaux.push_back(animal);
}

void Environment::addTarget(const Vec2d& cible){
Cibles.push_back(cible);
}

void Environment::update(sf::Time dt) {
    //faire évoluer les animaux de la faune ici:
}

void Environment::draw(sf::RenderTarget& targetWindow) const {
    for (auto cible: Cibles){
    targetWindow.draw(buildCircle(cible,5,sf::Color(255,0,0))); //position dans l'appel à buildcircle incertain
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
