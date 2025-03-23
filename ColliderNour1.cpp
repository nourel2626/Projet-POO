/*
 * POOSV 2025
 */

#include <Application.hpp>
#include <Obstacle/Collider.hpp>
#include <Utility/Utility.hpp>
#include <cassert>
#include <algorithm>

Collider::Collider(Collider const& autre)
    : Position(autre.Position), Rayon(autre.Rayon)
{}

Collider::Collider(Vec2d position, double rayon){
    if (rayon <0){
        throw std::invalid_argument("Le rayon ne peut pas être négatif !!");
    }
    Rayon=rayon;
    Position=position;
}

double Collider::distanceTo (Vec2d to){
    return (directionTo(to)).length();
}

Vec2d Collider::getPosition() const&{
    return Position;
}
double Collider::getRadius()const{
    return Rayon;
}

void Collider::move (Vec2d dx){
    this -> Position = this -> Position + dx;
}


Collider& Collider::operator=(Collider& x){
    Rayon = x.getRadius();
    Position = x.getPosition();
   return x;
}

bool Collider::operator>(Collider& body1) {
   return body1.isPointInside(this->Position);
}

bool Collider::operator>(Vec2d p) {
    return this->isPointInside(p);
}
Vec2d Collider::directionTo(Vec2d to){
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize; // largeur
    auto height = worldSize; // hauteur

    std::vector <Vec2d> candidats = {
        to,
        to + Vec2d(0, height),
        to + Vec2d(0, -height),
        to + Vec2d(width, 0),
        to + Vec2d(-width, 0),
        to + Vec2d(width, height),
        to + Vec2d(width, -height),
        to + Vec2d(-width, -height),
        to + Vec2d(-width, height),
    };
    Vec2d bestDirection = candidats[0] - Position;
    double bestDistance = bestDirection.length();
    for (const auto& i : candidats) {
            Vec2d direction = i - Position;
            double distance = direction.length();

            if (distance < bestDistance) {
                bestDirection = direction;
                bestDistance = distance;
            }
        }

        return bestDirection;
    }


bool Collider::isColliderInside(Collider other) {
    return other.getRadius() <= this->Rayon && distanceTo(other.getPosition()) <= (this->Rayon - other.getRadius());
}



bool Collider::isPointInside(Vec2d p){
 if (distanceTo(directionTo(p)) <= (this -> Rayon)){
        return true;
} else {
        return false;
}
}
void Collider::clamping(){
      double worldSize = getAppConfig().simulation_world_size;
      auto width  = worldSize; // largeur
      auto height = worldSize; // hauteur

      double x,y;
      while(Position.operator[](0)<0 or Position[1]<0){
          if (Position.operator[](0)<0){
              x=Position.operator[](0)+width; // On dit que la première coordonnée est selon l'axe x
          }
          if (Position.operator[](0)>width){
              x=Position.operator[](0)-width;
          }
          if (Position.operator[](1)<0){
              y=Position.operator[](1)+height; // On dit que la première coordonnée est selon l'axe x
          }
          if (Position.operator[](1)>height){
              y=Position.operator[](1)-height;
          }

}
      Vec2d newPosition(x,y);
      Position=newPosition;

Vec2d directionTo(Collider to){
        double x(to.operator[](0),y(to.operator[](1));
        x=Position.operator[](0)-x;
        y=Position.operator[](1)-y;
        Vec2d retour(x,y);
        return retour;
    }


};

    
