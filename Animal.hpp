#pragma once
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Obstacle/Collider.hpp>

enum Deceleration{forte, moyenne, faible};
class Animal :public Collider{


    public:
        Animal();
        Animal(const Vec2d& position);
        double getStandardMaxSpeed();
        double getMass();
        void setTargetPosition(Vec2d Position);
        Vec2d getSpeedVector();
        void update(sf::Time dt);
        void draw(sf::RenderTarget& targetWindow);
        double getViewRange ();
        double getViewDistance();
        double getRotation();
        void setRotation (double angle);
        void drawVision(sf::RenderTarget& targetWindow);
        bool isTargetInSight(Vec2d positionCible);
    private:
        double Angle;
        double DistanceVision;
        Vec2d Direction;
        double MagnitudeVitesse;
        Vec2d PositionCible;
       Vec2d ForceAttraction(Deceleration deceleration);
    };





