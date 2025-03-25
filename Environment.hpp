#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>

class Animal;

class Environment {
public :
      /*!
     * @brief Ajoute un animal
     * @param animal l'animal à ajouter à la liste d'animaux
     */
    void addAnimal(Animal*& animal);
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

    ~Environment();

    Environment& operator=(const Environment&) = delete; // Permet d'éviter la copie d'un Environment par affectation

    Environment();
private :
    std::list <Animal*> Animaux;
    std::list <Vec2d> Cibles;
};
