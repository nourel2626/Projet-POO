#include "Environment/OrganicEntity.hpp"
#include <Application.hpp>
#include "OrganicEntity.hpp"


OrganicEntity::OrganicEntity(Vec2d const& position, double energie, sf::Time longevite, double taille)
    : Collider(position, taille/2.0),
      Energie(energie),
      Age(sf::Time::Zero),
      Longevite(longevite)
{}
OrganicEntity::~OrganicEntity()= default;

double OrganicEntity::getEnergie() const {
    return Energie;
}
void OrganicEntity::setEnergie(double energie){
    Energie=energie;
}
void OrganicEntity::draw(sf::RenderTarget& targetWindow) const{
    sf::Texture& texture = getTexture();
    auto image_to_draw(buildSprite( getPosition(), getRadius()*2,texture));
    targetWindow.draw(image_to_draw);
    sf::Color color(0, 0, 255);
    if (!isDebugOn()){
        draw(targetWindow);
        auto text2 = buildText(to_nice_string(OrganicEntity::getEnergie()), (getPosition()), getAppFont(),
                               getAppConfig().default_debug_text_size, sf::Color::Black );
        targetWindow.draw(text2);
    }

}
sf::Texture& OrganicEntity::getTexture() const{
    return getAppTexture(getAppConfig().entity_texture_tracked);
}

double OrganicEntity::getTaille() const{
    return getRadius();
}
bool OrganicEntity::isDead (){
    bool retour = false;
    if (Energie < getAppConfig().animal_min_energy) {
        retour = true;
    }
    if(Age > Longevite){
        retour=true;
    }

    return retour;
}
void OrganicEntity::updateAge(sf::Time dt){
    Age += dt;
}
bool OrganicEntity::matable(OrganicEntity const* other) const {
    return false;
}
bool OrganicEntity::canMate(Scorpion const* scorpion) const {
    return false;
}
bool OrganicEntity::canMate(Lizard const* lizard) const {
    return false;
}

bool OrganicEntity::canMate(Cactus const* food) const {
    return false;
}
sf::Time OrganicEntity::getAge() const {
    return Age;
}
void OrganicEntity::update(sf::Time dt) {
    if (isDead()){
        delete this;

    }
    return updateAge(dt);
}
bool OrganicEntity::meet (OrganicEntity *mate) {
    return false;
}
bool OrganicEntity::meetWith (Scorpion *scorpion) {
    return false;
}
bool OrganicEntity::meetWith (Lizard *lizard) {
    return false;
}
bool OrganicEntity::meetWith (Cactus *cactus){
    return false;
}
