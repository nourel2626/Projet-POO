#include "Obstacle/Collider.hpp"
#include "Random/Random.hpp"
#include "Environment/Environment.hpp"

class CloudGenerator : public Collider{
public:
    CloudGenerator(const Vec2d& position, double taille);

    void update (sf::Time dt);
private:
    sf::Time TimeSinceLastCloud;
};
