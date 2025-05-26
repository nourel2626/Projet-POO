#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "Utility/Vec2d.hpp"
#include <Utility/Utility.hpp>
#include <vector>

class Collider;
class Cloud;
class Rock;
class Wave;
class Animal;
class OrganicEntity;
class CloudGenerator;

/*!
 * @class Environment
 * @brief Classe représentant l’environnement dans lequel évoluent les entités
 */
class Environment {
public:
    /*!
     * @brief Constructeur
     */
    Environment();

    /*!
     * @brief Destructeur
     */
    ~Environment();

    /*!
     * @brief Ajoute une entité organique à l’environnement
     *
     * @param entity L’entité à ajouter
     */
    void addEntity(OrganicEntity* entity);

    /*!
     * @brief Ajoute une cible dans l’environnement
     *
     * @param cible La cible à ajouter
     */
    void addTarget(const Vec2d& cible);

    /*!
     * @brief Met à jour l’environnement au cours du temps
     *
     * @param dt Le pas de temps
     */
    void update(sf::Time dt);

    /*!
     * @brief Dessine les éléments de l’environnement
     *
     * @param targetWindow La fenêtre de rendu
     */
    void draw(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Vide l’environnement
     */
    void clean();

    /*!
     * @brief Constructeur de copie supprimé
     */
    Environment(const Environment&) = delete;

    /*!
     * @brief Opérateur d’affectation supprimé
     */
    Environment& operator=(const Environment&) = delete;

    /*!
     * @brief Renvoie la température actuelle
     *
     * @return La température de l’environnement
     */
    double getTemperature() const;

    /*!
     * @brief Augmente la température de 0.5
     */
    void increaseTemperature();

    /*!
     * @brief Diminue la température de 0.5
     */
    void decreaseTemperature();

    /*!
     * @brief Réinitialise les paramètres climatiques
     */
    void resetControls();

    /*!
     * @brief Renvoie les entités visibles par un animal (sous forme de positions)
     *
     * @param observer L’animal observateur
     * @return Liste de positions visibles
     */
    std::list<Vec2d> getEntitiesInSightForAnimal(Animal* observer) const;

    /*!
     * @brief Renvoie les entités visibles par un animal
     *
     * @param observer L’animal observateur
     * @return Liste d’entités visibles
     */
    std::list<OrganicEntity*> getEntitiesInSightForAnimal2(Animal* observer) const;

    /*!
     * @brief Ajoute une onde à l’environnement
     *
     * @param wave L’onde à ajouter
     */
    void addWave(Wave* wave);

    /*!
     * @brief Ajoute un obstacle à l’environnement
     *
     * @param collider L’obstacle à ajouter
     */
    void addObstacle(Collider* collider);

    /*!
     * @brief Renvoie la liste des obstacles de l’environnement
     *
     * @return Vecteur de pointeurs vers les obstacles
     */
    std::vector<Collider*> getObstacles() const;

    /*!
     * @brief Ajoute un nuage à l’environnement
     *
     * @param cloud Le nuage à ajouter
     */
    void addCloud(Cloud* cloud);

    /*!
     * @brief Ajoute un générateur de nuages à l’environnement
     *
     * @param generator Le générateur à ajouter
     */
    void addGenerator(CloudGenerator* generator);

    /*!
     * @brief Renvoie le nombre total de nuages
     *
     * @return Nombre de nuages
     */
    double getCloudCount() const;

    /*!
     * @brief Renvoie la durée de sécheresse
     *
     * @return Durée de sécheresse
     */
    sf::Time getDroughtDuration() const;

    /*!
     * @brief Indique si la pluie est active
     *
     * @return true si pluie active, false sinon
     */
    bool getPluie() const;

    /*!
     * @brief Indique si l’environnement est humide
     *
     * @return true si humide, false sinon
     */
    bool getHumidity() const;
    /*!
     * @brief Calcule les intensités des ondes au point donné
     *
     * @param location La position où l'on souhaite évaluer l'intensité des ondes
     * @param dt Le pas de temps utilisé pour mettre à jour les ondes
     * @return Une liste des intensités des ondes au point spécifié
     */
    std::list<double> getIntensiteOndes(Vec2d location, sf::Time dt) const;
private:
    std::list<OrganicEntity*> Entites;
    std::list<Vec2d> Cibles;
    double Temperature;
    std::vector<Wave*> Waves;
    std::vector<Collider*> Rocks;
    std::list<Cloud*> Clouds;
    std::list<CloudGenerator*> Generators;
    sf::Time DroughtDuration = sf::Time::Zero;
    sf::Time RainDuration = sf::Time::Zero;
    sf::Time HumidityDuration = sf::Time::Zero;
    bool Pluie;
    bool Drought;
    bool Humidity;
};
