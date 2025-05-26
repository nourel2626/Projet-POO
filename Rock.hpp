#pragma once
#include <Obstacle/Collider.hpp>


/*!
 * @class Rock
 *
 * @brief Représente un rocher dans le monde simulé.
 *
 * Hérite de la classe `Collider` et possède une orientation propre.
 * La position et le rayon sont initialisés à la création.
 */
class Rock : public Collider {
public:
    /*!
     * @brief Constructeur du rocher
     *
     * Initialise un rocher à une position donnée, avec un rayon déterminé
     * automatiquement par la méthode "calculRayon".
     *
     * @param position La position du centre du rocher
     */
    Rock(const Vec2d& position);

    /*!
     * @brief Dessine le rocher sur la fenêtre cible
     *
     * Méthode héritée de "Collider" et redéfinie
     *
     * @param targetWindow La fenêtre de rendu
     */
    void draw(sf::RenderTarget& targetWindow) const override;
    virtual ~Rock() = default;

private:
    double Orientation;
    Vec2d Position;
    double Rayon;
    /*!
     * @brief Calcule le rayon du rocher
     *
     * Méthode statique utilisée pour attribuer un rayon à chaque instance de Rock.
     *
     * @return Un rayon utilisé dans le constructeur
     */
    static double calculRayon();
};
