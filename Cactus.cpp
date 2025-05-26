#include "Environment.hpp"
#include <Application.hpp>
#include <Environment/Cactus.hpp>

Cactus::Cactus(Vec2d position)
    : OrganicEntity(position, getAppConfig().food_energy, sf::seconds(1E9), getAppConfig().food_size) //Construction d'un cactus avec une longétivité "infinie", il ne disparaît que s'il est mangé
{}
void Cactus::draw(sf::RenderTarget &targetWindow) const{
    OrganicEntity::draw(targetWindow);

}
sf::Texture& Cactus::getTexture() const {
    return getAppTexture(getAppConfig().food_texture);
}
void Cactus::update(sf::Time  dt){
    auto& env= getAppEnv();
    if(env.getHumidity()){
        if(!(getEnergie()> getAppConfig().food_max_energy)){
            setRadius(getRadius()+getAppConfig().food_growth_rate/2);
            setEnergie(getEnergie()+getAppConfig().food_growth_rate);
        }
    }

}
bool Cactus::eatable( OrganicEntity const* entity) const{ // double dispatch permettant de gérer la prédation les différents cas en fonction du type de l'entité
    return entity->eatableBy(this);
}
bool Cactus::eatableBy(Scorpion const* scorpion) const{
    return false;
}
bool Cactus::eatableBy(Lizard const* lizard) const{
    return true;
}
bool Cactus::eatableBy(Cactus const* cactus) const{
    return false;
}
bool Cactus::matable(OrganicEntity const* other) const { // double dispatch permettant de gérer la reproduction en fonction du type des entités
    if (other->matable(this) && this->matable(other)) {
        return true;
    } else {
        return false;
    }
}
bool Cactus::canMate(Scorpion const* scorpion) const {
    return false;
}
bool Cactus::canMate(Lizard const* lizard) const {
    return false;
}
bool Cactus::canMate(Cactus const* food) const {
    return false;
}
bool Cactus::meet (OrganicEntity *mate)  { // double dispatch permettant de gérer la rencontre en fonction du type des entités
    return mate->meet(this);
}
bool Cactus::meetWith (Scorpion *scorpion)  {
    return false;
}
bool Cactus::meetWith (Lizard *lizard)  {
    return false;
}
bool Cactus::meetWith (Cactus *cactus)  {
    return false;
}
