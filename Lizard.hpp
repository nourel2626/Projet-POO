#pragma once

#include <Animal/Animal.hpp>
#include <Utility/Vec2d.hpp>

class Lizard: public Animal{
public:
    Lizard(Vec2d position, double energie, bool femelle,double taille = 150);
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
    OrganicEntity* updateState();
    bool matable(OrganicEntity const* other) const ;//override;
    bool canMate(Scorpion const* scorpion) const ;//override;
    bool canMate(Lizard const* lizard) const ;//override;
    bool canMate(Cactus const* food) const ;//override;
    double getEnergyLossFactor() const;//override;
    bool meet (OrganicEntity *mate) ;//override;
    bool meetWith (Scorpion *scorpion) ;// override;
    bool meetWith (Lizard *lizard) ;// override;
    bool meetWith (Cactus *cactus) ;// override;
private:

};

