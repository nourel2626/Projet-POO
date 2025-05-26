#pragma once

#include "Obstacle/Collider.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @brief Classe abstraite représentant une entité organique dans l'environnement.
 *
 * Hérite de Collider pour avoir une position et un rayon.
 * Possède une énergie, une longévité, une taille, un âge, et des comportements de reproduction et d'alimentation.
 */
class Scorpion;
class Lizard;
class Cactus;
class Animal;

class OrganicEntity : public Collider {
public:
    /*!
     * @brief Destructeur virtuel pour assurer la destruction correcte via un pointeur sur la classe de base.
     */
    virtual ~OrganicEntity();

    /*!
     * @brief Constructeur principal.
     *
     * @param position Position initiale de l'entité.
     * @param energie Énergie de départ.
     * @param longevite Durée de vie maximale.
     * @param taille Taille de l'entité.
     */
    OrganicEntity(Vec2d const& position, double energie, sf::Time longevite, double taille);

    /*!
     * @brief Met à jour l'état de l'entité
     *
     * @param dt Durée écoulée depuis la dernière mise à jour.
     */
    virtual void update(sf::Time dt) = 0;

    /*!
     * @brief Dessine l'entité dans la fenêtre
     *
     * @param target Cible de rendu
     */
    virtual void draw(sf::RenderTarget& target) const = 0;

    /*!
     * @brief Renvoie la taille de l'entité.
     *
     * @return La taille de l'entité.
     */
    double getTaille() const;

    /*!
     * @brief Renvoie la texture associée à cette entité
     *
     * @return Texture à utiliser pour l'affichage.
     */
    virtual sf::Texture& getTexture() const = 0;

    /*!
     * @brief Teste si une autre entité est comestible pour celle-ci
     *
     * @param entity Entité à tester.
     * @return true si comestible, false sinon.
     */
    virtual bool eatable(OrganicEntity const* entity) const = 0;

    /*!
     * @brief Teste si l'entité est comestible par un Scorpion.
     *
     * @param scorpion Scorpion à tester.
     * @return true si oui, false sinon
     */
    virtual bool eatableBy(Scorpion const* scorpion) const = 0;

    /*!
     * @brief Teste si l'entité est comestible par un Lizard.
     *
     * @param lizard Lézard testeur.
     * @return true si oui, false sinon
     */
    virtual bool eatableBy(Lizard const* lizard) const = 0;

    /*!
     * @brief Teste si l'entité est comestible par un Cactus.
     *
     * @param cactus Cactus testeur.
     * @return true si oui, false sinon
     */
    virtual bool eatableBy(Cactus const* cactus) const = 0;

    /*!
     * @brief Accède à l’énergie de l’entité.
     *
     * @return L’énergie actuelle.
     */
    double getEnergie() const;

    /*!
     * @brief Modifie l’énergie de l’entité.
     *
     * @param energie Nouvelle énergie.
     */
    void setEnergie(double energie);

    /*!
     * @brief Teste si l’entité est morte (âge > longévité ou énergie épuisée).
     *
     * @return true si morte.
     */
    bool isDead();

    /*!
     * @brief Met à jour l’âge de l’entité.
     *
     * @param dt Durée à ajouter à l’âge actuel.
     */
    void updateAge(sf::Time dt);

    /*!
     * @brief Teste si une autre entité est compatible pour reproduction.
     *
     * @param other Entité potentiellement partenaire.
     * @return true si reproduction possible.
     */
    virtual bool matable(OrganicEntity const* other) const = 0;

    /*!
     * @brief Teste la compatibilité de reproduction avec un Scorpion.
     *
     * @param scorpion Partenaire.
     * @return true si reproduction possible.
     */
    virtual bool canMate(Scorpion const* scorpion) const = 0;

    /*!
     * @brief Teste la compatibilité de reproduction avec un Lizard.
     *
     * @param lizard Partenaire.
     * @return true si reproduction possible.
     */
    virtual bool canMate(Lizard const* lizard) const = 0;

    /*!
     * @brief Teste la compatibilité de reproduction avec un Cactus.
     *
     * @param food Partenaire.
     * @return true si reproduction possible.
     */
    virtual bool canMate(Cactus const* food) const = 0;

    /*!
     * @brief Renvoie l’âge courant.
     *
     * @return Âge de l’entité.
     */
    sf::Time getAge() const;

    /*!
     * @brief Rencontre une autre entité pour reproduction
     *
     * @param mate Partenaire potentiel.
     * @return true si rencontre effective.
     */
    virtual bool meet(OrganicEntity* mate) = 0;

    /*!
     * @brief Rencontre spécifique avec un Scorpion
     *
     * @param scorpion Partenaire.
     * @return true si rencontre réussie.
     */
    virtual bool meetWith(Scorpion* scorpion) = 0;

    /*!
     * @brief Rencontre spécifique avec un Lizard
     *
     * @param lizard Partenaire.
     * @return true si rencontre réussie.
     */
    virtual bool meetWith(Lizard* lizard) = 0;

    /*!
     * @brief Rencontre spécifique avec un Cactus
     *
     * @param cactus Partenaire.
     * @return true si rencontre réussie.
     */
    virtual bool meetWith(Cactus* cactus) = 0;

private:
    double Energie;
    sf::Time Age;
    sf::Time Longevite;
};
