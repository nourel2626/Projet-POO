#include "Environment.hpp"
#include <Application.hpp>
#include "Animal/Animal.hpp"
#include <Application.hpp>
#include <Environment/OrganicEntity.hpp>

Environment::Environment() : Temperature(getAppConfig().environment_default_temperature)
{}

double Environment::getTemperature() const {
    return Temperature;
}

void Environment::increaseTemperature() {
    Temperature += 0.5;
}
void Environment::decreaseTemperature() {
    if (Temperature > getAppConfig().environment_min_temperature) {
        Temperature -= 0.5;
    } else {
        throw std::invalid_argument("La température est en dessous de la température minimale");
    }
}
void Environment::resetControls(){
    Temperature = getAppConfig().environment_default_temperature;
}
Environment::~Environment() {
    clean();
}

void Environment::addEntity(OrganicEntity* entity){
    Entites.push_back(entity);
}

void Environment::addTarget(const Vec2d& cible){
Cibles.push_back(cible);
}

//void Environment::update(sf::Time dt) {
//    for (auto& entity : Entites) {
//        entity->update(dt);
//        if (entity->isDead()){
//            delete entity;
//            entity = nullptr;

//        }
//    }
//}
void Environment::update(sf::Time dt) {
    for (auto it = Entites.begin(); it != Entites.end(); ) {
        OrganicEntity* entity = *it;
        entity->update(dt);

        if (entity->isDead()) {
            delete entity;
            it = Entites.erase(it); // Supprime l'élément de la liste et avance l'itérateur
        } else {
            ++it;
        }
    }
}


void Environment::draw(sf::RenderTarget& targetWindow) const {
    for (auto cible: Cibles){
    targetWindow.draw(buildCircle(cible,5,sf::Color(255,0,0)));
}

        // Dessiner tous les animaux
        for (auto& entity : Entites) {
            entity->draw(targetWindow);
        }
    }

void Environment::clean () {
for (auto entity: Entites) {
   delete entity;
   entity = nullptr;
}
Entites.clear();
Cibles.clear();
}

std::list<Vec2d> Environment::getEntitiesInSightForAnimal(Animal *observer) const {
    std::list<Vec2d> visibleEntities;

    for (auto& entity : Entites) {
        if (entity != observer && observer->isTargetInSight(entity->getPosition())) {
            visibleEntities.push_back(entity->getPosition());
        }
    }

    return visibleEntities;
}
std::list<OrganicEntity*> Environment::getEntitiesInSightForAnimal2(Animal *observer) const {
    std::list<OrganicEntity*> visibleEntities;

    for (auto& entity : Entites) {
        if (entity != observer && observer->isTargetInSight(entity->getPosition())) {
            visibleEntities.push_back(entity);
        }
    }

    return visibleEntities;
}
