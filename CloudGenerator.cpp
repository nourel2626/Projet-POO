#include <Environment/CloudGenerator.hpp>
#include <Application.hpp>
CloudGenerator::CloudGenerator(const Vec2d& position, double taille)
    : Collider(position,taille)
    { TimeSinceLastCloud=sf::Time::Zero;
    }

void CloudGenerator::update(sf::Time dt){
    TimeSinceLastCloud += dt;
    if (TimeSinceLastCloud > sf::seconds(getAppConfig().cloud_generator_delta)){
        TimeSinceLastCloud = sf::Time::Zero;
        normal( getAppConfig().simulation_world_size/2.0, (getAppConfig().simulation_world_size/4.0)* (getAppConfig().simulation_world_size*4.0));

    }
}
/*
void CloudGenerator::update(sf::Time dt){
    TimeSinceLastCloud += dt;

    // Si le temps écoulé dépasse le délai de génération
    if (TimeSinceLastCloud > sf::seconds(getAppConfig().cloud_generator_delta)) {
        TimeSinceLastCloud = sf::Time::Zero;

        // Vérification des conditions : sécheresse + température + limite de nuages
        auto& env = getAppEnv();
        if (env.getDroughtDuration() > sf::seconds(getAppConfig().environment_drought_duration)
            && Environment::getTemperature() < getAppConfig().environment_rain_temperature
            && env.getCloudCount() < getAppConfig().environment_max_clouds) {

            // Calcul de la moyenne et variance
            double mu = getAppConfig().simulation_world_size / 2.0;
            double sigma2 = std::pow(getAppConfig().simulation_world_size / 4.0, 2);

            // Position générée selon une loi normale
            Vec2d position(normal(mu, sigma2), normal(mu, sigma2));

            // Taille du nuage entre les bornes min et max
            double taille = uniform(getAppConfig().cloud_min_size, getAppConfig().cloud_max_size);

            // Ajout du nuage à l'environnement
            env.addGenerator(std::make_unique<CloudGenerator>(position, taille));
        }
    }
}

*/
