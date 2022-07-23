#include <utility>

#include "Player.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../Particle/Particle.hpp"

Player Player::player;
sf::VertexArray Player::vertexArray;

Player::Player() = default;

Player::Player(const sf::Vector2i& indices)
	: Entity{ indices, sizeMap[EntityType::player] },
	velocity{ 0.f, 0.f },
	isGrounded{ false },
	terminalVelocity{ 75.f, 1000.f },
	gravity{ 180.f },
	friction{ 6.f },
	movementOffset{ 50.f, 150.f }
{
};

Player::~Player() = default;

void Player::update(const float deltaTime, const sf::Event& e)
{
	player.velocity.y += player.gravity * deltaTime;

	switch (e.type)
	{
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::W)
			{
				if (player.isGrounded)
				{
					player.velocity.y -= player.movementOffset.y;
				}
			}
			break;
	}

	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.body.setScale(-1.f, 1.f);
		player.velocity.x -= player.movementOffset.x;
	}
	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.body.setScale(1.f, 1.f);
		player.velocity.x += player.movementOffset.x;
	}

	if (player.velocity.x > 0.f)
	{
		player.velocity.x -= player.friction;
		if (player.velocity.x < 0.f)
		{
			player.velocity.x = 0.f;
		}
	}
	else if (player.velocity.x < 0.f)
	{
		player.velocity.x += player.friction;
		if (player.velocity.x > 0.f)
		{
			player.velocity.x = 0.f;
		}
	}

	player.velocity.x = std::clamp(player.velocity.x, -player.terminalVelocity.x, player.terminalVelocity.x);
	player.velocity.y = std::clamp(player.velocity.y, -player.terminalVelocity.y, player.terminalVelocity.y);

	const Entity* collider{ nullptr };

	player.body.move(player.velocity.x * deltaTime, 0.f);
	collider = player.collisionHandler(EntityType::tile);
	if (collider != nullptr)
	{
		if (player.velocity.x > 0.f)
		{
			player.body.setPosition(collider->body.getPosition().x - collider->body.getSize().x / 2.f - player.body.getSize().x / 2.f, player.body.getPosition().y);
		}
		else if (player.velocity.x < 0.f)
		{
			player.body.setPosition(collider->body.getPosition().x + collider->body.getSize().x / 2.f + player.body.getSize().x / 2.f, player.body.getPosition().y);
		}

		player.velocity.x = 0.f;
	}

	player.body.move(0.f, player.velocity.y * deltaTime);
	collider = player.collisionHandler(EntityType::tile);
	if (collider != nullptr)
	{
		if (player.velocity.y > 0.f)
		{
			player.body.setPosition(player.body.getPosition().x, collider->body.getPosition().y - collider->body.getSize().y / 2.f - player.body.getSize().y / 2.f);
			player.isGrounded = true;
		}
		else if (player.velocity.y < 0.f)
		{
			player.body.setPosition(player.body.getPosition().x, collider->body.getPosition().y + collider->body.getSize().y / 2.f + player.body.getSize().y / 2.f);
		}

		player.velocity.y = 0.f;
	}
	else
	{
		player.isGrounded = false;
	}

	if(!(player.velocity.x == 0.f && player.velocity.y == 0.f))
	Particle::particles.emplace_back(sf::Vector2i{ player.body.getPosition() / 6.f });
}

void Player::draw()
{
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);

	int vertexPtr{};

	player.transform = player.body.getTransform();
	sf::Vertex* quad{ &vertexArray[vertexPtr] };

	for (int i{}; i < 4; ++i)
	{
		player.mesh[i] = player.body.getPoint(i);
		quad[i] = player.transform.transformPoint(player.mesh[i]);
		quad[i].texCoords = player.mesh[i];
	}

	vertexPtr += 4;

	Scene::window.draw(vertexArray, &ResourceManager::textureMap[TextureId::player]);
}
