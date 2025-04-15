#pragma once
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Obstacle/Collider.hpp>
#include "Random/Random.hpp"
#include <list>
#include <Environment/Environment.hpp>
#include <Environment/OrganicEntity.hpp>

enum Deceleration{forte, moyenne, faible};
enum Etat{
    FOOD_IN_SIGHT, // nourriture en vue
    FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
    RUNNING_AWAY,  // en fuite
    MATE_IN_SIGHT, // partenaire en vue
    MATING,        // vie privée (rencontre avec un partenaire!)
    GIVING_BIRTH,  // donne naissance
    WANDERING,     // déambule
};

class Animal : public OrganicEntity{


    public:
        Animal();
        Animal(const Vec2d& position, double taille, double energie, bool femelle);
        virtual double getStandardMaxSpeed() const=0;
        virtual double getMass() const=0;
        void setTargetPosition(Vec2d Position);
        Vec2d getSpeedVector()const ;
        void update(sf::Time dt) override;
        void draw(sf::RenderTarget& targetWindow) const override;
        Etat updateState();
        void directionMove(sf::Time dt, Vec2d f);
        double getViewRange () const;
        double getViewDistance() const;
        double getRotation() const;
        void setRotation (double angle);
        void drawVision(sf::RenderTarget& targetWindow) const;
        virtual double getRandomWalkRadius() const=0;
        virtual double getRandomWalkDistance () const=0;
        virtual double getRandomWalkJitter() const=0;
        Vec2d randomWalk();
        Vec2d convertToGlobalCoord(const Vec2d& local) const;
        virtual bool isTargetInSight(Vec2d positionCible);
        virtual sf::Texture& getTexture()const=0;
        bool getSex() const;
        void setDirection(Vec2d direction);
        Vec2d getDirection() const;
        void setMagnitudeVitesse(double magnitude);
        Vec2d ForceAttraction(Deceleration deceleration);
        virtual bool eatableBy(Scorpion const* scorpion) const=0;
        virtual bool eatableBy(Lizard const* lizard) const=0;
        virtual bool eatableBy(Cactus const* cactus) const=0;
        virtual bool eatable(OrganicEntity const* entity) const=0;
    private:
        double Angle;
        double DistanceVision;
        Vec2d Direction;
        double MagnitudeVitesse;
        Vec2d PositionCible;
        Vec2d current_target = Vec2d(1, 0);
        bool Femelle;
    };



