#include "Environment.hpp"
#include <Application.hpp>
#include <Environment/Cactus.hpp>

Cactus::Cactus(Vec2d position)
    :OrganicEntity(position, getAppConfig().food_energy)
{
    Taille = getAppConfig().food_energy;
}

Cactus::~Cactus(){
}

void Cactus::draw(sf::RenderTarget &targetWindow){
    sf::Texture& texture = getAppTexture(getAppConfig().food_texture);
    auto image_to_draw(buildSprite(getPosition(), Taille,texture));
    targetWindow.draw(image_to_draw)

}
