#include <Obstacle/Rock.hpp>
#include <Application.hpp>
#include <Random/Random.hpp>

double Rock::calculRayon() {
double rayon;
rayon = uniform(getAppConfig().simulation_world_size/50,2*getAppConfig().simulation_world_size/50);
if (rayon < 1) {
    rayon = 1;
}
return rayon;
}


Rock::Rock(const Vec2d& position)
: Collider(position, calculRayon()),
  Orientation(uniform(-PI,PI))

{}

void Rock::draw(sf::RenderTarget& targetWindow) const {
    sf::Sprite rockSprite;
        rockSprite.setTexture(getAppTexture(getAppConfig().rock_texture));
        rockSprite.setOrigin(rockSprite.getLocalBounds().width / 2, rockSprite.getLocalBounds().height / 2);
        rockSprite.setPosition(getPosition());  
        rockSprite.setRotation(Orientation * 180.0 / PI);       
        double scale = 2.0 * getRadius() / rockSprite.getLocalBounds().width;
        rockSprite.setScale(scale, scale);

        targetWindow.draw(rockSprite);
}
