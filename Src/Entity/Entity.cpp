#include "Entity.hpp"

Entity::Entity() = default;

Entity::Entity(const sf::Vector2i& indices, const sf::Vector2f& bodySize)
{
	body.setSize(bodySize);
	body.setOrigin(bodySize.x / 2.f, bodySize.y / 2.f);
	body.setPosition(indices.x * bodySize.x, indices.y * bodySize.y);
}

Entity::~Entity() = default;
