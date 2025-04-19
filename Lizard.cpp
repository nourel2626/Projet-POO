#include <Animal/Lizard.hpp>
#include <Application.hpp>

Lizard::Lizard(Vec2d position,double taille, double energie, bool femelle)
    :Animal(position, taille, energie, femelle)
{

}

Lizard::Lizard(Vec2d position)
    :Animal(position,getAppConfig().lizard_size, getAppConfig().lizard_energy_initial,(uniform(0,1)==0) )
{}

double Lizard::getStandardMaxSpeed()const{
    return getAppConfig().lizard_max_speed;
}
double Lizard::getMaxSpeed() const{
    return Animal::getMaxSpeed();

}
double Lizard::getMass()const{
    return getAppConfig().lizard_mass;
}
double Lizard::getRandomWalkRadius() const{
    return getAppConfig().lizard_random_walk_radius;
}
double Lizard::getRandomWalkDistance()const{
    return getAppConfig().lizard_random_walk_distance;
}
double Lizard::getRandomWalkJitter()const{
    return getAppConfig().lizard_random_walk_jitter;
}
double Lizard::getViewRange()const{
    return getAppConfig().lizard_view_range;
}
sf::Texture& Lizard::getTexture()const {
    if (getSex()==true){
    return getAppTexture(getAppConfig().lizard_texture_female);
    }
    else{
       return getAppTexture(getAppConfig().lizard_texture_male);
    }
}
void Lizard::update(sf::Time dt){
    Animal::update(dt);
}

//    auto& env = getAppEnv();
//    std::list<Vec2d> ciblesPotentielles = env.getEntitiesInSightForAnimal(this);
//    Vec2d f;

//    if (ciblesPotentielles.empty()) {
//        // Aucun cible visible -> random walk
//        f = randomWalk();
//    } else {
//        // Choisir une cible visible
//        setTargetPosition(ciblesPotentielles.front());
//        f = ForceAttraction(Deceleration::moyenne);
//    }

//    Vec2d acceleration = f / getMass();
//    Vec2d nouvelle_vitesse = getSpeedVector() + acceleration * dt.asSeconds();
//    Vec2d nouvelle_direction = nouvelle_vitesse.normalised();

//    if (nouvelle_vitesse.length() > getStandardMaxSpeed()) {
//        nouvelle_vitesse = nouvelle_direction * getStandardMaxSpeed();
//    }

//    if (!isEqual(nouvelle_direction.lengthSquared(), 0.0)) {
//        setDirection(nouvelle_direction);
//    }


//    setMagnitudeVitesse(nouvelle_vitesse.length());

//    Vec2d old_position = getPosition();
//    Vec2d nouvelle_position = old_position + nouvelle_vitesse * dt.asSeconds();
//    Vec2d dx = nouvelle_position - old_position;

//    move(dx);
//}
void Lizard::draw(sf::RenderTarget& targetWindow)const{
    Animal::draw(targetWindow);
}
void Lizard::drawVision(sf::RenderTarget &targetWindow)const{
  Animal::drawVision(targetWindow);
 }

bool Lizard::isTargetInSight(Vec2d positionCible){
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
bool Lizard::eatableBy(Scorpion const* scorpion) const{
    return true;
}
bool Lizard::eatableBy(Lizard const* lizard) const{
    return false;
}
bool Lizard::eatableBy(Cactus const* cactus) const{
    return false;
}
bool Lizard::eatable( OrganicEntity const* entity) const{
    return entity->eatableBy(this);
}

