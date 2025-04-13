#include "Scorpion.hpp"
#include <Application.hpp>

Scorpion::Scorpion(Vec2d position, double energie, bool femelle)
    :Animal(position)
{
    Energie=energie;
    Femelle=femelle;
}

Scorpion::Scorpion(Vec2d position)
    :Animal(position),
      Energie(getAppConfig().scorpion_energy_initial)
{
    Femelle=(uniform(0,1)==0);
}


double Scorpion::getStandardMaxSpeed(){
    return getAppConfig().scorpion_max_speed;
}
double Scorpion::getMass(){
    return getAppConfig().scorpion_mass;
}
double Scorpion::getRandomWalkRadius() const{
    return getAppConfig().scorpion_random_walk_radius;
}
double Scorpion::getRandomWalkDistance() const{
    return getAppConfig().scorpion_random_walk_distance;
}
double Scorpion::getRandomWalkJitter() const{
    return getAppConfig().scorpion_random_walk_jitter;
}
double Scorpion::getViewRange(){
    return getAppConfig().scorpion_view_range;
}

sf::Texture& Scorpion::getTexture(){
    return getAppTexture(getAppConfig().scorpion_texture);
}
