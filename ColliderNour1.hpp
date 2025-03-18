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

    private:
        Vec2d Centre;
        double Rayon;
};
