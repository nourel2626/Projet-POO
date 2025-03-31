
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

double Collider::distanceTo (Collider to){
    return (directionTo(to.Position)).length();
}

Vec2d Collider::getPosition() const&{
    return Position;
}
double Collider::getRadius()const{
    return Rayon;
}

void Collider::move (const Vec2d& dx){
 Position = Position +  dx;
 clamping ();
}


Collider& Collider::operator=(Collider& x){
    Rayon = x.getRadius();
    Position = x.getPosition();
   return x;
}

bool Collider::operator>(Collider& body1) {
   return isColliderInside(body1);
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
    bool retour(false);
    if (this ->Rayon<other.getRadius()){
        retour= false;
       }
    if((other.getRadius() <= Rayon) && (distanceTo(other.getPosition()) <= (this->Rayon - other.getRadius()))) {
        retour= true;
    }
    return retour;

}



bool Collider::isPointInside(Vec2d p){
    bool retour(false);
    if (distanceTo(p) <= (Rayon)){
        retour= true;
    }
    else {
        retour= false;
    }
    return retour;
}
/*
bool Collider::isPointInside(Vec2d p) {
    // Calculer la distance entre le centre du Collider (this) et le point p
    double distance = this->distanceTo(p);

    // Vérifier si la distance est inférieure ou égale au rayon du Collider
    return distance <= this->Rayon;
}
*/


void Collider::clamping(){
      double worldSize = getAppConfig().simulation_world_size;
      auto width  = worldSize; // largeur
      auto height = worldSize; // hauteur

      double x = Position.x();
      double y = Position.y();
      while(x<0 or y<0 or x>width or y>height){
          if (x<0){
              x=x+width;
          }
          if (x>width){
              x=x-width;
          }
          if (y<0){
              y=y+height;
          }
          if (y>height){
              y=y-height;
          }

      }
      Vec2d newPosition(x,y);
      Position=newPosition;
}

    Vec2d Collider::directionTo(Collider to){   //faire fonction minDistance pour optimiser
        double worldSize = getAppConfig().simulation_world_size;
        auto width  = worldSize; // largeur
        auto height = worldSize; // hauteur

        std::vector <Vec2d> candidats = {
            to.getPosition(),
            to.getPosition() + Vec2d(0, height),
            to.getPosition() + Vec2d(0, -height),
            to.getPosition() + Vec2d(width, 0),
            to.getPosition() + Vec2d(-width, 0),
            to.getPosition() + Vec2d(width, height),
            to.getPosition() + Vec2d(width, -height),
            to.getPosition() + Vec2d(-width, -height),
            to.getPosition() + Vec2d(-width, height),
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

 /*   void Collider::move(Vec2d& dx){
        Vec2d nouvellePosition(Position+dx); //Position+=dx;
        Position=nouvellePosition;
        clamping();

    }
*/
    bool Collider::isColliding(Collider other){
        bool retour(false);
        double rayonTotal(Rayon+other.getRadius());
        double distanceTotal;
        distanceTotal= distance(Position,other.getPosition());
        if (distanceTotal<rayonTotal)
            {retour= true;}
        else
            {retour= false;}
        return retour;
    }
    bool Collider::operator|(Collider& body1){
        return isColliding(body1);
    }
    std::ostream& operator<<(std::ostream& os, Collider body){
         os<<"Collider: position = "<<body.getPosition()<<" radius = "<<body.getRadius();//<<std::endl;
         return os;
    }

    void Collider::operator+=(Vec2d dx){
        Position= Position+dx;
    }

