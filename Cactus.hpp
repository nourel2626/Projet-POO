#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Environment/OrganicEntity.hpp>

class Cactus :public OrganicEntity{
public:
    Cactus(Vec2d position);
    ~Cactus();
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow) const;
    bool eatableBy(Scorpion const* scorpion) const;
    bool eatableBy(Lizard const* lizard) const;
    bool eatableBy(Cactus const* cactus) const;
    bool eatable( OrganicEntity const* entity) const;
private:


};
