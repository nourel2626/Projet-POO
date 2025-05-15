#include <Environment/Wave.hpp>
#include <Application.hpp>

Wave::Wave(const Vec2d& origine, double energie, double rayon, double mu, double vitesse)
    : Collider(origine, rayon),
      Origine(origine),
      RayonInitial(rayon),
      Rayon(rayon),
      Energie(energie),
      µ(mu),
      Vitesse(vitesse),
      Time(sf::Time::Zero)
{
    std::pair<double, double> arc = {-PI,PI};
    Arcs.push_back(arc);
}


void Wave::draw(sf::RenderTarget& targetWindow) const {
    for (auto arc : Arcs) {
        Arc circle = buildArc(
            arc.first/DEG_TO_RAD,
            arc.second/DEG_TO_RAD,
            Rayon,
            Origine,
            sf::Color::Black,
            0,
            getAppConfig().wave_intensity_thickness_ratio * getIntensity()
        );
        targetWindow.draw(circle);
    }
}

void Wave::setRayon(double rayon){
    Rayon = rayon;
}

double Wave::getIntensity() const {
    double e = Energie * std::exp(-Rayon / µ);
    return e / (2 * PI * Rayon);
}
/*bool Wave::containsAngle(double angle, double start, double end) {
    return angle >= start && angle <= end;
}
*/
bool containsAngle(const std::pair<double,double>& arc, double angle) {
    double start = arc.first;
    double end = arc.second;

    // Normaliser angle dans [0, 2π[
    while (angle < 0) angle += 2 * M_PI;
    while (angle >= 2 * M_PI) angle -= 2 * M_PI;

    // Normaliser start et end aussi
    while (start < 0) start += 2 * M_PI;
    while (start >= 2 * M_PI) start -= 2 * M_PI;

    while (end < 0) end += 2 * M_PI;
    while (end >= 2 * M_PI) end -= 2 * M_PI;

    if (start <= end) {
        return angle >= start && angle <= end;
    } else {
        // cas arc "enroulé" sur zéro (ex: start=5.5, end=0.5)
        return angle >= start || angle <= end;
    }
}


/*void Wave::update(sf::Time dt) {
   Time += dt;
   Rayon = RayonInitial + Vitesse * Time.asSeconds();
}
*/
void Wave::update(sf::Time dt) {
    Time += dt;
    Rayon = RayonInitial + Vitesse * Time.asSeconds();

    std::vector<std::pair<double, double>> newArcs;

    for (const auto& arc : Arcs) {
        bool arcFragmented = false;

        for (auto obstacle : getAppEnv().getObstacles()) {
            Vec2d direction = obstacle->getPosition() - Origine;
            double angleToObstacle = direction.angle();

            // On teste si l'obstacle est dans l'arc (d’après sa position)
            if (containsAngle(arc,angleToObstacle)) {
                // Et s’il est en collision ou à l'intérieur de l’onde
                if (isColliding(*obstacle) || isColliderInside(*obstacle)) {
                    // Fragmentation de l'arc
                    double R = Rayon;
                    double r = obstacle->getRadius();
                    double alpha = 2 * std::atan2(r, R + r);  // Angle de fragmentation

                    double start1 = arc.first;
                    double end1 = angleToObstacle - alpha;

                    double start2 = angleToObstacle + alpha;
                    double end2 = arc.second;

                    if (end1 > start1)
                        newArcs.emplace_back(start1, end1);

                    if (end2 > start2)
                        newArcs.emplace_back(start2, end2);

                    arcFragmented = true;
                    break; // on arrête après le premier obstacle trouvé dans cet arc
                }
            }
        }

        if (!arcFragmented) {
            newArcs.emplace_back(arc.first, arc.second);

        }
    }

    Arcs = newArcs;
}
