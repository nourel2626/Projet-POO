#pragma once
#define SCORPION_HPP

#include <Animal/Animal.hpp>


class Scorpion : public Animal{
public:
    Scorpion(Vec2d position,double taille, double energie, bool femelle);
    Scorpion(Vec2d position);
    double getStandardMaxSpeed() const;
    double getMass()const;
    double getRandomWalkRadius() const;
    double getRandomWalkDistance()const;
    double getRandomWalkJitter()const;
    double getViewRange()const;
    sf::Texture& getTexture()const;
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow)const;
    bool isTargetInSight(Vec2d positionCible);
    bool eatableBy(Scorpion const* scorpion) const;
    bool eatableBy(Lizard const* lizard) const;
    bool eatableBy(Cactus const* cactus) const;
    bool eatable(OrganicEntity const* entity) const;
    void drawVision(sf::RenderTarget &targetWindow)const;
private:

};
