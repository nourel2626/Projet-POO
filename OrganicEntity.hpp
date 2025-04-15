#pragma once

#include "Obstacle/Collider.hpp"
#include <SFML/Graphics.hpp>

class Scorpion;
class Lizard;
class Cactus;
class OrganicEntity : public Collider {
public:
    virtual ~OrganicEntity() ;
    OrganicEntity(Vec2d const& position, double taille, double e);
    virtual void update(sf::Time dt) = 0;                // méthode virtuelle pure
    virtual void draw(sf::RenderTarget& target) const=0; // idem pour le dessin
    double getTaille() const;
    virtual sf::Texture& getTexture() const ;
    virtual bool eatable(OrganicEntity const* entity) const=0;
    virtual bool eatableBy(Scorpion const* scorpion) const=0;
    virtual bool eatableBy(Lizard const* lizard) const=0;
    virtual bool eatableBy(Cactus const* cactus) const=0;

private:
    double Energie;
};
