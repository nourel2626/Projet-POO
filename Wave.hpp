#pragma once
#include <Obstacle/Collider.hpp>
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include <Environment/Environment.hpp>
#include <Obstacle/Rock.hpp>
#include <vector>
class Wave : public Collider {
public:
    Wave(const Vec2d& origine, double energie, double rayon , double µ, double vitesse);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow) const override;
    double getIntensity() const;
    void setRayon(double rayon);
    bool containsAngle(const std::pair<double,double>& arc, double angle);



private:
    Vec2d Origine;
    double RayonInitial;
    double Rayon;
    double Energie;
    double µ;
    double Vitesse;
    sf::Time Time;
    std::vector<std::pair<double, double>> Arcs;
};
