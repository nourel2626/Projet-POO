/*
 * POOSV 2025
 */

#include <Application.hpp>
#include <Obstacle/Collider.hpp>
#include <Utility/Utility.hpp>
#include <cassert>
#include <algorithm>

Collider::Collider(Collider const& autre)
    : Centre(autre.Centre), Rayon(autre.Rayon)
{}



Vec2d Collider::getPosition() const&{
    return Centre;
}
double Collider::getRadius()const{
    return Rayon;
}

Collider& Collider::operator=(Collider& x){
    Rayon = x.getRadius();
    Centre = x.getPosition();
   return x;
}

Collider::Collider(Vec2d centre, double rayon){
    if (rayon <0){
        throw std::invalid_argument("Le rayon ne peut pas être négatif !!");
    }
    Rayon=rayon;
    Centre=centre;
};
    void Collider::clamping(){
        double worldSize = getAppConfig().simulation_world_size;
        auto width  = worldSize; // largeur
        auto height = worldSize; // hauteur

        double x,y;
        while(Centre.operator[](0)<0 or Centre[1]<0){
            if (Centre.operator[](0)<0){
                x=Centre.operator[](0)+width; // On dit que la première coordonnée est selon l'axe x
            }
            if (Centre.operator[](0)>width){
                x=Centre.operator[](0)-width;
            }
            if (Centre.operator[](1)<0){
                y=Centre.operator[](1)+height; // On dit que la première coordonnée est selon l'axe x
            }
            if (Centre.operator[](1)>height){
                y=Centre.operator[](1)-height;
            }

        }
        Vec2d newCentre(x,y);
        Centre=newCentre;


    };
    Vec2d directionTo(Collider to){
        double x(to.operator[](0),y(to.operator[](1));
        x=Center.operator[](0)-x;
        y=Center.operator[](1)-y;
        Vec2d retour(x,y);
        return retour;
    }

