#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Environment/OrganicEntity.hpp>

class Cactus :public OrganicEntity{
public:
    Cactus(Vec2d position);
    ~Cactus();
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& targetWindow) const override;
    bool eatableBy(Scorpion const* scorpion) const override;
    bool eatableBy(Lizard const* lizard) const override;
    bool eatableBy(Cactus const* cactus) const override;
    bool eatable( OrganicEntity const* entity) const override;
    sf::Texture& getTexture() const override;
    bool matable(OrganicEntity const* other) const override;
    bool canMate(Scorpion const* scorpion) const override;
    bool canMate(Lizard const* lizard) const override;
    bool canMate(Cactus const* food) const override;
    bool meet (OrganicEntity *mate)  override;
    bool meetWith (Scorpion *scorpion)  override;
    bool meetWith (Lizard *lizard)  override;
    bool meetWith (Cactus *cactus)   override;
    //bool eatableBy(OrganicEntity const* entity) const override;
private:


};
