#include "Player.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../Particle/Particle.hpp"

Player Player::player;
sf::VertexArray Player::vertexArray;
const float Player::gravity{ 9.8f };
const float Player::friction{ 12.f };

Player::Player() = default;

Player::Player(const sf::Vector2i& indices)
	: Entity{ indices, sf::Vector2f(16.f, 16.f) } 
{
	velocity = sf::Vector2f(0.f, 0.f);
	isGrounded = false;
};

Player::~Player() = default;

void Player::update(const float deltaTime, const sf::Event& e)
{
	player.velocity.y += gravity * deltaTime;

	switch (e.type)
	{
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::W)
			{
				if (player.isGrounded)
				{
					player.velocity.y -= 10.f;
				}
			}
			break;
	}

	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.body.setScale(-1.f, 1.f);
		player.velocity.x -= 50.f * deltaTime;
	}
	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.body.setScale(1.f, 1.f);
		player.velocity.x += 50.f * deltaTime;
	}

	if (player.velocity.x > 0.f)
	{
		player.velocity.x -= friction * deltaTime;
		if (player.velocity.x < 0.f)
		{
			player.velocity.x = 0.f;
		}
	}
	else if (player.velocity.x < 0.f)
	{
		player.velocity.x += friction * deltaTime;
		if (player.velocity.x > 0.f)
		{
			player.velocity.x = 0.f;
		}
	}

	const Entity* collider{ nullptr };

	player.body.move(player.velocity.x, 0.f);
	collider = player.collisionHandler(EntityType::tile);
	if (collider != nullptr)
	{
		if (player.velocity.x > 0.f)
		{
			player.body.setPosition(collider->body.getPosition().x - collider->body.getSize().x / 2.f - player.body.getSize().x / 2.f, player.body.getPosition().y);
			player.velocity.x = 0.f;
		}
		else if (player.velocity.x < 0.f)
		{
			player.body.setPosition(collider->body.getPosition().x + collider->body.getSize().x / 2.f + player.body.getSize().x / 2.f, player.body.getPosition().y);
			player.velocity.x = 0.f;
		}
	}

	player.body.move(0.f, player.velocity.y);
	collider = player.collisionHandler(EntityType::tile);
	if (collider != nullptr)
	{
		if (player.velocity.y > 0.f)
		{
			player.body.setPosition(player.body.getPosition().x, collider->body.getPosition().y - collider->body.getSize().y / 2.f - player.body.getSize().y / 2.f);
			player.velocity.y = 0.f;
			player.isGrounded = true;
		}
		else if (player.velocity.y < 0.f)
		{
			player.body.setPosition(player.body.getPosition().x, collider->body.getPosition().y + collider->body.getSize().y / 2.f + player.body.getSize().y / 2.f);
			player.velocity.y = 0.f;
		}
	}
	else
	{
		player.isGrounded = false;
	}

	if(player.velocity.x != 0.f || player.velocity.y != 0.f)
	Particle::particles.emplace_back(sf::Vector2i(player.body.getPosition().x / 4.f, player.body.getPosition().y / 4.f));
}

void Player::draw()
{
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);

	int vertexPtr{ 0 };

	player.transform = player.body.getTransform();
	sf::Vertex* quad{ &vertexArray[vertexPtr] };

	for (int i{ 0 }; i < 4; i++)
	{
		player.mesh[i] = player.body.getPoint(i);
		quad[i] = player.transform.transformPoint(player.mesh[i]);
		quad[i].texCoords = sf::Vector2f(player.mesh[i].x, player.mesh[i].y);
	}

	vertexPtr += 4;

	Scene::window.draw(vertexArray, &ResourceManager::textureMap[TextureId::player]);
}
