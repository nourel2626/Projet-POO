#include "Environment.hpp"
#include <Application.hpp>
#include "Animal/Animal.hpp"
#include <Application.hpp>
#include <Environment/OrganicEntity.hpp>

Environment::Environment() : Température(getAppConfig().environment_default_temperature)
{}

double Environment::getTemperature() const {
    return Température;
}

void Environment::increaseTemperature() {
    Température += 0.5;
}
void Environment::decreaseTemperature() {
    if (Température > getAppConfig().environment_min_temperature) {
        Température -= 0.5;
    } else {
        throw std::invalid_argument("La température est en dessous de la température minimale");
    }
}
void Environment::resetControls(){
    Température = getAppConfig().environment_default_temperature;
}
Environment::~Environment() {
    clean();
}

void Environment::addEntity(OrganicEntity* entity){
    Entités.push_back(entity);
}

void Environment::addTarget(const Vec2d& cible){
Cibles.push_back(cible);
}

void Environment::update(sf::Time dt) {
    for (auto& entity : Entités) {
        entity->update(dt);
    }
}


void Environment::draw(sf::RenderTarget& targetWindow) const {
    for (auto cible: Cibles){
    targetWindow.draw(buildCircle(cible,5,sf::Color(255,0,0)));
}

        // Dessiner tous les animaux
        for (auto& entity : Entités) {
            entity->draw(targetWindow);
        }
    }

void Environment::clean () {
for (auto entity: Entités) {
   delete entity;
   entity = nullptr;
}
Entités.clear();
Cibles.clear();
}

std::vector<OrganicEntity*> Environment::getEntitiesInSightForAnimal(Animal* observer) const {
    std::vector<OrganicEntity*> visibleEntities;

    for (auto& entity : Entités) {
        if (entity != observer && observer->isTargetInSight(entity->getPosition())) {
            visibleEntities.push_back(entity);
        }
    }

    return visibleEntities;
}
