#ifndef CHASINGAUTOMATON_H
#define CHASINGAUTOMATON_H
#pragma once
#include <Utility/Vec2d.hpp>
#include <Obstacle/Collider.hpp>

enum Deceleration{forte, moyenne, faible};
class ChasingAutomaton
{
public:
    ChasingAutomaton();
    ChasingAutomaton(Vec2d position, double magnitudeVitesse = 0, Vec2d positionCible = {0,0}, Vec2d direction = {1,0});
    double getStandardMaxSpeed();
    double getMass();
    void setTargetPosition(Vec2d Position);
    Vec2d getSpeedVector();
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow);

private:
    Collider collider;
    Vec2d Direction;
    double MagnitudeVitesse;
    Vec2d PositionCible;
    Vec2d ForceAttraction(Deceleration deceleration);
};


#endif // CHASINGAUTOMATON_H
