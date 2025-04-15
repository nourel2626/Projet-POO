#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Utility/Vec2d.hpp"
#include <Utility/Utility.hpp>


class Animal;
class OrganicEntity;

class Environment {
public :
     Environment();

     /*!
     *@brief Destructeur
     */
     ~Environment();
    /*!
     * @brief Ajoute un animal
     * @param animal l'animal à ajouter à la liste d'animaux
     */
    void addEntity(OrganicEntity* entity);
    /*!
     * @brief Ajoute une cible dans l'environnement
     * @param cible la cible à ajouter à la liste de cibles
     */
    void addTarget (const Vec2d& cible);
    /*!
     * @brief Permet de faire évoluer les animaux au cours du temps
     * @param dt // à modifer plus tard
     */
    void update(sf::Time dt);
    /*!
     * @brief Matérialise graphiquement les cibles sous forme de petits cercles rouges
     * @param targetWindow la fenêtre sur laquelle va s'afficher le dessin
     */
    void draw(sf::RenderTarget& targetWindow) const;
    /*!
     * @brief Permet de vider l'environnement de ses animaux et ses cibles
     */
    void clean ();

    Environment(const Environment&) = delete; // Permet d'éviter la copie d'un Environment à partir d'un constructeur de copie

    Environment& operator=(const Environment&) = delete; // Permet d'éviter la copie d'un Environment par affectation

   double getTemperature() const;
   void increaseTemperature();
   void decreaseTemperature();
   void resetControls();
   std::list<Vec2d> getEntitiesInSightForAnimal(Animal* observer) const;
    std::list<OrganicEntity> getEntitiesInSightForAnimal2(Animal *observer) const ;
private :
    std::list <OrganicEntity*> Entites;
    std::list <Vec2d> Cibles;
    double Temperature;
};
