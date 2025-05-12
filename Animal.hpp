#pragma once
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Obstacle/Collider.hpp>
#include "Random/Random.hpp"
#include <list>
#include <Environment/Environment.hpp>
#include <Environment/OrganicEntity.hpp>

enum Deceleration{forte, moyenne, faible};
enum State{
    FOOD_IN_SIGHT, // nourriture en vue
    FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
    RUNNING_AWAY,  // en fuite
    MATE_IN_SIGHT, // partenaire en vue
    MATING,        // vie privée (rencontre avec un partenaire!)
    GIVING_BIRTH,  // donne naissance
    WANDERING,     // déambule
};
struct Pregnancy{
    bool Enceinte = false;
    sf::Time Gestation = sf::Time::Zero;
};

class Animal : public OrganicEntity{


    public:
        Animal();
        Animal(const Vec2d& position, double energie, bool femelle, sf::Time longevite, double taille);
        virtual double getStandardMaxSpeed() const=0;
        virtual double getMass() const=0;
        void setTargetPosition(Vec2d Position);
        virtual Vec2d getSpeedVector()const ;
        virtual void update(sf::Time dt) override;
        virtual void draw(sf::RenderTarget& targetWindow) const override;
        virtual void drawDebug(sf::RenderTarget& targetWindow) const;
        virtual void drawAnnulus(sf::RenderTarget& targetWindow) const;
        virtual OrganicEntity* updateState();
        virtual void directionMove(sf::Time dt, Vec2d f);
        virtual double getViewRange () const;
        virtual double getViewDistance() const;
        virtual double getRotation() const;
        void setRotation (double angle);
        virtual void drawVision(sf::RenderTarget& targetWindow) const;
        virtual double getRandomWalkRadius() const=0;
        virtual double getRandomWalkDistance () const=0;
        virtual double getRandomWalkJitter() const=0;
        Vec2d randomWalk();
        Vec2d convertToGlobalCoord(const Vec2d& local) const;
        virtual bool isTargetInSight(Vec2d positionCible);
        virtual sf::Texture& getTexture()const override;
        virtual bool getSex() const;
        void setDirection(Vec2d direction);
        virtual Vec2d getDirection() const;
        void setMagnitudeVitesse(double magnitude);
        Vec2d ForceAttraction(Deceleration deceleration);
        virtual double getMaxSpeed() const=0;
//        virtual bool matable(OrganicEntity const* other) const override;
//        virtual bool canMate(Scorpion const* scorpion) const override;
//        virtual bool canMate(Lizard const* lizard) const override;
//        virtual bool canMate(Cactus const* food) const override;
        virtual double getEnergyLossFactor() const=0;
        void analyzeEnvironment();
        bool getEnceinte() const;
        void setEnceinte(bool enceinte);
        State getEtat() const ;
        sf::Time getGestation() const;
    private:
        double Angle;
        double DistanceVision;
        Vec2d Direction;
        double MagnitudeVitesse;
        Vec2d PositionCible;
        Vec2d current_target = Vec2d(1, 0);
        bool Femelle;
        State Etat;
        std::list<OrganicEntity*> Predateurs;
        std::list<OrganicEntity*> Cibles;
        std::list<OrganicEntity*> Mates;
        Pregnancy Grossese;
        sf::Time TempsDepuisEtatChange;
    };



