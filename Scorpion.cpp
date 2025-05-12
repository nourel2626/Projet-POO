#include "Scorpion.hpp"
#include <Application.hpp>

Scorpion::Scorpion(Vec2d position, double energie, bool femelle, double taille)
    :Animal(position, energie, femelle,getAppConfig().scorpion_longevity, taille)
{

}

Scorpion::Scorpion(Vec2d position)
    : Animal(position,
             getAppConfig().scorpion_energy_initial,
             uniform(0,1)==0,
             getAppConfig().scorpion_longevity,
             getAppConfig().scorpion_size)
{}




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

    return Animal::isTargetInSight(positionCible);

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

OrganicEntity* Scorpion::updateState(){
    return Animal::updateState();
}
//bool Scorpion::matable(OrganicEntity const* other) const {
//    if (other->matable(this) && this->matable(other)) {
//        return true;
//    }
//}
bool Scorpion::matable(OrganicEntity const* other) const {
    const Scorpion* otherScorpion = dynamic_cast<const Scorpion*>(other);
    if (otherScorpion != nullptr && other->canMate(this) && this->canMate(otherScorpion)) {
        return true;
    }
    return false;
}

bool Scorpion::canMate(Scorpion const* scorpion) const { //il manque si enceinte ou accouche

    if (this->getSex() == scorpion->getSex()){
        return false;
    }
    if (getSex()){
        if (getEnergie() < getAppConfig().scorpion_energy_min_mating_female) {
            return false;
        } else {
            if (getEnergie() < getAppConfig().scorpion_energy_min_mating_male) {
                return false;
            }
        }
    }
    if (getAge().asSeconds() < getAppConfig().scorpion_min_age_mating) {
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
bool Scorpion::canMate(Lizard const* lizard) const {
    return false;
}
bool Scorpion::canMate(Cactus const* food) const {
    return false;
}
double Scorpion::getEnergyLossFactor() const {
     return getAppConfig().scorpion_energy_loss_factor;
 }
bool Scorpion::meet (OrganicEntity *mate) {
     return mate -> meet(this);
 }
 bool Scorpion::meetWith (Scorpion *scorpion) {
     if (!(this->canMate(scorpion) or scorpion ->canMate(this))) {
         return false;
     }else {
         double babies;
         babies = uniform(getAppConfig().scorpion_min_children,getAppConfig().scorpion_max_children);
         setEnceinte(true);
         this->setEnergie(getEnergie()-(babies*getAppConfig().scorpion_energy_loss_female_per_child));
         scorpion->setEnergie(scorpion->getEnergie()-getAppConfig().scorpion_energy_loss_mating_male);
         // reste comment indiquer que la femelle est enceinte + temps de gestation
     }
 }
 bool Scorpion::meetWith (Lizard *lizard) {
     return false;
 }
 bool Scorpion::meetWith (Cactus *cactus) {
     return false;
 }
