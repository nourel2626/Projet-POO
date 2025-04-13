#ifndef SCORPION_HPP
#define SCORPION_HPP

#include <Animal/Animal.hpp>


class Scorpion : public Animal{
public:
    Scorpion(Vec2d position, double energie, bool femelle);
    Scorpion(Vec2d position);
    double getStandardMaxSpeed();
    double getMass();
    double getRandomWalkRadius() const;
    double getRandomWalkDistance() const;
    double getRandomWalkJitter() const;
    double getViewRange();
    virtual sf::Texture& getTexture();
private:
    double Energie;
    double Taille;
    bool Femelle;
};
#endif // SCORPION_HPP
