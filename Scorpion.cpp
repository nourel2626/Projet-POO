#include "Scorpion.hpp"
#include <Application.hpp>

Scorpion::Scorpion(Vec2d position, double taille, double energie, bool femelle)
    :Animal(position, taille, energie, femelle)
{

}

Scorpion::Scorpion(Vec2d position)
    :Animal(position,getAppConfig().scorpion_size, getAppConfig().scorpion_energy_initial,(uniform(0,1)==0) )

{

}


double Scorpion::getStandardMaxSpeed()const{
    return getAppConfig().scorpion_max_speed;
}
double Scorpion::getMaxSpeed() const{
    return Animal::getMaxSpeed();
}
double Scorpion::getMass()const{
    return getAppConfig().scorpion_mass;
}
double Scorpion::getRandomWalkRadius()const{
    return getAppConfig().scorpion_random_walk_radius;
}
double Scorpion::getRandomWalkDistance()const{
    return getAppConfig().scorpion_random_walk_distance;
}
double Scorpion::getRandomWalkJitter()const{
    return getAppConfig().scorpion_random_walk_jitter;
}
double Scorpion::getViewRange()const{
    return getAppConfig().scorpion_view_range;
}

sf::Texture& Scorpion::getTexture()const{
    return getAppTexture(getAppConfig().scorpion_texture);
}
void Scorpion::update(sf::Time dt){
    Animal::update(dt);
}
void Scorpion::draw(sf::RenderTarget& targetWindow)const{
    Animal::draw(targetWindow);
}
void Scorpion::drawVision(sf::RenderTarget &targetWindow)const{
    Animal::drawVision(targetWindow);
}
bool Scorpion::isTargetInSight(Vec2d positionCible){
      bool retour(Animal::isTargetInSight(positionCible));
//    bool retour(false);
//    Vec2d d(positionCible-getPosition());
//    Vec2d dn(d.normalised());
//    double a(getDirection().dot(dn));
//    if ((d.lengthSquared()<= getViewDistance()*getViewDistance())and(a >= cos((getViewRange()+0.001)/2))){
//        retour=true;
//    }
//    if (isEqual(d.lengthSquared(),0)){
//        retour=true;
//    }
    return retour;

}
bool Scorpion::eatableBy(Scorpion const* scorpion) const{
    return false;
}
bool Scorpion::eatableBy(Lizard const* lizard) const{
    return false;
}
bool Scorpion::eatableBy(Cactus const* cactus) const{
    return false;
}
bool Scorpion::eatable( OrganicEntity const* entity) const{
    return entity->eatableBy(this);
}
