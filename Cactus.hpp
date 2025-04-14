#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Environment/OrganicEntity.hpp>

class Cactus :public OrganicEntity{
public:
    Cactus(Vec2d position);
    ~Cactus();
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow);
private:
    double Taille;

};
