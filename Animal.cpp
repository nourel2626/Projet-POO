#include "Animal.hpp"
#include <Application.hpp>


Animal::Animal(const Vec2d& position)
    : Collider(position,ANIMAL_RADIUS),
      Direction(1,0),
      MagnitudeVitesse(0.0),
      PositionCible(0,0)
      {}
double Animal:: getRandomWalkRadius () const {
    return ANIMAL_RANDOM_WALK_RADIUS;
}
double Animal::getRandomWalkDistance () const {
    return ANIMAL_RANDOM_WALK_DISTANCE;
}
double Animal::getRandomWalkJitter() const{
    return ANIMAL_RANDOM_WALK_JITTER;
}
double Animal::getViewRange () {
    return ANIMAL_VIEW_RANGE;
}
Vec2d Animal::randomWalk(Vec2d current_target) {
    Vec2d random_vec(uniform(-1.0,1.0),uniform(-1.0,1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised()*getRandomWalkRadius();
    Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);
    Vec2d global_target = convertToGlobalCoord(moved_current_target);
    return global_target - getPosition();
}
Vec2d Animal::convertToGlobalCoord(const Vec2d& local) const {
    sf::Transform transform;
    transform.translate(getPosition());
    transform.rotate(Direction.angle() / DEG_TO_RAD); // gamma en degrés
    return transform.transformPoint(local);
}
/*double Animal::getViewRange() {
    return 6.82;  // Essayons 180° (PI radians)
}
*/
Vec2d Animal::ForceAttraction(Deceleration deceleration){
    Vec2d forceAttraction,vTarget,toTarget;
    toTarget= PositionCible -  getPosition();
    double decelerationNum;
    if(deceleration==forte){
        decelerationNum=0.9;
    }
    else if (deceleration==moyenne){
        decelerationNum=0.6;
    }
    else{
        decelerationNum=0.3;
    }

    double speed(std::min((toTarget.length()/decelerationNum),getStandardMaxSpeed()));
    vTarget= (toTarget/toTarget.length())*speed;
    forceAttraction= vTarget - getSpeedVector();
    return forceAttraction;

}
double Animal::getViewDistance () {
    return ANIMAL_VIEW_DISTANCE;
}
double Animal::getRotation () {
    return Direction.angle();
}
bool Animal::isTargetInSight(Vec2d positionCible){
    bool retour(false);
    Vec2d d(positionCible-getPosition());
    Vec2d dn(d.normalised());
    double a(Direction.dot(dn));
    if ((d.lengthSquared()<= getViewDistance())and(a >= cos((Angle+0.001)/2))){
        retour=true;
    }
    if (isEqual(d.lengthSquared(),0)){
        retour=true;
    }
    return retour;

}


void Animal::drawVision(sf::RenderTarget &targetWindow) {
    sf::Color color = sf::Color::Black;
    color.a = 16;  // Gris transparent

    double startAngle = (-getViewRange()*180/PI)/2.0; // Début de l'arc
    double endAngle = (getViewRange()*180/PI)/2.0;   // Fin de l'arc
    double rotation = Direction.angle()/DEG_TO_RAD;  // Rotation pour aligner l'arc avec la direction

    Arc arc = buildArc(startAngle, endAngle, getViewDistance(), getPosition(), color, rotation);
    targetWindow.draw(arc);
}


void Animal::setRotation(double angle){
    Direction = {cos(angle), sin (angle)};
}

void Animal::draw(sf::RenderTarget &targetWindow){
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite( getPosition(), getRadius()*2,texture));
    targetWindow.draw(image_to_draw);
    targetWindow.draw(buildCircle(PositionCible,5,sf::Color(255,0,0)));
     drawVision(targetWindow); // Problème ici

}
double Animal::getStandardMaxSpeed(){
    return ANIMAL_MAX_SPEED;
}
double Animal::getMass(){
    return ANIMAL_MASS;
}
void Animal::setTargetPosition(Vec2d Position){
    PositionCible=Position;
}
Vec2d Animal::getSpeedVector(){
    return MagnitudeVitesse*Direction;
}
/*void Animal::update(sf::Time dt){
    Vec2d f(ForceAttraction(Deceleration::moyenne));
    Vec2d acceleration(f/getMass());
    Vec2d nouvelle_vitesse(getSpeedVector()+acceleration*dt.asSeconds());
    Vec2d nouvelle_direction(nouvelle_vitesse.normalised());
    if (nouvelle_vitesse.length()>getStandardMaxSpeed()){
        nouvelle_vitesse=nouvelle_direction*getStandardMaxSpeed();
    }
    Direction = nouvelle_direction;
    MagnitudeVitesse = nouvelle_vitesse.length();
    Vec2d nouvelle_position( getPosition()+ nouvelle_vitesse* dt.asSeconds());
    Vec2d dx(nouvelle_position -  getPosition());
     move(dx);

}
*/
void Animal::update(sf::Time dt){
    auto& env = getAppEnv();
    std::list<Vec2d> ciblesPotentielles = env.getTargetsInSightForAnimal(this);
    if (ciblesPotentielles.empty()){

    }
    else{
    PositionCible=ciblesPotentielles.front();
    Vec2d f(ForceAttraction(Deceleration::moyenne));
    Vec2d acceleration(f/getMass());
    Vec2d nouvelle_vitesse(getSpeedVector()+acceleration*dt.asSeconds());
    Vec2d nouvelle_direction(nouvelle_vitesse.normalised());
    if (nouvelle_vitesse.length()>getStandardMaxSpeed()){
        nouvelle_vitesse=nouvelle_direction*getStandardMaxSpeed();
    }
    Direction = nouvelle_direction;
    MagnitudeVitesse = nouvelle_vitesse.length();
    Vec2d nouvelle_position( getPosition()+ nouvelle_vitesse* dt.asSeconds());
    Vec2d dx(nouvelle_position -  getPosition());
     move(dx);
    }
}


