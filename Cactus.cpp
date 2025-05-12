#include "Environment.hpp"
#include <Application.hpp>
#include <Environment/Cactus.hpp>

Cactus::Cactus(Vec2d position)
    : OrganicEntity(position, getAppConfig().food_energy, sf::seconds(1E9), getAppConfig().food_size)
{}



Cactus::~Cactus(){
}

void Cactus::draw(sf::RenderTarget &targetWindow) const{
    OrganicEntity::draw(targetWindow);

}
sf::Texture& Cactus::getTexture() const {
    return getAppTexture(getAppConfig().food_texture);
}
void Cactus::update(sf::Time  dt){

}

bool Cactus::eatable( OrganicEntity const* entity) const{
    return entity->eatableBy(this);
}
bool Cactus::eatableBy(Scorpion const* scorpion) const{
    return false;
}
bool Cactus::eatableBy(Lizard const* lizard) const{
    return true;
}
bool Cactus::eatableBy(Cactus const* cactus) const{
    return false;
}
bool Cactus::matable(OrganicEntity const* other) const {
     if (other->matable(this) && this->matable(other)) {
         return true;
     }
 }

 bool Cactus::canMate(Scorpion const* scorpion) const {
     return false;
 }
 bool Cactus::canMate(Lizard const* lizard) const {
     return false;
 }
 bool Cactus::canMate(Cactus const* food) const {
     return false;
 }
 bool Cactus::meet (OrganicEntity *mate)  {
      return mate->meet(this);
  }
  bool Cactus::meetWith (Scorpion *scorpion)  {
      return false;
  }
  bool Cactus::meetWith (Lizard *lizard)  {
      return false;
  }
  bool Cactus::meetWith (Cactus *cactus)  {
      return false;
  }
