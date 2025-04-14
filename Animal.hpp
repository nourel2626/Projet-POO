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
        Animal(const Vec2d& position, double taille, double energie, bool femelle);
        virtual double getStandardMaxSpeed();
        virtual double getMass();
        void setTargetPosition(Vec2d Position);
        Vec2d getSpeedVector();
        void update(sf::Time dt);
        virtual void draw(sf::RenderTarget& targetWindow);
        double getViewRange ();
        double getViewDistance();
        double getRotation();
        void setRotation (double angle);
        void drawVision(sf::RenderTarget& targetWindow);
        virtual double getRandomWalkRadius() const;
        virtual double getRandomWalkDistance () const;
        virtual double getRandomWalkJitter() const;
        Vec2d randomWalk();
        Vec2d convertToGlobalCoord(const Vec2d& local) const;
        bool isTargetInSight(Vec2d positionCible);
        virtual sf::Texture& getTexture();
    private:
        double Angle;
        double DistanceVision;
        Vec2d Direction;
        double MagnitudeVitesse;
        Vec2d PositionCible;
       Vec2d ForceAttraction(Deceleration deceleration);
       Vec2d current_target = Vec2d(1, 0);
 bool estFemelle;
    };




