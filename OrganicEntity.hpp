#pragma once

#include "Obstacle/Collider.hpp"

class OrganicEntity : public Collider {
public:
    virtual ~OrganicEntity() = default;
    OrganicEntity(Vec2d const& position, double taille, double e);
    virtual void update(sf::Time dt) = 0;                // méthode virtuelle pure
    virtual void draw(sf::RenderTarget& target) const = 0; // idem pour le dessin
private:
    double energy;
};
