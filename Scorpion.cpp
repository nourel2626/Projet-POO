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
    auto& env = getAppEnv();
    std::list<Vec2d> ciblesPotentielles = env.getEntitiesInSightForAnimal(this);
    Vec2d f;

    if (ciblesPotentielles.empty()) {
        // Aucun cible visible -> random walk
        f = randomWalk();
    } else {
        // Choisir une cible visible
        setTargetPosition(ciblesPotentielles.front());
        f = ForceAttraction(Deceleration::moyenne);
    }

    Vec2d acceleration = f / getMass();
    Vec2d nouvelle_vitesse = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d nouvelle_direction = nouvelle_vitesse.normalised();

    if (nouvelle_vitesse.length() > getStandardMaxSpeed()) {
        nouvelle_vitesse = nouvelle_direction * getStandardMaxSpeed();
    }

    if (!isEqual(nouvelle_direction.lengthSquared(), 0.0)) {
        setDirection(nouvelle_direction);
    }


    setMagnitudeVitesse(nouvelle_vitesse.length());

    Vec2d old_position = getPosition();
    Vec2d nouvelle_position = old_position + nouvelle_vitesse * dt.asSeconds();
    Vec2d dx = nouvelle_position - old_position;

    move(dx);
}
void Scorpion::draw(sf::RenderTarget& targetWindow)const{
    Animal::draw(targetWindow);
//    sf::Texture& texture = getTexture();
//    auto image_to_draw(buildSprite( getPosition(), getRadius()*2,texture,getRotation()*(1/DEG_TO_RAD)));
//    targetWindow.draw(image_to_draw);
//    //targetWindow.draw(buildCircle(PositionCible,5,sf::Color(255,0,0)));
//     drawVision(targetWindow); // Problème ici
//     sf::Color color(0, 0, 255);

//     // Un anneau autour de la current_target

//     auto& env = getAppEnv();
//     std::list<Vec2d> ciblesPotentielles = env.getEntitiesInSightForAnimal(this);
//     if (ciblesPotentielles.empty()){
//     targetWindow.draw(buildAnnulus(getPosition() + getRandomWalkDistance()*getDirection(), getRandomWalkRadius(), sf::Color(255, 150, 0),2));
//     targetWindow.draw(buildCircle(getPosition() + randomWalk(), 5, color));
//}
}
void Scorpion::drawVision(sf::RenderTarget &targetWindow)const{
    Animal::drawVision(targetWindow);
//    sf::Color color = sf::Color::Black;
//    color.a = 16;  // Gris transparent

//    double startAngle = (-getViewRange()*180/PI)/2.0; // Début de l'arc
//    double endAngle = (getViewRange()*180/PI)/2.0;   // Fin de l'arc
//    double rotation = getDirection().angle()/DEG_TO_RAD;  // Rotation pour aligner l'arc avec la direction

//    Arc arc = buildArc(startAngle, endAngle, getViewDistance(), getPosition(), color, rotation);
//    targetWindow.draw(arc);
}
bool Scorpion::isTargetInSight(Vec2d positionCible){
    bool retour(false);
    Vec2d d(positionCible-getPosition());
    Vec2d dn(d.normalised());
    double a(getDirection().dot(dn));
    if ((d.lengthSquared()<= getViewDistance()*getViewDistance())and(a >= cos((getViewRange()+0.001)/2))){
        retour=true;
    }
    if (isEqual(d.lengthSquared(),0)){
        retour=true;
    }
    return retour;

}
bool Scorpion::eatableBy(Scorpion const* scorpion) const{
    return false;
}
bool Scorpion::eatableBy(Lizard const* lizard) const{
    return true;
}
bool Scorpion::eatableBy(Cactus const* cactus) const{
    return false;
}
bool Scorpion::eatable( OrganicEntity const* entity) const{
    return entity->eatableBy(this);
}
