pragma once
#include <Animal/Lizard.hpp>

/*!
 * @class WaveLizard
 *
 * @brief Représente un lézard capable d’émettre des ondes.
 *
 * Hérite de la classe Lizard. Ce lézard possède un comportement
 * d’émission périodique d’ondes, simulé via une horloge interne.
 */
class Wave;
class WaveLizard : public Lizard {
public:
    /*!
     * @brief Constructeur du WaveLizard.
     *
     * @param position Position initiale dans l’environnement.
     * @param energie Énergie initiale du lézard.
     * @param femelle true si le lézard est femelle, false s’il est mâle.
     * @param taille Taille du lézard.
     */
    WaveLizard(Vec2d position, double energie, bool femelle, double taille);

    /*!
     * @brief Constructeur simplifié du WaveLizard.
     *
     * @param position Position initiale dans l’environnement.
     */
    WaveLizard(Vec2d position);

    /*!
     * @brief Émet une onde à partir de la position actuelle.
     *
     * Crée une instance de Wave, qui sera ajoutée à l’environnement.
     */
    void emission();

    /*!
     * @brief Met à jour l’état interne du lézard.
     *
     * Incrémente l’horloge interne et déclenche périodiquement l’émission d’ondes.
     *
     * @param dt Durée écoulée depuis la dernière mise à jour.
     */
    void update(sf::Time dt) override;

private:
    sf::Time Clock = sf::Time::Zero;
};
