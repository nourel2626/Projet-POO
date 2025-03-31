/*
 * POOSV 2025
 */

#pragma once

#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <ostream>

/*!
 * @brief A collider is defined by a radius
 * and a position in a toric world.
 *
 * @note radius must be >= 0.
 *
 * @note The "true" direction/distance denotes the
 * direction/distance for the shortest path between
 * the two considered points. (When considering a
 * body, we actually use its center as the source/
 * destination point.)
 */
class Collider
{
    public:
        Vec2d getPosition() const&;
        double getRadius() const;
        Collider(Vec2d centre, double rayon);
        void clamping();
        Collider(Collider const& autre);
        Collider& operator=(Collider& x);
        Vec2d directionTo(Vec2d to);
        double distanceTo(Vec2d to);
        void move(const Vec2d& dx);
        bool isColliderInside (Collider other);
        bool isPointInside (Vec2d p);
        bool operator>(Collider& body1);
        bool operator>(Vec2d p);
        Vec2d directionTo(Collider to);
        //void move(Vec2d& dx);
        bool isColliding(Collider other);
        bool operator|(Collider& body1);
        void operator+=(Vec2d dx);
        double distanceTo(Collider to);
    private:
        Vec2d Position;
        double Rayon;
};
        std::ostream& operator<<(std::ostream& os,Collider body);
