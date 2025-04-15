#include "Environment.hpp"
#include <Application.hpp>
#include <Environment/Cactus.hpp>

Cactus::Cactus(Vec2d position)
    :OrganicEntity(position, getAppConfig().food_energy,getAppConfig().food_energy)
{

}

Cactus::~Cactus(){
}

void Cactus::draw(sf::RenderTarget &targetWindow) const{
    sf::Texture& texture = getAppTexture(getAppConfig().food_texture);
    auto image_to_draw(buildSprite(getPosition(),getTaille(),texture));
    targetWindow.draw(image_to_draw);

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
    return false;
}
bool Cactus::eatableBy(Cactus const* cactus) const{
    return false;
}
