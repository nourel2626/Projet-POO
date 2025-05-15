#pragma once
#include <Obstacle/Collider.hpp>


class Rock : public Collider {
public:
    Rock(const Vec2d& position);
    void draw(sf::RenderTarget& targetWindow) const override;
private:
    double Orientation;
    Vec2d Position;
    double Rayon;
    static double calculRayon();

};
