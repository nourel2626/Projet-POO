#ifndef LIZARD_HPP
#define LIZARD_HPP

#include <Animal/Animal.hpp>
#include <Utility/Vec2d.hpp>

class Lizard: public Animal{
public:
    Lizard(Vec2d position, double energie, bool femelle);
    Lizard(Vec2d position);
    virtual double getStandardMaxSpeed();
    virtual double getMass();
    virtual double getRandomWalkRadius() const;
    virtual double getRandomWalkDistance() const;
    virtual double getRandomWalkJitter() const;
    virtual double getViewRange();
    virtual sf::Texture& getTexture();
private:
    double Energie;
    double Taille;
    bool Femelle;
};
#endif // LIZARD_HPP
