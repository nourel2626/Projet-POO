#pragma once

#include <Animal/Animal.hpp>
#include <Utility/Vec2d.hpp>

class Lizard: public Animal{
public:
    Lizard(Vec2d position,double taille, double energie, bool femelle);
    Lizard(Vec2d position);
    double getStandardMaxSpeed()const ;
    double getMaxSpeed() const;
    double getMass()const;
    double getRandomWalkRadius()const;
    double getRandomWalkDistance() const;
    double getRandomWalkJitter() const;
    double getViewRange() const;
    sf::Texture& getTexture() const;
    void update(sf::Time dt) ;
    void draw(sf::RenderTarget& targetWindow) const;
    void drawVision(sf::RenderTarget& targetWindow)const;
    bool isTargetInSight(Vec2d positionCible);
    bool eatableBy(Scorpion const* scorpion) const;
    bool eatableBy(Lizard const* lizard) const;
    bool eatableBy(Cactus const* cactus) const;
    bool eatable(OrganicEntity const* entity) const;
private:

};


