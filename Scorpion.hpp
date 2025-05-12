#pragma once

#include <Animal/Animal.hpp>


class Scorpion : public Animal{
public:
    Scorpion(Vec2d position, double energie, bool femelle,double taille= 150);
    Scorpion(Vec2d position);
    double getStandardMaxSpeed() const;
    double getMaxSpeed() const;
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
    OrganicEntity* updateState();
    bool matable(OrganicEntity const* other) const ;
    bool canMate(Scorpion const* scorpion) const ;
    bool canMate(Lizard const* lizard) const ;
    bool canMate(Cactus const* food) const ;
    double getEnergyLossFactor() const ;
    bool meet (OrganicEntity *mate) ;//override;
    bool meetWith (Scorpion *scorpion) ;// override;
    bool meetWith (Lizard *lizard) ;//override;
    bool meetWith (Cactus *cactus) ;// override;
private:

};

