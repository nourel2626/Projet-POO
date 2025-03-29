#include "chasingautomaton.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>

    ChasingAutomaton::ChasingAutomaton(Vec2d position, double magnitudeVitesse, Vec2d positionCible, Vec2d direction)
        :collider(position,CHASING_AUTOMATON_RADIUS)
    {
        MagnitudeVitesse=magnitudeVitesse;
        PositionCible=positionCible;
        Direction=direction;


    }
    double ChasingAutomaton::getStandardMaxSpeed(){
        return CHASING_AUTOMATON_MAX_SPEED;
    }
    double ChasingAutomaton::getMass(){
        return CHASING_AUTOMATON_MASS;
    }
    void ChasingAutomaton::setTargetPosition(Vec2d Position){
        PositionCible=Position;
    }
    Vec2d ChasingAutomaton::getSpeedVector(){
        return MagnitudeVitesse*Direction;
    }
    void ChasingAutomaton::update(sf::Time dt){
        Vec2d f(ForceAttraction(moyenne));
        Vec2d acceleration(f/getMass());
        Vec2d nouvelle_vitesse(getSpeedVector()+acceleration*dt.asSeconds());
        Vec2d nouvelle_direction(nouvelle_vitesse.normalised());
        if (nouvelle_vitesse.length()>getStandardMaxSpeed()){
            nouvelle_vitesse=nouvelle_direction*getStandardMaxSpeed();
        }
        Vec2d nouvelle_position(collider.getPosition()+ nouvelle_vitesse* dt.asSeconds());
        Vec2d dx(nouvelle_position - collider.getPosition());
        collider.move(dx);

    }
    Vec2d ChasingAutomaton::ForceAttraction(Deceleration deceleration){
        Vec2d forceAttraction,vTarget,toTarget;
        toTarget= PositionCible - collider.getPosition();
        double decelerationNum;
        if(deceleration==forte){
            decelerationNum=0.9;
        }
        else if (deceleration==moyenne){
            decelerationNum=0.6;
        }
        else{
            decelerationNum=0.3;
        }

        double speed(std::min((toTarget.length()/decelerationNum),getStandardMaxSpeed()));
        vTarget= (toTarget/toTarget.length())*speed;
        forceAttraction= vTarget - getSpeedVector();
        return forceAttraction;

    }
    void ChasingAutomaton::draw(sf::RenderTarget &targetWindow){
        sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
        auto image_to_draw(buildSprite(collider.getPosition(),collider.getRadius()*2,texture));
        targetWindow.draw(image_to_draw);
    };







