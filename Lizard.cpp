#include <Animal/Lizard.hpp>
#include <Application.hpp>

Lizard::Lizard(Vec2d position, double energie, bool femelle)
    :Animal(position)
{
    Energie=energie;
    Femelle=femelle;
}

Lizard::Lizard(Vec2d position)
    :Animal(position),
      Energie(getAppConfig().lizard_energy_initial)
{
    Femelle=(uniform(0,1)==0);
}


double Lizard::getStandardMaxSpeed(){
    return getAppConfig().lizard_max_speed;
}
double Lizard::getMass(){
    return getAppConfig().lizard_mass;
}
double Lizard::getRandomWalkRadius() const{
    return getAppConfig().lizard_random_walk_radius;
}
double Lizard::getRandomWalkDistance() const{
    return getAppConfig().lizard_random_walk_distance;
}
double Lizard::getRandomWalkJitter() const{
    return getAppConfig().lizard_random_walk_jitter;
}
double Lizard::getViewRange(){
    return getAppConfig().lizard_view_range;
}
sf::Texture& Lizard::getTexture(){
    if (Femelle==true){
    return getAppTexture(getAppConfig().lizard_texture_female);
    }
    else{
       return getAppTexture(getAppConfig().lizard_texture_male);
    }
}
