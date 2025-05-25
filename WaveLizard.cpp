#include <Animal/NeuronalScorpion/WaveLizard.hpp>
#include <Environment/Wave.hpp>
#include <Environment/Wave.hpp>
#include <Application.hpp>

WaveLizard::WaveLizard(Vec2d position, double energie, bool femelle,double taille)
    : Lizard(position, energie, femelle, taille)
{}

WaveLizard::WaveLizard(Vec2d position)
    : Lizard(position)
{}

void WaveLizard::emission() {
    Wave* wave = new Wave(getPosition(), getAppConfig().wave_default_energy, getAppConfig().wave_default_radius,
                         getAppConfig().wave_default_mu, getAppConfig().wave_default_speed);
    getAppEnv().addWave(wave);
}
void WaveLizard::update(sf::Time dt) {
    Lizard::update(dt);
    Clock += dt;

    if (Clock.asSeconds() >= (1.0 / getAppConfig().wave_lizard_frequency)) {
        emission();
        Clock = sf::Time::Zero;
    }
}
