#pragma once
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Obstacle/Collider.hpp>
#include "Random/Random.hpp"
#include <list>
#include <Environment/Environment.hpp>

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
        double getRandomWalkRadius() const;
        double getRandomWalkDistance () const;
        double getRandomWalkJitter() const;
        Vec2d randomWalk(Vec2d current_target);
        Vec2d convertToGlobalCoord(const Vec2d& local) const;
        bool isTargetInSight(Vec2d positionCible);
    private:
        double Angle;
        double DistanceVision;
        Vec2d Direction;
        double MagnitudeVitesse;
        Vec2d PositionCible;
       Vec2d ForceAttraction(Deceleration deceleration);
       Vec2d current_target = Vec2d(1, 0);
    };





