
#pragma once
#include <Utility/Vec2d.hpp>
#include <Obstacle/Collider.hpp>

enum Deceleration{forte, moyenne, faible};
class ChasingAutomaton : public Collider
{
public:
    ChasingAutomaton();
    ChasingAutomaton(const Vec2d& position);
    double getStandardMaxSpeed();
    double getMass();
    void setTargetPosition(Vec2d Position);
    Vec2d getSpeedVector();
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow);

private:
    Vec2d Direction;
    double MagnitudeVitesse;
    Vec2d PositionCible;
    Vec2d ForceAttraction(Deceleration deceleration);
};




#endif // CHASINGAUTOMATON_H
