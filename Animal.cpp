#include "Animal.hpp"
#include <Application.hpp>


Animal::Animal(const Vec2d& position, double energie, bool femelle, sf::Time longevite, double taille)
    : OrganicEntity(position, energie, longevite, taille),
      Direction(1, 0),
      MagnitudeVitesse(0.0),
      PositionCible(0, 0),
      Femelle(femelle),
      Etat(WANDERING)
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

    double speed(std::min((toTarget.length()/decelerationNum),getMaxSpeed()));
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
     drawAnnulus(targetWindow);
     if (isDebugOn()) {
         drawDebug(targetWindow);
         Collider::draw(targetWindow);
     }
}
void Animal::drawAnnulus(sf::RenderTarget& targetWindow) const {
     sf::Color color(0, 0, 255);
     if (Etat==WANDERING){
        targetWindow.draw(buildAnnulus(getPosition() + getRandomWalkDistance()*Direction, getRandomWalkRadius(), sf::Color(255, 150, 0),2));
        Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);
        Vec2d global_target = convertToGlobalCoord(moved_current_target);
     targetWindow.draw(buildCircle(global_target, 5, color));
     }
}
void Animal::drawDebug(sf::RenderTarget &targetWindow) const{
    std::string femelle("Mâle");
    Vec2d decalage(0,2*getAppConfig().default_debug_text_size);
    if (Femelle){femelle="Femelle";}
    auto text = buildText(femelle,getPosition()+ 3*decalage, getAppFont(),
                          getAppConfig().default_debug_text_size, sf::Color::Black, getRotation()+Angle*(1/DEG_TO_RAD));
    targetWindow.draw(text);
    auto text2 = buildText(to_nice_string(OrganicEntity::getEnergie()), (getPosition()+ 4*decalage), getAppFont(),
                          getAppConfig().default_debug_text_size, sf::Color::Black, getRotation() );
    targetWindow.draw(text2);
    std::string etat;
    switch (Etat) {
    case FOOD_IN_SIGHT:
        etat="FOOD_IN_SIGHT";
        break;
    case FEEDING:
        etat="FEEDING";
        break;
    case RUNNING_AWAY:
        etat="RUNNING_AWAY";
        break;
    case MATE_IN_SIGHT:
        etat="MATE_IN_SIGHT";
        break;
    case MATING:
        etat="MATING";
        break;
    case GIVING_BIRTH:
        etat="GIVING_BIRTH";
        break;
    case WANDERING:
        etat="WANDERING";
        break;
    }
    Vec2d decalage2 (0,4*getAppConfig().default_debug_text_size);
    auto text3 = buildText(etat,getPosition()+ decalage2, getAppFont(),
                          getAppConfig().default_debug_text_size, sf::Color::Black, getRotation() );
    targetWindow.draw(text3);
}

