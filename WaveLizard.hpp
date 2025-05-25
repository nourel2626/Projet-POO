#pragma once
#include <Animal/Lizard.hpp>


class Wave;
class WaveLizard: public Lizard {
public:
    WaveLizard(Vec2d position, double energie, bool femelle,double taille);
    WaveLizard(Vec2d position);
    void emission();
    void update(sf::Time dt);
private:


};
