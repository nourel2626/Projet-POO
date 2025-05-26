#pragma once

#include <Obstacle/Collider.hpp>
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include <Environment/Environment.hpp>
#include <Obstacle/Rock.hpp>
#include <vector>
#include <list>

/*!
 * @class Wave
 *
 * @brief Représente une onde circulaire se propageant depuis un point d'origine.
 *
 * Hérite de Collider.
 * Une onde possède une position d'origine, une énergie, un coefficient d'atténuation (µ),
 * une vitesse de propagation, un rayon initial et un rayon courant.
 * Elle peut être partiellement bloquée par des obstacles, ce qui génère des arcs visibles.
 */
class Wave : public Collider {
public:
    /*!
     * @brief Constructeur de l'onde.
     *
     * @param origine Position d'origine de l'onde.
     * @param energie Énergie initiale portée par l'onde.
     * @param rayon Rayon initial de l'onde.
     * @param µ Coefficient d'atténuation de l'énergie.
     * @param vitesse Vitesse de propagation de l'onde.
     */
    Wave(const Vec2d& origine, double energie, double rayon, double µ, double vitesse);

    /*!
     * @brief Met à jour l'état de l'onde.
     *
     * @param dt Durée écoulée depuis la dernière mise à jour.
     */
    void update(sf::Time dt);

    /*!
     * @brief Dessine l'onde et ses arcs visibles dans la fenêtre cible.
     *
     * @param targetWindow Fenêtre cible
     */
    void draw(sf::RenderTarget& targetWindow) const override;

    /*!
     * @brief Renvoie l’intensité actuelle de l’onde.
     *
     * @return Intensité actuelle.
     */
    double getIntensity() const;

    /*!
     * @brief Définit un nouveau rayon courant pour l'onde.
     *
     * @param rayon Nouveau rayon à appliquer.
     */
    void setRayon(double rayon);

    /*!
     * @brief Vérifie si un angle donné appartient à un arc angulaire.
     *
     * @param arc Arc sous forme de (angle début, angle fin) en radians.
     * @param angle Angle à tester
     * @return true si l’angle appartient à l’arc, false sinon.
     */
    bool containsAngle(const std::pair<double, double>& arc, double angle) const;

    /*!
     * @brief Calcule si la distance entre l’origine de l’onde et un point est inférieure au rayon courant.
     *
     * Utile pour déterminer si l’onde touche une entité.
     *
     * @param pos Position à tester.
     * @return true si la position est atteinte par l’onde, false sinon.
     */
    bool distanceToObstacle(const Vec2d& pos) const;

    /*!
     * @brief Destructeur par défaut.
     */
    virtual ~Wave() = default;
    /*!
     * @brief Renvoies l'origine de 'londe
     *
     * @return l'origine de l'onde
     */
    Vec2d getOrigine() const;
    /*!
     * @brief Renvoies l'intensité de l'onde à une position précise
     *
     * @param position la position à laquelle on veut connaître l'intensité de l'onde
     * @return l'intensité de l'onde à la position position
     */
    double getIntensityAt(const Vec2d& position) const;

private:
    Vec2d Origine;
    double RayonInitial;
    double Rayon;
    double Energie;
    double µ;
    double Vitesse;
    sf::Time Time;
    std::vector<std::pair<double, double>> Arcs;
};
