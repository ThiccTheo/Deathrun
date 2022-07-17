#pragma once

#include <iostream>

#include "CommonSFML.hpp"

enum class EntityType { player, tile, particle, count };

class Entity
{
public:
	sf::Transform transform;
	sf::RectangleShape body;
	sf::Vector2f mesh[4];

	Entity();
	Entity(const sf::Vector2i& indices, const sf::Vector2f& bodySize);
	virtual ~Entity();
	const Entity* collisionHandler(const EntityType entityType);
};