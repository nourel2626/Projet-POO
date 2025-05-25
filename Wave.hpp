#pragma once
//#include <fstream>
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
 * Hérite de "Collider"
 * Une onde possède une origine, une énergie, une atténuation µ, une vitesse, un rayon initial
 * et un rayon courant. Elle peut être fragmentée par des obstacles,
 * représentés sous forme d’arcs angulaires.
 */
class Wave : public Collider {
public:
    /*!
     * @brief Constructeur de l'onde
     *
     * Initialise une onde circulaire à une position donnée, avec des paramètres physiques.
     *
     * @param origine Position d'origine de l'onde
     * @param energie Énergie initiale portée par l'onde
     * @param rayon Rayon initial de l'onde
     * @param µ Coefficient d'atténuation de l'énergie
     * @param vitesse Vitesse de propagation de l'onde
     */
    Wave(const Vec2d& origine, double energie, double rayon, double µ, double vitesse);

    /*!
     * @brief Met à jour l'état de l'onde au cours du temps
     *
     * Met à jour le rayon, fragmente les arcs en fonction des collisions avec les obstacles,
     * et gère l'évolution temporelle.
     *
     * @param dt Durée écoulée depuis la dernière mise à jour
     */
    void update(sf::Time dt);

    /*!
     * @brief Dessine l'onde et ses arcs visibles dans la fenêtre cible
     *
     * @param targetWindow Fenêtre sur laquelle dessiner
     */
    void draw(sf::RenderTarget& targetWindow) const override;

    /*!
     * @brief Retourne l’intensité actuelle de l’onde
     *
     * @return Intensité de l'onde
     */
    double getIntensity() const;

    /*!
     * @brief Définit un nouveau rayon courant pour l'onde
     *
     * @param rayon Nouveau rayon à appliquer
     */
    void setRayon(double rayon);

    /*!
     * @brief Teste si un angle appartient à un arc donné
     *
     * Un angle est contenu dans un arc si :
     * - arc.first ≤ angle ≤ arc.second (cas normal)
     * - ou s'il traverse 0, angle est entre [first, 2π) U [0, second]
     *
     * @param arc Arc représenté comme une paire (début, fin) en radians
     * @param angle Angle à tester (normalisé entre 0 et 2π)
     * @return true si l'angle appartient à l'arc, false sinon
     */
    bool containsAngle(const std::pair<double, double>& arc, double angle);
    double normalizeAngle(double angle);
    void fragmente(Collider* obstacle);
    bool distanceToObstacle(const Vec2d& pos );
    virtual ~Wave() = default;
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
