#include "Environment/OrganicEntity.hpp"
#include <Application.hpp>
#include "OrganicEntity.hpp"

 OrganicEntity::OrganicEntity(Vec2d const& position, double taille,double energie)
    : Collider(position,taille/2.0)
 {
     Energie=energie;
 }

 double OrganicEntity::getTaille() const{
     return getRadius();
 }

OrganicEntity::~OrganicEntity()=default;

void OrganicEntity::draw(sf::RenderTarget& targetWindow) const{
    sf::Texture& texture = getTexture();
    auto image_to_draw(buildSprite( getPosition(), getRadius()*2,texture));
    targetWindow.draw(image_to_draw);
     sf::Color color(0, 0, 255);

}
sf::Texture& OrganicEntity::getTexture() const{
    return getAppTexture(getAppConfig().entity_texture_tracked);
}
bool OrganicEntity::eatable( OrganicEntity const* entity) const{
    return entity->eatableBy(this);
}
bool OrganicEntity::eatableBy(Scorpion const* scorpion) const{
    return false;
}
bool OrganicEntity::eatableBy(Lizard const* lizard) const{
    return false;
}
bool OrganicEntity::eatableBy(Cactus const* cactus) const{
    return false;
}