double Animal::getStandardMaxSpeed()const{
    return ANIMAL_MAX_SPEED;
}
double Animal::getMaxSpeed() const{
    double retour(getStandardMaxSpeed());
    if (Etat==FOOD_IN_SIGHT){
        retour*=3;
    }
    else if(Etat==MATE_IN_SIGHT){
        retour*=2;
    }
    else if(Etat == RUNNING_AWAY){
        retour*=4;
    }
    return retour;
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

/*
Prend les entités en vue par l'animal et les ajoutes aux atributs cible ou prédateur selon leur type

 */
void Animal::analyzeEnvironment(){
    auto& env = getAppEnv();
    std::list<OrganicEntity*> entities = env.getEntitiesInSightForAnimal2(this);
    for (auto& entity : entities){
        if(this->eatable(entity)){
            Cibles.push_back(entity);

        }
        if(entity->eatable(this)){
            Predateurs.push_back(entity);

        }
        if(this->matable(entity)){
            Mates.push_back(entity);
        }
     }
}

/*
Analyse les cibles et les prédateurs et determine l'etat de l'animal si l'état=food in sight il determine la mailleur cible

 */

//OrganicEntity* Animal::updateState(){
//    auto& env = getAppEnv();
//    //State etat;
//    OrganicEntity* meilleurCible(this);
//    std::list<OrganicEntity*> entities = env.getEntitiesInSightForAnimal2(this);

//    double worldSize = getAppConfig().simulation_world_size;
//    ciblesEtPredateurs();
//    if (!Predateurs.empty()){
//        Vec2d distancePredateur;
//        for (auto& predateur : Predateurs){
//            distancePredateur= predateur->getPosition()-getPosition();
//            if (distancePredateur.length()< worldSize/4){
//                Etat=RUNNING_AWAY;
//            }

//        }

//    }
//    else if (entities.empty() or Cibles.empty()) {
//        // Aucun cible visible -> random walk
//        Etat=WANDERING;


//    }
//    else {
//        // Choisir une cible visible mangeable et la plus proche

//        double minDist(worldSize);
//       for (auto& cible : Cibles ){
//           double dist(this->distanceTo(cible->getPosition()));
//           if (dist< minDist){
//               minDist=dist;
//               meilleurCible=cible;

//           }
//       }
//       Etat=FOOD_IN_SIGHT;

//    }
//    //Etat = etat;
//    return meilleurCible;
//}

OrganicEntity* Animal::updateState() {
    auto& env = getAppEnv();
    double worldSize = getAppConfig().simulation_world_size;
    double minDist(worldSize);
    // 0. Analyse de l’environnement
    analyzeEnvironment();
   //1. Si il voit un prédateur, il fuit
    if (!Predateurs.empty()){
            Vec2d distancePredateur;
            for (auto& predateur : Predateurs){
                distancePredateur= predateur->getPosition()-getPosition();
                if (distancePredateur.length()< worldSize/4){
                    Etat=RUNNING_AWAY;
                }
                else{Etat=WANDERING;}
            }
        }
    // 2. Si déjà en FEEDING, on vérifie la pause
    if (Etat == FEEDING) {
        if (TempsDepuisEtatChange.asSeconds() < getAppConfig().animal_eating_pause_time) {
            return this;  // Encore en train de manger
        } else {
            Etat = WANDERING;
        }
    }



    // 3. Reproduction (prioritaire)
    OrganicEntity* ciblePartenaire;
    for (auto& mate : Mates ){
        double dist(this->distanceTo(mate->getPosition()));
        if (dist< minDist){
            minDist=dist;
            ciblePartenaire=mate;
        }
    }
    if (ciblePartenaire != nullptr) {
        if (Collider::isColliding(*ciblePartenaire)) {
            Etat = MATING;
        }

        else  {
            Etat = MATE_IN_SIGHT;
        }
        return ciblePartenaire;
    }

    // 4. Alimentation

    OrganicEntity* cibleNourriture;
         for (auto& cible : Cibles ){
             double dist(this->distanceTo(cible->getPosition()));
             if (dist< minDist){
                 minDist=dist;
                 cibleNourriture=cible;
                }
         }
   if (cibleNourriture != nullptr) {
        if (Collider::isColliding(*cibleNourriture)) {
            Etat = FEEDING;
            TempsDepuisEtatChange = sf::Time::Zero;
            //addEnergie(getAppConfig().animal_meal_retention);
            setEnergie(getEnergie()+getAppConfig().animal_meal_retention);
            if (dynamic_cast<Animal*>(cibleNourriture)) { // si la cible est un animal
                cibleNourriture->setEnergie(0); // tue l’animal mangé
            } else { // si la cible est un cactus
                cibleNourriture->setEnergie(getEnergie()-getAppConfig().animal_meal_retention);
            }
        } else {
            Etat = FOOD_IN_SIGHT;

        return cibleNourriture;
        }
    }
   if (getEnceinte() and getGestation()< getAppConfig().ani){
   }

    // 5. Rien en vue
    Etat = WANDERING;
    return this;
}
sf::Time Animal::getGestation() const {
    return Grossese.Gestation;
}
void Animal::update(sf::Time dt){
    auto& env = getAppEnv();
    std::list<OrganicEntity*> ciblesPotentielles = env.getEntitiesInSightForAnimal2(this);
    Vec2d f;
    OrganicEntity* cible(updateState());

    switch (Etat) {
    case FOOD_IN_SIGHT:{
        PositionCible = cible->getPosition();
        f = ForceAttraction(Deceleration::moyenne);
        break;
    }
    case FEEDING:{
        f={0,0};
        break;
    }
    case RUNNING_AWAY:{
        double delta1(500),delta2(1.2);
        Vec2d force{0,0};
        for (auto& cible: ciblesPotentielles){
            Vec2d dir(PositionCible-getPosition());
            if (cible->eatable(this)){
                force-=(delta1*dir)/(pow(dir.length(),delta2));
            }
        }
        f=force;
        break;
    }
    case MATE_IN_SIGHT:{
        f={0,0};
        break;
    }
    case MATING:{
        f={0,0};
        break;
    }
    case GIVING_BIRTH:{
        f={0,0};
        setEnceinte(false);
        Grossese.Gestation=sf::Time::Zero;

        break;
    }
    case WANDERING:{
        f = randomWalk();
        break;
    }
    }

    updateAge(dt);
    if(getEnceinte()){
        Grossese.Gestation+=dt;
    }

    double perte_energie;
    perte_energie = getAppConfig().animal_base_energy_consumption + (getSpeedVector().length()*getEnergyLossFactor()*dt.asSeconds());
    setEnergie(getEnergie() - perte_energie);
    if (getEnergie()< 70){
        MagnitudeVitesse= MagnitudeVitesse/1.05;
    }
    directionMove(dt, f);
//    if (isDead()){
//        delete this;

//    }
}


void Animal::directionMove(sf::Time dt, Vec2d f)
{

    Vec2d acceleration = f / getMass();
    Vec2d nouvelle_vitesse = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d nouvelle_direction = nouvelle_vitesse.normalised();

    if (nouvelle_vitesse.length() > getMaxSpeed()) {
        nouvelle_vitesse = nouvelle_direction * getMaxSpeed();
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

//bool Animal::matable(const OrganicEntity *other) const{
//    return OrganicEntity::matable(other);
//}
//bool Animal::canMate(const Scorpion *scorpion) const{
//    return OrganicEntity::canMate(scorpion);
//}

//bool Animal::canMate(const Lizard *lizard) const{
//    return OrganicEntity::canMate(lizard);
//}

//bool Animal::canMate(const Cactus *cactus) const {
//    return OrganicEntity::canMate(cactus);
//}

bool Animal::getEnceinte() const{
    return Grossese.Enceinte;
}

State Animal::getEtat() const{
    return Etat;
}
void Animal::setEnceinte(bool enceinte){
    Grossese.Enceinte=enceinte;
}
