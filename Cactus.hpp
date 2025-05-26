#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Environment/OrganicEntity.hpp>

/*!
 * @brief Classe représentant un Cactus dans l’environnement.
 *
 * Le Cactus est une entité organique qui ne se déplace pas, mais qui peut
 * interagir avec d'autres entités comme les lézards ou les scorpions
 * selon des règles spécifiques de reproduction ou de consommation.
 */
class Cactus : public OrganicEntity
{
public:
    /*!
     * @brief Constructeur principal du cactus
     *
     * @param position La position initiale du cactus
     */
    Cactus(Vec2d position);

    /*!
     * @brief Destructeur
     */
    virtual ~Cactus() = default;

    /*!
     * @brief Met à jour l’état interne du cactus
     *
     * @param dt Le temps écoulé depuis la dernière mise à jour
     */
    void update(sf::Time dt) override;

    /*!
     * @brief Affiche le cactus dans la fenêtre graphique
     *
     * @param targetWindow Fenêtre où le cactus doit être dessiné
     */
    void draw(sf::RenderTarget& targetWindow) const override;

    /*!
     * @brief Détermine si le cactus est comestible par un scorpion
     *
     * @param scorpion Le scorpion qui tente de manger
     * @return false (par défaut, un cactus n’est pas comestible par un scorpion)
     */
    bool eatableBy(Scorpion const* scorpion) const override;

    /*!
     * @brief Détermine si le cactus est comestible par un lézard
     *
     * @param lizard Le lézard qui tente de manger
     * @return true car le cactus peut être mangé par le lézard
     */
    bool eatableBy(Lizard const* lizard) const override;

    /*!
     * @brief Détermine si un cactus peut être mangé par un autre cactus
     *
     * @param cactus Le cactus "prédateur"
     * @return false, un cactus ne mange pas un autre cactus
     */
    bool eatableBy(Cactus const* cactus) const override;

    /*!
     * @brief Détermine si une entité peut manger ce cactus
     *
     * @param entity L’entité organique qui veut manger le cactus
     * @return true si elle peut le manger, false sinon (en fonction de son type)
     */
    bool eatable(OrganicEntity const* entity) const override;

    /*!
     * @brief Récupère la texture utilisée pour représenter le cactus
     *
     * @return Une référence à la texture correspondante
     */
    sf::Texture& getTexture() const override;

    /*!
     * @brief Détermine si le cactus peut se reproduire avec une entité
     *
     * @param other L’autre entité à tester
     * @return true si la reproduction est possible, false sinon
     */
    bool matable(OrganicEntity const* other) const override;

    /*!
     * @brief Vérifie si un cactus peut se reproduire avec un scorpion
     *
     * @param scorpion Le scorpion testé
     * @return false, un cactus ne peut pas se reproduire avec un scorpion
     */
    bool canMate(Scorpion const* scorpion) const override;

    /*!
     * @brief Vérifie si un cactus peut se reproduire avec un lézard
     *
     * @param lizard Le lézard testé
     * @return false, un cactus ne peut pas se reproduire avec un lézard
     */
    bool canMate(Lizard const* lizard) const override;

    /*!
     * @brief Vérifie si un cactus peut se reproduire avec un autre cactus
     *
     * @param cactus Le cactus partenaire
     * @return false, les cactus ne se reproduisent pas
     */
    bool canMate(Cactus const* cactus) const override;

    /*!
     * @brief Rencontre avec une autre entité organique
     *
     * @param mate L’entité rencontrée
     * @return true si une interaction a lieu, false sinon
     */
    bool meet(OrganicEntity* mate) override;

    /*!
     * @brief Rencontre spécifique avec un scorpion
     *
     * @param scorpion Le scorpion rencontré
     * @return false, un cactus ne rencontre pas un scorpion
     */
    bool meetWith(Scorpion* scorpion) override;

    /*!
     * @brief Rencontre spécifique avec un lézard
     *
     * @param lizard Le lézard rencontré
     * @return false, un cactus ne rencontre pas un lézard
     */
    bool meetWith(Lizard* lizard) override;

    /*!
     * @brief Rencontre spécifique avec un autre cactus
     *
     * @param cactus Le cactus rencontré
     * @return false, un cactus ne rencontre pas de cactus
     */
    bool meetWith(Cactus* cactus) override;
};
