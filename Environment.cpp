#include "Environment.hpp"
#include <Application.hpp>
#include "Animal/Animal.hpp"
#include <Application.hpp>
#include <Environment/OrganicEntity.hpp>
#include <Environment/Wave.hpp>
#include <Environment/CloudGenerator.hpp>
#include <Obstacle/Rock.hpp>
#include <Environment/Cloud.hpp>

Environment::Environment() : Temperature(getAppConfig().environment_default_temperature)
{}

double Environment::getTemperature() const {
    return Temperature;
}

void Environment::increaseTemperature() {
    if (Temperature <= getAppConfig().environment_max_temperature) {
        Temperature += 0.5;
    } else {
        Temperature = getAppConfig().environment_max_temperature;
    }
}
void Environment::decreaseTemperature() {
    if (Temperature >= getAppConfig().environment_min_temperature) {
        Temperature -= 0.5;
    } else {
        Temperature = getAppConfig().environment_min_temperature;
    }
}
void Environment::resetControls(){
    Temperature = getAppConfig().environment_default_temperature;
}
Environment::~Environment() {
    clean();
}

void Environment::addEntity(OrganicEntity* entity){
    if (entity != nullptr) {
        Entites.push_back(entity);
    } else {
        throw std::invalid_argument("il n'y a pas d'entité");
    }
}
void Environment::addTarget(const Vec2d& cible){
    Cibles.push_back(cible);
}

void Environment::update(sf::Time dt) {
    for (auto it = Entites.begin(); it != Entites.end(); ) {
        OrganicEntity* entity = *it;
        entity->update(dt);
        if (entity->isDead()) {
            delete entity;
            it = Entites.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = Waves.begin(); it != Waves.end(); ) {
        (*it)->update(dt);

        if ((*it)->getIntensity() < getAppConfig().wave_intensity_threshold) {
            delete *it;
            it = Waves.erase(it);
        } else {
            ++it;
        }
    }

    for (auto& generator: Generators){
        generator->update(dt);
    }
    for(auto& cloud:Clouds){
        cloud->update(dt);
    }
    for(auto it = Clouds.begin(); it != Clouds.end(); ) {
        if((*it)->getRadius() < getAppConfig().cloud_evaporation_size) {
            delete *it;
            it = Clouds.erase(it);
        } else {
            ++it;
        }
    }
    double couvertureNuages(Clouds.size()/getAppConfig().environment_max_clouds);
    if(!Pluie && couvertureNuages>= getAppConfig().environment_raining_cloud_density ){
        if(bernoulli(getAppConfig().environment_raining_probability)){
            Pluie=true;
            Drought=false;
            RainDuration=sf::Time::Zero;

        }
    }
    if(Pluie && RainDuration.asSeconds()>= getAppConfig().environment_raining_duration){
        Pluie=false;
        for(auto& cloud:Clouds){
            delete cloud;
            cloud =nullptr;
        }
        Clouds.clear();
        HumidityDuration=sf::Time::Zero;
        DroughtDuration= sf::Time::Zero;
        Humidity=true;
        Drought=true;
    }
    if(Humidity && HumidityDuration.asSeconds()>= getAppConfig().environment_humidity_duration){
        Humidity=false;
    }
    HumidityDuration+=dt;
    RainDuration+=dt;
    DroughtDuration+=dt;
}


void Environment::draw(sf::RenderTarget& targetWindow) const {
    for (auto cible: Cibles){
        targetWindow.draw(buildCircle(cible,5,sf::Color(255,0,0)));
    }
    for (auto& entity : Entites) {
        entity->draw(targetWindow);
    }
    for (auto& wave : Waves) {
        wave->draw(targetWindow);
    }
    for (auto& rock : Rocks) {
        rock->draw(targetWindow);
    }
    for (auto& cloud: Clouds) {
        cloud ->draw(targetWindow);
    }
    
    std::list<OrganicEntity*> sorted( Entites.begin(), Entites.end());
    // on définit une relation d'ordre sur la base de getDepth():
    auto comp([](OrganicEntity* a, OrganicEntity* b)->bool{ return int(a->getDepth()) < int(b->getDepth()); });
    // on trie l'ensemble sur cette base
    sorted.sort (comp);
    // il faut ensuite dessiner l'ensemble trié sorted et non plus entities
    // Dessiner tous les animaux
    for (auto& entity : sorted) {
        entity->draw(targetWindow);
    }
    

}

void Environment::clean () {
    for (auto entity: Entites) {
        delete entity;
        entity = nullptr;
    }
    for (auto wave: Waves) {
        delete wave;
        wave = nullptr;
    }
    for (auto rock: Rocks) {
        delete rock;
        rock = nullptr;
    }

    for (auto cloud: Clouds) {
        delete cloud;
        cloud = nullptr;
    }
    for (auto generator: Generators) {
        delete generator;
        generator = nullptr;
    }

    Rocks.clear();
    Waves.clear();
    Entites.clear();
    Cibles.clear();
    Clouds.clear();
    Generators.clear();
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
void Environment::addWave(Wave* wave) {
    if (wave != nullptr) {
        Waves.push_back(wave);
    }else{
        throw std::invalid_argument("il n'y a pas de wave");
    }
}

void Environment::addObstacle(Collider* collider){
    if (collider!=nullptr) {
        Rocks.push_back(collider);
    }else{
        throw std::invalid_argument("il n'y a pas d'obstacle");
    }
}

std::vector<Collider*> Environment::getObstacles() const {
    return Rocks;
}

void Environment::addCloud(Cloud* cloud){
    if (cloud != nullptr){
        Clouds.push_back(cloud);
    } else {
        throw std::invalid_argument("il n'y a pas de nuage");
    }
}

void Environment::addGenerator(CloudGenerator* generator){
    if (generator != nullptr){
        Generators.push_back(generator);
    } else {
        throw std::invalid_argument("il n'y a pas de générateur");
    }
}


std::list<double> Environment::getIntensiteOndes(Vec2d location, sf::Time dt) const{
    std::list<double> retour;
    if(!Waves.empty()){
        for(auto& onde : Waves){
            double intensite(onde->getIntensity());
            retour.push_back(intensite);
        }}
    return retour;
}
sf::Time Environment::getDroughtDuration() const{
    return DroughtDuration;
}
double Environment::getCloudCount() const{
    return Clouds.size();
}

bool Environment::getPluie() const{
    return Pluie;
}
bool Environment::getHumidity() const{
    return Humidity;
}

