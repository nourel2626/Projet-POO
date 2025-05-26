
#pragma once

#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <ostream>

/*!
 * @brief A collider is defined by a radius
 * and a position in a toric world.
 *
 * @note radius must be >= 0.
 *
 * @note The "true" direction/distance denotes the
 * direction/distance for the shortest path between
 * the two considered points. (When considering a
 * body, we actually use its center as the source/
 * destination point.)
 */
class Collider
{
    public:
        /*!
         * @brief Obtient la position actuelle du collider
         *
         * @return La position du centre du collider
         */
        Vec2d getPosition() const&;
        /*!
         * @brief Obtient le rayon du collider
         *
         * @return Le rayon du collider
         */
        double getRadius() const;
        void setRadius(double rayon);
        /*!
         * @brief Constructeur principal
         *
         * @param centre La position du centre du collider
         * @param rayon Le rayon du collider
         */
        Collider(Vec2d centre, double rayon);
        /*!
         * @brief Force la position à rester dans les limites du monde (torique)
         */
        void clamping();
        /*!
         * @brief Constructeur de copie
         *
         * @param autre Le collider à copier
         */
        Collider(Collider const& autre);
        /*!
         * @brief Surcharge de l'opérateur d'affectation
         *
         * @param x Le collider à affecter
         * @return Une référence vers l'objet courant
         */
        Collider& operator=(Collider& x);
        /*!
         * @brief Calcule la direction normalisée vers un point donné
         *
         * @param to La destination
         * @return Un vecteur unitaire dans la direction la plus courte vers `to`
         */
        Vec2d directionTo(Vec2d to);
        /*!
         * @brief Calcule la distance minimale torique jusqu’à un point donné
         *
         * @param to Le point cible
         * @return La distance minimale torique entre le centre et `to`
         */
        double distanceTo(Vec2d to);
        /*!
         * @brief Déplace le collider selon un vecteur donné
         *
         * @param dx Le déplacement à appliquer
         */
        void move(const Vec2d& dx);
        /*!
         * @brief Teste si un autre collider est totalement contenu dans celui-ci
         *
         * @param other Le collider cible
         * @return true si `other` est entièrement à l’intérieur de ce collider
         */
        bool isColliderInside (const Collider& other);
        /*!
         * @brief Teste si un point est à l’intérieur du collider
         *
         * @param p Le point à tester
         * @return true si le point est à l’intérieur
         */
        bool isPointInside (Vec2d p);
        /*!
         * @brief Surcharge de l’opérateur > (interprétation contextuelle)
         */
        bool operator>(Collider& body1);
        /*!
         * @brief Surcharge de l’opérateur > pour les positions
         */
        bool operator>(Vec2d p);
        /*!
         * @brief Calcule la direction vers un autre collider
         *
         * @param to Le collider cible
         * @return Vecteur unitaire de direction vers `to`
         */
        Vec2d directionTo(const Collider& to);
        /*!
         * @brief Teste la collision avec un autre collider
         *
         * @param other Le collider cible
         * @return true en cas de chevauchement
         */
        bool isColliding(const Collider& other);
        /*!
         * @brief Surcharge de l'opérateur | (interprétation contextuelle, probablement test de collision)
         */
        bool operator|(Collider& body1);
        /*!
         * @brief Surcharge de l'opérateur += pour déplacer le collider
         *
         * @param dx Le vecteur de déplacement
         */
        void operator+=(Vec2d dx);
        /*!
         * @brief Calcule la distance torique vers un autre collider
         *
         * @param to Le collider cible
         * @return Distance minimale torique entre les centres
         */
        double distanceTo(const Collider& to);
        /*!
         * @brief Méthode virtuelle pure pour afficher le collider
         *
         * @param target Cible de rendu SFML
         */
        virtual void draw(sf::RenderTarget& target) const;
        virtual ~Collider() = default;
    private:
        Vec2d Position;
        double Rayon;
};
        /*!
         * @brief Surcharge de l’opérateur de flux pour afficher un collider
         *
         * @param os Le flux de sortie
         * @param body Le collider à afficher
         * @return Le flux modifié
         */
        std::ostream& operator<<(std::ostream& os,const Collider& body);
