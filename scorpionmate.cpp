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
        if (getEnergie() < getAppConfig().scorpion_energy_min_mating_female ) {
            return false;
        }
    }
     else {
        if (getEnergie() < getAppConfig().scorpion_energy_min_mating_male ) {
                return false;
            }
        }

    if (getAge().asSeconds() < getAppConfig().scorpion_min_age_mating ) {
        return false;
    }
    if (getEnceinte() or scorpion->getEnceinte()){
        return false;
    }
    if (getEtat()== GIVING_BIRTH or scorpion->getEtat()== GIVING_BIRTH){
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
//     }else {
//         double babies;
//         babies = uniform(getAppConfig().scorpion_min_children,getAppConfig().scorpion_max_children);
//         setEnceinte(true);
//         this->setEnergie(getEnergie()-(babies*getAppConfig().scorpion_energy_loss_female_per_child));
//         scorpion->setEnergie(scorpion->getEnergie()-getAppConfig().scorpion_energy_loss_mating_male);
//         // reste comment indiquer que la femelle est enceinte + temps de gestation
    }
 }
 bool Scorpion::meetWith (Lizard *lizard) {
     return false;
 }
 bool Scorpion::meetWith (Cactus *cactus) {
     return false;
 }
double Scorpion::getGestationTime() const {
     return getAppConfig().scorpion_gestation_time;
 }

double Scorpion::getMaxChildren() const{
    return getAppConfig().scorpion_max_children;
}
double Scorpion::getMinChildren() const{
    return getAppConfig().scorpion_min_children;
}
double Scorpion::getEnergyLossPerChildFemale() const{
   return getAppConfig().scorpion_energy_loss_female_per_child;
}
double Scorpion::getEnergyMatingMale() const{
    return getAppConfig().scorpion_energy_loss_mating_male;
}
void Scorpion::giveBirth(){
    Scorpion* scorpion= new Scorpion(getPosition());
    getAppEnv().Environment::addEntity(scorpion);
}
