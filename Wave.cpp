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

bool Wave::containsAngle(const std::pair<double,double>& arc, double angle) {
    double start = arc.first;
    double end = arc.second;

    return (angle >= start) and (angle <= end);
}

    bool Wave::distanceToObstacle(const Vec2d& pos) {
        double length = (pos - getPosition()).length();
        double r = Rayon;
        double marge = getAppConfig().wave_on_wave_marging;

        return (length >= r - marge && length <= r + marge);
    }

void Wave::update(sf::Time dt) {
    Time += dt;
    bool arcs_changed = true;
    size_t i = 0;
    if (!(getAppEnv().getObstacles().empty())){
        while (arcs_changed) {
            std::pair<double, double> arc;
            bool erased = false;
            arc=Arcs[i];
            for (const auto& obstacle : getAppEnv().getObstacles()) {
                Vec2d obstacle_distance = obstacle->getPosition() - Origine;
                double angleToObstacle = obstacle_distance.angle();
                double alpha;
                alpha = 2 * std::atan2(obstacle->getRadius(),(Rayon + obstacle->getRadius()));
                if ((containsAngle(arc,angleToObstacle)) and (distanceToObstacle(obstacle->getPosition()))) {
                    Arcs.emplace_back(arc.first,angleToObstacle-0.5*alpha);
                    Arcs.emplace_back(angleToObstacle+0.5*alpha,arc.second);
                    Arcs.erase(Arcs.begin()+i);
                    erased = true;
                    break;
                }

            }
            if (!erased) {
                i += 1;
            }
            if (i==Arcs.size()) {
                arcs_changed=false;
            }
        }
        //Arcs.erase(Arcs.begin(), Arcs.begin()+initial_size);
    }
    Rayon = RayonInitial + Vitesse * Time.asSeconds();
  //  Arcs = newArcs;


}
