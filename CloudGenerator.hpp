#pragma once

#include "Obstacle/Collider.hpp"
#include "Random/Random.hpp"
#include "Environment/Environment.hpp"
#include <Utility/Vec2d.hpp>

/**
 * \brief Classe responsable de générer des nuages à intervalles réguliers.
 *
 * La classe CloudGenerator gère l’apparition de nouveaux nuages dans l’environnement
 * en fonction du temps écoulé. Elle peut être mise à jour à chaque cycle de simulation.
 */
class CloudGenerator {
public:
    /**
     * \brief Constructeur de la classe CloudGenerator.
     * Initialise le générateur avec un temps écoulé à zéro.
     */
    CloudGenerator();

    /**
     * \brief Met à jour l'état du générateur de nuages.
     * \param dt Temps écoulé depuis la dernière mise à jour.
     * Si suffisamment de temps s’est écoulé, un nuage peut être généré.     */
    void update(sf::Time dt);

    /**
     * \brief Génère un nouveau nuage.
     * \return Un pointeur vers un objet Cloud nouvellement généré.
     */
    Cloud* Generator();

private:
    sf::Time TimeSinceLastCloud;
};
