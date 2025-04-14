#include "Environment/OrganicEntity.hpp"

#include "OrganicEntity.hpp"

 OrganicEntity::OrganicEntity(Vec2d const& position, double taille,double energie)
    : Collider(position,taille/2.0),
    energy(energie)
 {}
