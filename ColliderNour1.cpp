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

    Vec2d Collider::minDistance(Collider to){
       double d1,d2;
       Vec2d v1,v2,v3,v4,v5,v6,v7,v8,v9;
       double worldSize = getAppConfig().simulation_world_size;
       auto width  = worldSize; // largeur
       auto height = worldSize; // hauteur
       d1= distance(Position,to.getPosition());
       v1=to.getPosition();
       for (int i(0);i<3;i++){
           for (int j(0);j<3;j++){
               if (i==0){
                   if(j==1){
                       v2=to.getPosition()+Vec2d(0,height);
                       d2=distance(Position,v2);
                       if (d2<d1) {
                           d1=d2;
                           v1=v2;
                       }
                   }
                   else if(j==2){
                       v3=to.getPosition()+Vec2d(0,-height);
                       d2=distance(Position,v3);
                       if(d2<d1) {
                           d1=d2;
                           v1=v3;
                       };
                   }
               }
               else if(i==1){
                   if (j==0){
                       v4=to.getPosition()+Vec2d(width,0);
                       d2=distance(Position,v4);
                       if(d2<d1) {
                           d1=d2;
                           v1=v4;
                       };

                   }
                   else if (j==1){
                       v5=to.getPosition()+Vec2d(width,height);
                       d2=distance(Position,v5);
                       if(d2<d1) {
                           d1=d2;
                           v1=v5;
                       };
                   }
                   else if (j==2){
                       v6=to.getPosition()+Vec2d(width,-height);
                       d2=distance(Position,v6);
                       if(d2<d1) {
                           d1=d2;
                           v1=v6;
                       };
                   }
               }
               else if (i==2){
                   if (j==0){
                       v7=to.getPosition()+Vec2d(-width,0);
                       d2=distance(Position,v7);
                       if(d2<d1) {
                           d1=d2;
                           v1=v7;
                       };
                   }
                   else if (j==1){
                       v8=to.getPosition()+Vec2d(-width,height);
                       d2=distance(Position,v8);
                       if(d2<d1) {
                           d1=d2;
                           v1=v8;
                       };
                   }
                   else if (j==2){
                       v9=to.getPosition()+Vec2d(-width,-height);
                       d2=distance(Position,v9);
                       if(d2<d1) {
                           d1=d2;
                           v1=v9;
                       };
                   }
               }
           }
       }
       Vec2d distanceMin(v1);
       return distanceMin;
    }
    Vec2d Collider::directionTo(Collider to){
        Vec2d retour;
        retour=to.getPosition() - minDistance(to);
        return retour;

    }
    void Collider::move(Vec2d& dx){
        Vec2d nouvellePosition(Centre+dx); //Position+=dx;
        Centre=nouvellePosition;
        clamping();

    }

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
    std::ostream& Collider::operator<<(std::ostream& os){
         os<<"Collider: position = "<<Position<<" radius = "<<Rayon<<std::endl;
         return os;
    }

};

    
