#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>

class Animal;

class Environment {
public :
    void addAnimal(Animal*& animal);
    void addTarget (const Vec2d& cible);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow) const;
    void clean ();
    Environment(const Environment&) = delete;
    ~Environment();
    Environment& operator=(const Environment&) = delete;
    Environment();
private :
    std::list <Animal*> Animaux;
    std::list <Vec2d> Cibles;
};
