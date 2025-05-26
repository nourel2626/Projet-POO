#include <Environment/CloudGenerator.hpp>
#include <Environment/Cloud.hpp>
#include <Application.hpp>


CloudGenerator::CloudGenerator():
TimeSinceLastCloud(sf::Time::Zero)
{}

Cloud* CloudGenerator::Generator(){
    double coord1(normal ( getAppConfig().simulation_world_size/2.0,
                       (getAppConfig().simulation_world_size/4.0)* (getAppConfig().simulation_world_size/4.0)));
    double coord2(normal ( getAppConfig().simulation_world_size/2.0,
                       (getAppConfig().simulation_world_size/4.0)* (getAppConfig().simulation_world_size/4.0)));
    Vec2d position(coord1, coord2);
    double rayon(uniform( getAppConfig().cloud_min_size , getAppConfig().cloud_max_size));
    Cloud* cloud=new Cloud(position,rayon);
    return  cloud;
}


void CloudGenerator::update(sf::Time dt){
    TimeSinceLastCloud += dt;

    // Si le temps écoulé dépasse le délai de génération
    if (TimeSinceLastCloud.asSeconds() > getAppConfig().cloud_generator_delta) {
        TimeSinceLastCloud = sf::Time::Zero;

        // Vérification des conditions : sécheresse + température + limite de nuages
        auto& env = getAppEnv();
        if (env.getDroughtDuration().asSeconds() > getAppConfig().environment_drought_duration
            && env.getTemperature() < getAppConfig().environment_rain_temperature
            && env.getCloudCount() < getAppConfig().environment_max_clouds) {

            // Ajout du nuage à l'environnement
            Cloud* cloud(Generator());
            env.addCloud(cloud);
        }
    }
}


