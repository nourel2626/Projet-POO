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

        // Charge la texture depuis AppTexture
        rockSprite.setTexture(getAppTexture(getAppConfig().rock_texture));

        // Centre le sprite sur son origine
        rockSprite.setOrigin(rockSprite.getLocalBounds().width / 2, rockSprite.getLocalBounds().height / 2);

        // Positionne et oriente le sprite
        rockSprite.setPosition(getPosition());  // getPosition() hérité de Collider
        rockSprite.setRotation(Orientation * 180.0 / PI);       // Conversion en degrés

        // Mise à l’échelle (le sprite par défaut fait généralement 100x100 px)
        double scale = 2.0 * getRadius() / rockSprite.getLocalBounds().width;
        rockSprite.setScale(scale, scale);

        targetWindow.draw(rockSprite);
}
