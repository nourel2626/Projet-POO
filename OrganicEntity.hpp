#pragma once

#include "Obstacle/Collider.hpp"
#include <SFML/Graphics.hpp>

class Scorpion;
class Lizard;
class Cactus;
class Animal;
class OrganicEntity : public Collider {
public:
    virtual ~OrganicEntity() ;
    OrganicEntity(Vec2d const& position, double energie, sf::Time longevite, double taille);
    virtual void update(sf::Time dt) = 0;                // méthode virtuelle pure
    virtual void draw(sf::RenderTarget& target) const=0; // idem pour le dessin
    double getTaille() const;
    virtual sf::Texture& getTexture() const ;
    virtual bool eatable(OrganicEntity const* entity) const=0;
    virtual bool eatableBy(Scorpion const* scorpion) const=0;
    virtual bool eatableBy(Lizard const* lizard) const=0;
    virtual bool eatableBy(Cactus const* cactus) const=0;
    double getEnergie() const;
    void setEnergie(double);
    double getTaille();
    bool isDead ();
    void updateAge(sf::Time dt);
    virtual bool matable(OrganicEntity const* other) const = 0;
    virtual bool canMate(Scorpion const* scorpion) const = 0;
    virtual bool canMate(Lizard const* lizard) const = 0;
    virtual bool canMate(Cactus const* food) const = 0;
    sf::Time getAge () const;
    virtual bool meet (OrganicEntity *mate) =0;
    virtual bool meetWith (Scorpion *scorpion) = 0;
    virtual bool meetWith (Lizard *lizard)= 0;
    virtual bool meetWith (Cactus *cactus) =0;

private:
    double Energie;
    sf::Time Age;
    sf::Time Longevite;
};
