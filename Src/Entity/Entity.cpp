#include "Entity.hpp"
#include "Player/Player.hpp"
#include "Particle/Particle.hpp"
#include "Tile/Tile.hpp"

Entity::Entity() = default;

Entity::Entity(const sf::Vector2i& indices, const sf::Vector2f& bodySize)
	: body{ bodySize }
{
	body.setOrigin(bodySize / 2.f);
	body.setPosition(indices.x * bodySize.x, indices.y * bodySize.y);
}

Entity::~Entity() = default;

const Entity* Entity::collisionHandler(const EntityType entityType)
{
	switch (entityType)
	{
		case EntityType::player:
			if (body.getGlobalBounds().intersects(Player::player.body.getGlobalBounds()))
			{
				return &Player::player;
			}
			break;
		case EntityType::particle:
			for (Particle& particle : Particle::particles)
			{
				if (body.getGlobalBounds().intersects(particle.body.getGlobalBounds()))
				{
					return &particle;
				}
			}
			break;
		case EntityType::tile:
			for (Tile& tile : Tile::tiles)
			{
				if (body.getGlobalBounds().intersects(tile.body.getGlobalBounds()))
				{
					return &tile;
				}
			}
			break;
	}

	return nullptr;
}
