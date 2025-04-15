#include "Animal.hpp"
#include <Application.hpp>


Animal::Animal(const Vec2d& position, double taille, double energie, bool femelle)
    : OrganicEntity(position, taille, energie),
      Direction(1, 0),
      MagnitudeVitesse(0.0),
      PositionCible(0, 0),
      Femelle(femelle)
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
double Animal::getViewRange ()const{
    return ANIMAL_VIEW_RANGE;
}
Vec2d Animal::randomWalk() {
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
double Animal::getViewDistance () const{
    return ANIMAL_VIEW_DISTANCE;
}
double Animal::getRotation ()const{
    return Direction.angle();
}
bool Animal::isTargetInSight(Vec2d positionCible){
    bool retour(false);
    Vec2d d(positionCible-getPosition());
    Vec2d dn(d.normalised());
    double a(Direction.dot(dn));
    if ((d.lengthSquared()<= getViewDistance()*getViewDistance())and(a >= cos((getViewRange()+0.001)/2))){
        retour=true;
    }
    if (isEqual(d.lengthSquared(),0)){
        retour=true;
    }
    return retour;

}
void Animal::drawVision(sf::RenderTarget &targetWindow)const{
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

void Animal::draw(sf::RenderTarget& targetWindow) const{
    sf::Texture& texture = getTexture();
    auto image_to_draw(buildSprite( getPosition(), getRadius()*2,texture,getRotation()*(1/DEG_TO_RAD)));
    targetWindow.draw(image_to_draw);
    //targetWindow.draw(buildCircle(PositionCible,5,sf::Color(255,0,0)));
     drawVision(targetWindow); // Problème ici
     sf::Color color(0, 0, 255);

     // Un anneau autour de la current_target

     //auto& env = getAppEnv();
     // si état = WANDERING
     //std::list<Vec2d> ciblesPotentielles = env.getEntitiesInSightForAnimal(this);
     //if (ciblesPotentielles.empty()){
     targetWindow.draw(buildAnnulus(getPosition() + getRandomWalkDistance()*Direction, getRandomWalkRadius(), sf::Color(255, 150, 0),2));
     Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);
     Vec2d global_target = convertToGlobalCoord(moved_current_target);
     targetWindow.draw(buildCircle(global_target, 5, color));
}

double Animal::getStandardMaxSpeed()const{
    return ANIMAL_MAX_SPEED;
}
double Animal::getMass()const{
    return ANIMAL_MASS;
}
void Animal::setTargetPosition(Vec2d Position){
    PositionCible=Position;
}
Vec2d Animal::getSpeedVector()const{
    return MagnitudeVitesse*Direction;
}

/*void Animal::update(sf::Time dt){
    auto& env = getAppEnv();
    std::list<Vec2d> ciblesPotentielles = env.getTargetsInSightForAnimal(this);
    if (ciblesPotentielles.empty()){
    move(getPosition()-randomWalk(getPosition()));

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
*/
Etat Animal::updateState(){
    auto& env = getAppEnv();
    Etat etat;
    std::list<OrganicEntity> ciblesPotentielles = env.getEntitiesInSightForAnimal2(this);
    if (ciblesPotentielles.empty()) {
        // Aucun cible visible -> random walk
        etat=WANDERING;
    } else {
        // Choisir une cible visible mangeable et la plus proche
        Vec2d meilleurCible;
        double worldSize = getAppConfig().simulation_world_size;
        double minDist(worldSize);
       for (auto& cible : ciblesPotentielles ){
           double dist(this->distanceTo(cible));
           if (dist< minDist and eatable(&cible)){
               minDist=dist;
           }
       }
       etat=FOOD_IN_SIGHT;
    }
    return etat;
}

void Animal::update(sf::Time dt){
    auto& env = getAppEnv();
    std::list<Vec2d> ciblesPotentielles = env.getEntitiesInSightForAnimal(this);
    Vec2d f;
    Etat etat(updateState());

    switch (etat) {
    case FOOD_IN_SIGHT:
        PositionCible = ciblesPotentielles.front();
        f = ForceAttraction(Deceleration::moyenne);
    case FEEDING:
        f={0,0};
    case RUNNING_AWAY:
        f={0,0};
    case MATE_IN_SIGHT:
        f={0,0};
    case MATING:
        f={0,0};
    case GIVING_BIRTH:
        f={0,0};
    case WANDERING:
        f = randomWalk();
    }

}


void Animal::directionMove(sf::Time dt, Vec2d f)
{

    Vec2d acceleration = f / getMass();
    Vec2d nouvelle_vitesse = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d nouvelle_direction = nouvelle_vitesse.normalised();

    if (nouvelle_vitesse.length() > getStandardMaxSpeed()) {
        nouvelle_vitesse = nouvelle_direction * getStandardMaxSpeed();
    }

    if (!isEqual(nouvelle_direction.lengthSquared(), 0.0)) {
        Direction = nouvelle_direction;
    }


    MagnitudeVitesse = nouvelle_vitesse.length();

    Vec2d old_position = getPosition();
    Vec2d nouvelle_position = old_position + nouvelle_vitesse * dt.asSeconds();
    Vec2d dx = nouvelle_position - old_position;

    move(dx);
}

sf::Texture& Animal::getTexture() const{
    return getAppTexture(ANIMAL_TEXTURE);
}

bool Animal::getSex() const{
    return Femelle;
}


void Animal::setDirection(Vec2d direction){
    Direction = direction;
}
void Animal::setMagnitudeVitesse(double magnitude){
    MagnitudeVitesse=magnitude;
}
Vec2d Animal::getDirection() const{
    return Direction;
}
bool Animal::eatableBy(Scorpion const* scorpion) const{
    return false;
}
bool Animal::eatableBy(Lizard const* lizard) const{
    return false;
}
bool Animal::eatableBy(Cactus const* cactus) const{
    return false;
}
bool Animal::eatable( OrganicEntity const* entity) const{
    return entity->eatableBy(this);
}
