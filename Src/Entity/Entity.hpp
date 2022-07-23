#pragma once

#include <iostream>
#include <unordered_map>

#include "CommonSFML.hpp"

enum class EntityType { player, tile, particle, count };

class Entity
{
public:
	sf::Transform transform;
	sf::RectangleShape body;
	sf::Vector2f mesh[4];
	static std::unordered_map<EntityType, sf::Vector2f> sizeMap;

	Entity();
	Entity(const sf::Vector2i& indices, const sf::Vector2f& bodySize);
	virtual ~Entity();
	static void init();
	const Entity* collisionHandler(const EntityType entityType);
};