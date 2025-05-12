#include <Animal/Lizard.hpp>
#include <Application.hpp>

Lizard::Lizard(Vec2d position, double energie, bool femelle,double taille)
    :Animal(position, energie, femelle, getAppConfig().lizard_longevity, taille)
{

}

Lizard::Lizard(Vec2d position)
    : Animal(position,
             getAppConfig().lizard_energy_initial,
             uniform(0,1)==0,
             getAppConfig().lizard_longevity,
             getAppConfig().lizard_size)
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

void Lizard::draw(sf::RenderTarget& targetWindow)const{
    Animal::draw(targetWindow);
}
void Lizard::drawVision(sf::RenderTarget &targetWindow)const{
  Animal::drawVision(targetWindow);
 }

bool Lizard::isTargetInSight(Vec2d positionCible){
    bool retour(Animal::isTargetInSight(positionCible));

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

OrganicEntity* Lizard::updateState(){
    return Animal::updateState();
}


//bool Lizard::matable(OrganicEntity const* other) const {
//    bool retour(false);
//    if (other->canMate(this) && this->canMate(other)) {
//        retour= true;
//    }
//    return retour;
//}
bool Lizard::matable(OrganicEntity const* other) const {
    bool retour(false);
    const Lizard* otherLizard = dynamic_cast<const Lizard*>(other);
    if (otherLizard != nullptr && other->canMate(this) && this->canMate(otherLizard)) {
        retour = true;
    }
    return retour;
}

bool Lizard::canMate(Scorpion const* scorpion) const {
    return false;
}
bool Lizard::canMate(Lizard const* lizard) const { //il manque si enceinte ou accouche

    if (this->getSex() == lizard->getSex()){
        return false;
    }
    if (getSex()){
        if (getEnergie() < getAppConfig().lizard_energy_min_mating_female) {
            return false;
        } else {
            if (getEnergie() < getAppConfig().lizard_energy_min_mating_male) {
                return false;
            }
        }
    }
    if (getAge().asSeconds() < getAppConfig().lizard_min_age_mating) {
        return false;
    }
    if (getEnceinte()){
        return false;
    }
    if (getEtat()== GIVING_BIRTH){
        return false;
    }
    return true;
}
bool Lizard::canMate(Cactus const* food) const {
    return false;
}

double Lizard::getEnergyLossFactor() const {
    return getAppConfig().lizard_energy_loss_factor;
}
bool Lizard::meet (OrganicEntity *mate) {
     return this -> meetWith(mate);
 }
 bool Lizard::meetWith (Scorpion *scorpion) {
     return false;
 }
 bool Lizard::meetWith (Lizard *lizard) {
     if (!(this->canMate(lizard) or lizard ->canMate(this))) {
         return false;
     }else {
         double babies;
         babies = uniform(getAppConfig().lizard_min_children,getAppConfig().lizard_max_children);
         setEnceinte(true);
         this->setEnergie(getEnergie()-(babies*getAppConfig().lizard_energy_loss_female_per_child));
         lizard->setEnergie(lizard->getEnergie()-getAppConfig().lizard_energy_loss_mating_male);
         // reste comment indiquer que la femelle est enceinte + temps de gestation
     }
 }
 bool Lizard::meetWith (Cactus *cactus) {
     return false;
 }
